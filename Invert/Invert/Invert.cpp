#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>

const int N = 3;

double FindDeterminant2d(double source[2][2]) {
    return (source[0][0] * source[1][1] - source[1][0] * source[0][1]);
}

double FindDeterminant3d(double source[N][N]) {
    return (source[0][0] * source[1][1] * source[2][2] +
        source[2][0] * source[0][1] * source[1][2] +
        source[1][0] * source[2][1] * source[0][2] -
        source[2][0] * source[1][1] * source[0][2] -
        source[0][0] * source[2][1] * source[1][2] -
        source[1][0] * source[0][1] * source[2][2]);
}

void FindMinor(double source[N][N], double minor[2][2], int row, int col) {
    int iMinor = 0;
    for (int i = 0; i < N; i++) {
        if (i == row) continue;
        int jMinor = 0;
        for (int j = 0; j < N; j++) {
            if (j == col) continue;
            minor[iMinor][jMinor] = source[i][j];
            jMinor++;
        }
        iMinor++;
    }
}

bool InvertMatrix(double source[N][N], double result[N][N]) {
    double minorMatrix[N][N];
    double temp[2][2];
    double det = FindDeterminant3d(source);

    if (det == 0) {
        std::cout << "Non-invertible" << std::endl;
        return false;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            FindMinor(source, temp, i, j);
            minorMatrix[i][j] = FindDeterminant2d(temp) * ((i + j) % 2 == 0 ? 1 : -1);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = minorMatrix[j][i] / det;
        }
    }
    return true;
}

bool ReadMatrix(std::istream& in, double matrix[N][N]) {
    std::string line;
    for (int i = 0; i < N; i++) {
        if (!std::getline(in, line)) return false;
        std::istringstream iss(line);
        for (int j = 0; j < N; j++) {
            if (!(iss >> matrix[i][j])) return false;
        }
    }
    return true;
}

void PrintMatrix(double matrix[N][N]) {
    std::cout << std::fixed << std::setprecision(3);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    double matrix[N][N];

    if (argc == 2) {
        std::string arg = argv[1];
        if (arg == "-h") {
            std::cout << "Usage: invert.exe [file]" << std::endl;
            return 0;
        }

        std::ifstream file(arg);
        if (!file || !ReadMatrix(file, matrix)) {
            std::cout << "Invalid matrix format" << std::endl;
            return 1;
        }
    }
    else {
        if (!ReadMatrix(std::cin, matrix)) {
            std::cout << "Invalid matrix format" << std::endl;
            return 1;
        }
    }

    double result[N][N];
    if (InvertMatrix(matrix, result)) {
        PrintMatrix(result);
    }
    return 0;
}
