#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#define INPUT_FILE "inputs/3.txt"

typedef std::vector<std::string> ParsedInput;

void parseInput(const char* filename, ParsedInput& inputVector) {
    std::ifstream file(filename);
    std::string line;

    while (getline(file, line)) {
        inputVector.push_back(line);
    }
}

int isDigit(char c) {
    return c >= '0' && c <= '9';
}

int isSymbol(char c) {
    return c != '.' && !isDigit(c);
}

int isOutOfBounds(int row, int col, int rows, int cols) {
    return row < 0 || row >= rows || col < 0 || col >= cols;
}

int isValidPart(std::vector<std::vector<int>>& directions, ParsedInput& inputVector, int row, int col, int len) {
    for (int i = 0; i < 3; ++i) {
        int offsetRow = row + directions[i][0];
        int offsetCol = col + directions[i][1];

        if (!isOutOfBounds(offsetRow, offsetCol, inputVector.size(), inputVector[row].size())) {
            if (isSymbol(inputVector[offsetRow][offsetCol])) {
                return 1;
            }
        }
    }

    for (int i = 0; i < len; ++i) {
        for (int j = 6; j < directions.size(); ++j) {
            int offsetRow = row + directions[j][0];
            int offsetCol = col + directions[j][1] + i;

            if (!isOutOfBounds(offsetRow, offsetCol, inputVector.size(), inputVector[row].size())) {
                if (isSymbol(inputVector[offsetRow][offsetCol])) {
                    return 1;
                }
            }
        }
    }

    for (int i = 3; i < 6; ++i) {
        int offsetRow = row + directions[i][0];
        int offsetCol = col + directions[i][1] + len - 1;

        if (!isOutOfBounds(offsetRow, offsetCol, inputVector.size(), inputVector[row].size())) {
            if (isSymbol(inputVector[offsetRow][offsetCol])) {
                return 1;
            }
        }
    }

    return 0;
}

int solvePart1(ParsedInput& inputVector) {
    int sumOfValidPartNumbers = 0;

    std::vector<std::vector<int>> directions = {
        { 0, -1}, // left
        {-1, -1}, // up-left
        { 1, -1}, // down-left
        { 0,  1}, // right
        {-1,  1}, // up-right
        { 1,  1}, // down-right
        { 1,  0}, // down
        {-1,  0}, // up
    };

    for (int row = 0; row < inputVector.size(); ++row) {
        for (int col = 0; col < inputVector[row].size(); ++col) {
            if (isDigit(inputVector[row][col])) {
                int len = 1;

                while (isDigit(inputVector[row][col + len])) {
                    len++;
                }

                if (isValidPart(directions, inputVector, row, col, len)) {
                    std::string foundNumber = inputVector[row].substr(col, len);

                    int partNumber = stoi(foundNumber);
                    sumOfValidPartNumbers += partNumber;
                }

                col += len - 1;
            }
        }
    }

    return sumOfValidPartNumbers;
}

int main() {
    ParsedInput inputVector;

    parseInput(INPUT_FILE, inputVector);

    int part1Solution = solvePart1(inputVector);

    std::cout << part1Solution << std::endl;
}