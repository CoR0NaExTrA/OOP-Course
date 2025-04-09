#include "../Calculator/Calculator.h"

Value VariableReference::Evaluate(const IdentifierTable& table) const {
    return table.GetValue(m_name);
}

Value BinaryOperation::Evaluate(const IdentifierTable& table) const {
    Value left = table.GetValue(m_lhs);
    Value right = table.GetValue(m_rhs);

    if (!left || !right || (m_operator == Operator::Divide && *right == 0)) {
        return std::nullopt;
    }

    switch (m_operator) {
    case Operator::Add: return *left + *right;
    case Operator::Subtract: return *left - *right;
    case Operator::Multiply: return *left * *right;
    case Operator::Divide: return *left / *right;
    }
    return std::nullopt;
}

bool IdentifierTable::DeclareVariable(const std::string& name) {
    if (IsDeclared(name)) return false;
    m_variables[name] = std::nullopt;
    return true;
}

bool IdentifierTable::AssignVariable(const std::string& name, double value) {
    if (!IsDeclared(name)) m_variables[name] = value;
    else if (IsFunction(name)) return false;
    m_variables[name] = value;
    return true;
}

bool IdentifierTable::AssignVariableFromIdentifier(const std::string& name, const std::string& other) {
    if (!IsDeclared(other)) return false;
    Value val = GetValue(other);
    if (!IsDeclared(name)) m_variables[name] = val;
    else if (IsFunction(name)) return false;
    m_variables[name] = val;
    return true;
}

bool IdentifierTable::DeclareFunction(const std::string& name, std::unique_ptr<Expression> expr) {
    if (IsDeclared(name)) return false;
    m_functions[name] = std::move(expr);
    return true;
}

Value IdentifierTable::GetValue(const std::string& name) const {
    if (auto it = m_variables.find(name); it != m_variables.end()) return it->second;
    if (auto it = m_functions.find(name); it != m_functions.end()) return it->second->Evaluate(*this);
    return std::nullopt;
}

bool IdentifierTable::IsDeclared(const std::string& name) const {
    return m_variables.contains(name) || m_functions.contains(name);
}

bool IdentifierTable::IsFunction(const std::string& name) const {
    return m_functions.contains(name);
}

std::map<std::string, Value> IdentifierTable::GetAllVariables() const {
    return { m_variables.begin(), m_variables.end() };
}

std::map<std::string, Value> IdentifierTable::GetAllFunctions() const {
    std::map<std::string, Value> result;
    for (const auto& [name, expr] : m_functions) {
        result[name] = expr->Evaluate(*this);
    }
    return result;
}

std::vector<Token> Calculator::Tokenize(const std::string& input) {
    std::vector<Token> tokens;
    std::string current;
    auto is_operator = [](char c) { return c == '+' || c == '-' || c == '*' || c == '/'; };

    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];

        if (std::isspace(c)) continue;

        if (std::isalpha(c)) {
            current = c;
            while (i + 1 < input.size() && (std::isalnum(input[i + 1]) || input[i + 1] == '_')) {
                current += input[++i];
            }
            tokens.push_back({ TokenType::Identifier, current });
        }
        else if (std::isdigit(c) || c == '.') {
            current = c;
            while (i + 1 < input.size() && (std::isdigit(input[i + 1]) || input[i + 1] == '.')) {
                current += input[++i];
            }
            tokens.push_back({ TokenType::Number, current });
        }
        else if (is_operator(c)) {
            tokens.push_back({ TokenType::Operator, std::string(1, c) });
        }
        else if (c == '=') {
            tokens.push_back({ TokenType::Equals, "=" });
        }
        else {
            tokens.push_back({ TokenType::Unknown, std::string(1, c) });
        }
    }

    return tokens;
}

