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

void Calculator::ExecuteCommand(const std::string& command) {
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;

    if (cmd == "var") {
        std::string name;
        if (!(iss >> name) || !std::isalpha(name[0])) std::cout << "Invalid usage\n";
        else if (!m_table.DeclareVariable(name)) std::cout << "Name already exists\n";
    }
    else if (cmd == "let") {
        std::string lhs, eq, rhs;
        if (!(iss >> lhs >> eq >> rhs) || eq != "=") std::cout << "Invalid usage\n";
        else if (std::isdigit(rhs[0]) || rhs[0] == '-') m_table.AssignVariable(lhs, std::stod(rhs));
        else if (!m_table.AssignVariableFromIdentifier(lhs, rhs)) std::cout << "Name does not exist\n";
    }
    else if (cmd == "fn") {
        std::string name, eq, lhs, op, rhs;
        if (!(iss >> name >> eq)) std::cout << "Invalid usage\n";
        else {
            std::string rest;
            std::getline(iss, rest);
            rest.erase(std::remove_if(rest.begin(), rest.end(), ::isspace), rest.end());
            auto pos = rest.find_first_of("+-*/");
            if (pos == std::string::npos) {
                if (!m_table.DeclareFunction(name, std::make_unique<VariableReference>(rest)))
                    std::cout << "Name already exists\n";
            }
            else {
                std::string l = rest.substr(0, pos);
                std::string r = rest.substr(pos + 1);
                BinaryOperation::Operator oper =
                    rest[pos] == '+' ? BinaryOperation::Operator::Add :
                    rest[pos] == '-' ? BinaryOperation::Operator::Subtract :
                    rest[pos] == '*' ? BinaryOperation::Operator::Multiply :
                    BinaryOperation::Operator::Divide;
                if (!m_table.DeclareFunction(name, std::make_unique<BinaryOperation>(l, r, oper)))
                    std::cout << "Name already exists\n";
            }
        }
    }
    else if (cmd == "print") {
        std::string name;
        iss >> name;
        PrintIdentifier(name);
    }
    else if (cmd == "printvars") PrintVariables();
    else if (cmd == "printfns") PrintFunctions();
    else std::cout << "Unknown command\n";
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