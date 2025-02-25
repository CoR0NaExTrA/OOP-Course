#include <iostream>
#include <optional>
#include <string>

int BIT_COUNT = 8;


//todo: Исправить форматирование, обернуть в try..catch stoi, разобраться с реверсом битов, пограничнные значения и сделать тесты
struct Args 
{
    int startNumber;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: Enter a single number as an argument." << std::endl;
        return std::nullopt;
    }
    Args args;
    try
    {
        args.startNumber = std::stoi(argv[1]);
        return args;
        if (args.startNumber < 0 || args.startNumber > 255)
        {
            return std::nullopt;
        }
    }
    catch (const std::string& err)
    {
        std::cerr << err << std::endl;
        return std::nullopt;
    }
}

int ReverseBits(const Args& args) 
{
    int reversed = 0;
    int number = args.startNumber;

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

    std::cout << "Начальное число: " << args->startNumber << std::endl;

    int num = ReverseBits(*args);

    std::cout << "Преобразованное число: " << num << std::endl;

    return 0;
}