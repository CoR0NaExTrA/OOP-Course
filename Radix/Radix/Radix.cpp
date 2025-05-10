#include <iostream>
#include <string>
#include <cmath>
#include <cctype>
#include <stdexcept>
#include <limits>
#include <optional>

struct Args {
    int sourceRadix;
    int destRadix;
    std::string value;
};

std::optional<Args> ParseArgs(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Error: Invalid number of arguments.\n";
        return std::nullopt;
    }

    Args args;

    try {
        args.sourceRadix = std::stoi(argv[1]);
        args.destRadix = std::stoi(argv[2]);
        args.value = argv[3];
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return std::nullopt;
    }
    return args;
}

int CharToDigit(char c, int radix) {
    int digit = isdigit(c) ? c - '0' : toupper(c) - 'A' + 10;
    if (digit < 0 || digit >= radix) {
        throw std::invalid_argument("Invalid character in number");
    }
    return digit;
}

void CheckOverflow(int result, int digit, int radix) {
    if (result > (std::numeric_limits<int>::max() - digit) / radix) {
        throw std::overflow_error("Integer overflow");
    }
}

void CheckRadix(int radix)
{
    if (radix < 2 || radix > 36) {
        throw std::invalid_argument("Invalid radix");
    }
}

int StringToInt(const std::string& str, int radix) {
    CheckRadix(radix);

    int result = 0;
    size_t start = (str[0] == '-') ? 1 : 0;
    bool isNegative = (start == 1);

    for (size_t i = start; i < str.length(); i++) {
        int digit = CharToDigit(str[i], radix);
        CheckOverflow(result, digit, radix);
        result = result * radix + digit;
    }

    return isNegative ? -result : result;
}

std::string IntToString(int n, int radix) {
    CheckRadix(radix);

    if (n == 0) {
        return "0";
    }

    bool isNegative = (n < 0);
    unsigned int absValue = static_cast<unsigned int>(isNegative ? -(n + 1) : n) + (isNegative ? 1 : 0);

    std::string result;

    while (absValue > 0) {
        int remainder = absValue % radix;
        char c = (remainder < 10) ? '0' + remainder : 'A' + (remainder - 10);
        result = c + result;
        absValue /= radix;
    }

    if (isNegative) {
        result = "-" + result;
    }

    return result;
}

int main(int argc, char* argv[]) {
    auto args = ParseArgs(argc, argv);

    try {
        int decimalValue = StringToInt(args->value, args->sourceRadix);
        std::string result = IntToString(decimalValue, args->destRadix);

        std::cout << result << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
