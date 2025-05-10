#include "ParseExpression.h"
#include <iostream>
#include <sstream>

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream in(line);
        try {
            std::cout << Evaluate(in) << std::endl;
        }
        catch (...) {
            std::cout << "ERROR" << std::endl;
        }
    }
    return 0;
}