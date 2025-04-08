#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <memory>
#include <optional>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <algorithm>

using Value = std::optional<double>;

class IdentifierTable;

class Expression 
{
public:
    virtual Value Evaluate(const IdentifierTable& table) const = 0;
    virtual ~Expression() = default;
};

class Literal : public Expression 
{
public:
    explicit Literal(double value) : m_value(value) {}
    Value Evaluate(const IdentifierTable&) const override { return m_value; }
private:
    double m_value;
};

class VariableReference : public Expression 
{
public:
    explicit VariableReference(std::string name) : m_name(std::move(name)) {}
    Value Evaluate(const IdentifierTable& table) const override;
private:
    std::string m_name;
};

class BinaryOperation : public Expression 
{
public:
    enum class Operator { Add, Subtract, Multiply, Divide };

    BinaryOperation(std::string lhs, std::string rhs, Operator op)
        : m_lhs(std::move(lhs)), m_rhs(std::move(rhs)), m_operator(op) {}

    Value Evaluate(const IdentifierTable& table) const override;

private:
    std::string m_lhs;
    std::string m_rhs;
    Operator m_operator;
};

class IdentifierTable 
{
public:
    bool DeclareVariable(const std::string& name);
    bool AssignVariable(const std::string& name, double value);
    bool AssignVariableFromIdentifier(const std::string& name, const std::string& other);
    bool DeclareFunction(const std::string& name, std::unique_ptr<Expression> expr);

    Value GetValue(const std::string& name) const;
    bool IsDeclared(const std::string& name) const;
    bool IsFunction(const std::string& name) const;

    std::map<std::string, Value> GetAllVariables() const;
    std::map<std::string, Value> GetAllFunctions() const;

private:
    std::unordered_map<std::string, Value> m_variables;
    std::unordered_map<std::string, std::unique_ptr<Expression>> m_functions;
};

class Calculator 
{
public:
    void ExecuteCommand(const std::string& command);

private:
    IdentifierTable m_table;
    void PrintIdentifier(const std::string& name) const;
    void PrintVariables() const;
    void PrintFunctions() const;
};

class CommandParser 
{
public:
    void Run();

private:
    Calculator m_calculator;
};
