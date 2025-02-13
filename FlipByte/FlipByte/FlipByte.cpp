#include <iostream>
#include <optional>
#include <string>

int BIT_COUNT = 8;

struct Args 
{
    int start_number;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Ошибка: введите одно число в качестве аргумента." << std::endl;
        return std::nullopt;
    }
    Args args;
    args.start_number = std::stoi(argv[1]);
    return args;
}

int ReverseBits(const Args& args) {
    int reversed = 0;
    int number = args.start_number;

    for (int i = 0; i < BIT_COUNT; i++)
    {
        reversed <<= 1;
        reversed |= (number & 1);
        number >>= 1;
    }

    return reversed;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");

    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }

    std::cout << "Начальное число: " << args->start_number << std::endl;

    int num = ReverseBits(*args);

    std::cout << "Преобразованное число: " << num << std::endl;

    return 0;
}