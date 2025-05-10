#include "ParseExpression.h"
#include <sstream>
#include <vector>
#include <limits>

int ParseExpression(std::istream& in) {
    char ch;
    in >> ch;
    if (ch != '(') {
        in.unget();
        int num;
        if (!(in >> num)) throw std::runtime_error("Invalid number");
        return num;
    }

    char op;
    in >> op;
    if (op != '+' && op != '*') throw std::runtime_error("Invalid operator");

    std::vector<int> args;
    while (true) {
        in >> std::ws;
        if (in.peek() == ')') {
            in.get();
            break;
        }
        args.push_back(ParseExpression(in));
    }

    if (args.empty()) throw std::runtime_error("No arguments provided");

    int result = (op == '+') ? 0 : 1;
    for (int arg : args) {
        if (op == '+') {
            if (result > std::numeric_limits<int>::max() - arg) throw std::overflow_error("Integer overflow");
            result += arg;
        }
        else {
            if (arg != 0 && result > std::numeric_limits<int>::max() / arg) throw std::overflow_error("Integer overflow");
            result *= arg;
        }
    }
    return result;
}

int Evaluate(std::istream& in) {
    try {
        return ParseExpression(in);
    }
    catch (...) {
        throw;
    }
}
