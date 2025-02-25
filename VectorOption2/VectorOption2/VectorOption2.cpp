#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <iomanip>
#include <numeric>

std::vector<double> ReadNumbers() {
    std::vector<double> numbers;
    std::string input;
    std::getline(std::cin, input);
    std::istringstream iss(input);
    double num;
    while (iss >> num) {
        numbers.push_back(num);
    }
    if (!iss.eof()) { // Ошибка при чтении
        std::cout << "ERROR" << std::endl;
        exit(0);
    }
    return numbers;
}

void ProcessNumbers(std::vector<double>& numbers) {
    if (numbers.empty()) return;
    double min_element = *std::min_element(numbers.begin(), numbers.end());
    for (double& num : numbers) {
        num *= min_element;
    }
}

void PrintSortedNumbers(const std::vector<double>& numbers) {
    std::vector<double> sorted_numbers = numbers;
    std::sort(sorted_numbers.begin(), sorted_numbers.end());
    std::cout << std::fixed << std::setprecision(3);
    for (const double num : sorted_numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<double> numbers = ReadNumbers();
    ProcessNumbers(numbers);
    PrintSortedNumbers(numbers);
    return 0;
}
