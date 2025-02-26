#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <iterator>

std::set<int> GeneratePrimeNumbersSet(int upperBound) {
    if (upperBound < 2) {
        return {};
    }

    std::vector<bool> isPrime(upperBound + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= upperBound; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= upperBound; j += i) {
                isPrime[j] = false;
            }
        }
    }

    std::set<int> primes;
    for (int i = 2; i <= upperBound; ++i) {
        if (isPrime[i]) {
            primes.insert(i);
        }
    }

    return primes;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <upperBound>" << std::endl;
        return 1;
    }

    int upperBound = std::atoi(argv[1]);
    if (upperBound <= 0 || upperBound > 100000000) {
        std::cerr << "Error: upperBound must be between 1 and 100000000." << std::endl;
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::set<int> primes = GeneratePrimeNumbersSet(upperBound);
    auto end = std::chrono::high_resolution_clock::now();

    std::ofstream outFile("primes.txt");
    if (!outFile) {
        std::cerr << "Error: Cannot open output file." << std::endl;
        return 1;
    }

    std::copy(primes.begin(), primes.end(), std::ostream_iterator<int>(outFile, " "));
    outFile << std::endl;
    outFile.close();

    std::chrono::duration<double> elapsed = end - start;
    std::cerr << "Execution time: " << elapsed.count() << " seconds." << std::endl;

    return 0;
}