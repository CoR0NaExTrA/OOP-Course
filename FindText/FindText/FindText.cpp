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

// Проверка, является ли символ границей слова (не буква)
bool IsWordBoundary(char ch)
{
    return !std::isalpha(static_cast<unsigned char>(ch));
}

void FindText(std::fstream& input, const Args& args)
{
    std::string line;
    int number_of_line = 0; //Номер строки
    bool found = false;

    while (getline(input, line))
    {
        number_of_line++;
        size_t pos = 0;
        while ((pos = line.find(args.find_word, pos)) != std::string::npos)
        {
            bool is_start_boundary = (pos == 0) || IsWordBoundary(line[pos - 1]);
            bool is_end_boundary = (pos + args.find_word.length() == line.length()) ||
                IsWordBoundary(line[pos + args.find_word.length()]);

            if (is_start_boundary && is_end_boundary)
            {
                std::cout << number_of_line << std::endl;
                found = true;
                break;
            }

            pos += args.find_word.length();
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

    std::fstream input(args->inputFileName);
    if (!input.is_open())
    {
        std::cerr << "Error: Couldn't open the input file for reading." << std::endl;
        return 1;
    }

    FindText(input, *args);

    input.close();
    return 0;
}