void Calculator::ExecuteCommand(const std::string& command) {
    auto tokens = Tokenize(command);
    if (tokens.empty()) {
        std::cout << "Unknown command\n";
        return;
    }

    const auto& cmd = tokens[0].value;

    if (cmd == "var") {
        if (tokens.size() != 2 || tokens[1].type != TokenType::Identifier) {
            std::cout << "Invalid usage\n";
            return;
        }
        if (!m_table.DeclareVariable(tokens[1].value)) {
            std::cout << "Name already exists\n";
        }
    }
    else if (cmd == "let") {
        if (tokens.size() != 4 || tokens[1].type != TokenType::Identifier || tokens[2].type != TokenType::Equals) {
            std::cout << "Invalid usage\n";
            return;
        }
        const std::string& name = tokens[1].value;
        const std::string& val = tokens[3].value;

        if (tokens[3].type == TokenType::Number) {
            if (!m_table.AssignVariable(name, std::stod(val))) {
                std::cout << "Invalid usage\n";
            }
        }
        else if (tokens[3].type == TokenType::Identifier) {
            if (!m_table.IsDeclared(val)) {
                std::cout << "Name does not exist\n";
                return;
            }
            if (!m_table.AssignVariableFromIdentifier(name, val)) {
                std::cout << "Invalid usage\n";
            }
        }
        else {
            std::cout << "Invalid usage\n";
        }
    }
    else if (cmd == "fn") {
        if (!(tokens.size() >= 4 && tokens[2].type == TokenType::Equals)) {
            std::cout << "Invalid usage\n";
            return;
        }

        const std::string& fname = tokens[1].value;

        // fn f = x
        if (tokens.size() == 4 && tokens[3].type == TokenType::Identifier) {
            if (!m_table.IsDeclared(tokens[3].value)) {
                std::cout << "Name does not exist\n";
                return;
            }

            auto ref = std::make_unique<VariableReference>(tokens[3].value);
            if (!m_table.DeclareFunction(fname, std::move(ref))) {
                std::cout << "Name already exists\n";
            }
            return;
        }

        // fn f = x + y
        if (tokens.size() == 6 &&
            tokens[3].type == TokenType::Identifier &&
            tokens[4].type == TokenType::Operator &&
            tokens[5].type == TokenType::Identifier) {

            if (!m_table.IsDeclared(tokens[3].value) || !m_table.IsDeclared(tokens[5].value)) {
                std::cout << "Name does not exist\n";
                return;
            }

            BinaryOperation::Operator op;
            if (tokens[4].value == "+") op = BinaryOperation::Operator::Add;
            else if (tokens[4].value == "-") op = BinaryOperation::Operator::Subtract;
            else if (tokens[4].value == "*") op = BinaryOperation::Operator::Multiply;
            else if (tokens[4].value == "/") op = BinaryOperation::Operator::Divide;
            else {
                std::cout << "Invalid usage\n";
                return;
            }

            auto expr = std::make_unique<BinaryOperation>(tokens[3].value, tokens[5].value, op);
            if (!m_table.DeclareFunction(fname, std::move(expr))) {
                std::cout << "Name already exists\n";
            }
            return;
        }

        std::cout << "Invalid usage\n";
    }
    else if (cmd == "print") {
        if (tokens.size() != 2 || tokens[1].type != TokenType::Identifier) {
            std::cout << "Invalid usage\n";
            return;
        }
        PrintIdentifier(tokens[1].value);
    }
    else if (cmd == "printvars") {
        PrintVariables();
    }
    else if (cmd == "printfns") {
        PrintFunctions();
    }
    else {
        std::cout << "Unknown command\n";
    }
}

void Calculator::PrintIdentifier(const std::string& name) const {
    Value val = m_table.GetValue(name);
    if (!val) std::cout << "nan\n";
    else std::cout << std::fixed << std::setprecision(2) << *val << "\n";
}

void Calculator::PrintVariables() const {
    auto vars = m_table.GetAllVariables();
    for (const auto& [name, val] : vars) {
        std::cout << name << ':';
        if (val) std::cout << std::fixed << std::setprecision(2) << *val << '\n';
        else std::cout << "nan\n";
    }
}

void Calculator::PrintFunctions() const {
    auto funcs = m_table.GetAllFunctions();
    for (const auto& [name, val] : funcs) {
        std::cout << name << ':';
        if (val) std::cout << std::fixed << std::setprecision(2) << *val << '\n';
        else std::cout << "nan\n";
    }
}

void CommandParser::Run() {
    std::string line;
    while (std::getline(std::cin, line)) {
        if (!line.empty()) m_calculator.ExecuteCommand(line);
    }
}