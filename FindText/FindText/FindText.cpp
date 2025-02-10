#include <iostream>
#include <string>
#include <fstream>
#include <optional>

struct Args 
{
    std::string inputFileName;
    std::string find_word;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        return std::nullopt;
    }
    Args args;
    args.inputFileName = argv[1];
    args.find_word = argv[2];
    return args;
}

void FindText(std::fstream& input, std::optional<Args> args)
{
    std::string line;
    int number_of_line = 0; //Номер строки

    std::cout << "Ваше слово " << args->find_word << " найдено в строках: " << std::endl;
    while (getline(input, line))
    {
        number_of_line += 1;
        if ((line.find(args->find_word) != std::string::npos) && (line.find(args->find_word) != (-1)))
        {
            std::cout << number_of_line << std::endl;
        }
    }
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");
    auto args = ParseArgs(argc, argv);
    std::fstream input;
    input.open(args -> inputFileName);
    if (!input.is_open())
    {
        std::cerr << "Error: Couldn't open the input file for reading." << std::endl;
        return 1;
    }

    FindText(input, args);

    return 0;
}
