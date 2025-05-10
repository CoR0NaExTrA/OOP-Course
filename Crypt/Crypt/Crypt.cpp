#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

// Функция перемешивания битов при шифровании
uint8_t MixBits(uint8_t byte) 
{
    return ((byte & 0b10000000) >> 0) |
        ((byte & 0b01000000) >> 2) |
        ((byte & 0b00100000) << 3) |
        ((byte & 0b00010000) >> 1) |
        ((byte & 0b00001000) << 2) |
        ((byte & 0b00000100) >> 1) |
        ((byte & 0b00000010) << 1) |
        ((byte & 0b00000001) << 4);
}

// Функция обратного перемешивания битов при дешифровании
uint8_t UnmixBits(uint8_t byte) 
{
    return ((byte & 0b10000000) >> 0) |
        ((byte & 0b01000000) << 2) |
        ((byte & 0b00100000) >> 3) |
        ((byte & 0b00010000) << 1) |
        ((byte & 0b00001000) >> 2) |
        ((byte & 0b00000100) << 1) |
        ((byte & 0b00000010) >> 1) |
        ((byte & 0b00000001) << 4);
}

void ProcessFile(const std::string& mode, const std::string& inputFile, const std::string& outputFile, int key)
{
    if (key < 0 || key > 255) 
    {
        throw std::invalid_argument("Key must be in range 0-255");
    }

    std::ifstream in(inputFile, std::ios::binary);
    if (!in) 
    {
        throw std::runtime_error("Error opening input file");
    }

    std::ofstream out(outputFile, std::ios::binary);
    if (!out) 
    {
        throw std::runtime_error("Error opening output file");
    }

    char byte;
    while (in.get(byte)) 
    {
        uint8_t transformedByte = static_cast<uint8_t>(byte) ^ key;
        transformedByte = (mode == "crypt") ? MixBits(transformedByte) : UnmixBits(transformedByte);
        out.put(static_cast<char>(transformedByte));
    }
}

int main(int argc, char* argv[]) 
{
    if (argc != 5) 
    {
        std::cerr << "Usage: crypt.exe <mode> <input file> <output file> <key>" << std::endl;
        return 1;
    }

    std::string mode = argv[1];
    if (mode != "crypt" && mode != "decrypt") 
    {
        std::cerr << "Invalid mode. Use 'crypt' or 'decrypt'." << std::endl;
        return 1;
    }

    std::string inputFile = argv[2];
    std::string outputFile = argv[3];

    try 
    {
        int key = std::stoi(argv[4]);
        ProcessFile(mode, inputFile, outputFile, key);
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
