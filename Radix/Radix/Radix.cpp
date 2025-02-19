#include <iostream>
#include <string>
#include <cmath>
#include <cctype>
#include <stdexcept>
#include <limits>

// Функция для перевода строки в число
int StringToInt(const std::string& str, int radix, bool& wasError) {
    if (radix < 2 || radix > 36) {
        wasError = true;
        return 0;
    }

    int result = 0;
    bool isNegative = false;
    size_t start = 0;

    // Обработка отрицательных чисел
    if (str[0] == '-') {
        isNegative = true;
        start = 1;
    }

    for (size_t i = start; i < str.length(); i++) {
        char c = toupper(str[i]);
        int digit;

        if (isdigit(c)) {
            digit = c - '0';
        }
        else if (isalpha(c)) {
            digit = c - 'A' + 10;
        }
        else {
            wasError = true;
            return 0;
        }

        if (digit >= radix) {
            wasError = true;
            return 0;
        }

        // Проверка на переполнение
        if (result > (std::numeric_limits<int>::max() - digit) / radix) {
            wasError = true;
            return 0;
        }

        result = result * radix + digit;
    }

    return isNegative ? -result : result;
}

std::string IntToString(int n, int radix, bool& wasError) {
    if (radix < 2 || radix > 36) {
        wasError = true;
        return "";
    }

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
    if (argc != 4) {
        std::cerr << "Error: Invalid number of arguments.\n";
        return 1;
    }

    int sourceRadix = std::stoi(argv[1]);
    int destRadix = std::stoi(argv[2]);
    std::string value = argv[3];

    bool wasError = false;

    int decimalValue = StringToInt(value, sourceRadix, wasError);
    if (wasError) {
        std::cerr << "Error: Invalid number or base in the input.\n";
        return 1;
    }

    std::string result = IntToString(decimalValue, destRadix, wasError);
    if (wasError) {
        std::cerr << "Error: Invalid number or base in the output.\n";
        return 1;
    }

    std::cout << result << "\n";
    return 0;
}