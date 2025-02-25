#include <iostream>
#include <string>
#include <fstream>
#include <optional>

struct Args
{
    std::string inputFileName;
    std::string findWord;
};

std::fstream OpeningInpuFile(const Args& args)
{
    std::fstream input(args.inputFileName);
    if (!input.is_open())
    {
        std::cerr << "Error: Couldn't open the input file for reading." << std::endl;
    }
    return input;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        return std::nullopt;
    }
    Args args;
    args.inputFileName = argv[1];
    args.findWord = argv[2];
    return args;
}

void FindText(std::fstream& input, const Args& args)
{
    std::string line;
    int numberOfLine = 0; //Номер строки
    bool found = false;

    while (getline(input, line))
    {
        numberOfLine++;
        if ((line.find(args.findWord) != std::string::npos) && (line.find(args.findWord) != (-1)))
        {
            found = true;
            std::cout << numberOfLine << std::endl;
        }
    }

    if (!found)
    {
        std::cout << "Text not found" << std::endl;
        exit(1);
    }
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");

    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }

    auto input = OpeningInpuFile(*args);

    FindText(input, *args);

    input.close();
    return 0;
}
