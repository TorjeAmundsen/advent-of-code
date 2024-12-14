#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#define INPUT_FILE "inputs/3.txt"

typedef std::vector<std::string> ParsedInput;

const std::vector<std::vector<int>> DIRECTIONS = {
    { 0, -1}, // left
    {-1, -1}, // up-left
    { 1, -1}, // down-left
    { 0,  1}, // right
    {-1,  1}, // up-right
    { 1,  1}, // down-right
    { 1,  0}, // down
    {-1,  0}, // up
};

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

int isValidPart(ParsedInput& inputVector, int row, int col, int len) {
    for (int i = 0; i < 3; ++i) {
        int offsetRow = row + DIRECTIONS[i][0];
        int offsetCol = col + DIRECTIONS[i][1];

        if (isOutOfBounds(offsetRow, offsetCol, inputVector.size(), inputVector[row].size())) {
            continue;
        }

        if (isSymbol(inputVector[offsetRow][offsetCol])) {
            return 1;
        }
    }

    for (int i = 0; i < len; ++i) {
        for (int j = 6; j < DIRECTIONS.size(); ++j) {
            int offsetRow = row + DIRECTIONS[j][0];
            int offsetCol = col + DIRECTIONS[j][1] + i;

            if (isOutOfBounds(offsetRow, offsetCol, inputVector.size(), inputVector[row].size())) {
                continue;
            }

            if (isSymbol(inputVector[offsetRow][offsetCol])) {
                return 1;
            }
        }
    }

    for (int i = 3; i < 6; ++i) {
        int offsetRow = row + DIRECTIONS[i][0];
        int offsetCol = col + DIRECTIONS[i][1] + len - 1;

        if (isOutOfBounds(offsetRow, offsetCol, inputVector.size(), inputVector[row].size())) {
            continue;
        }

        if (isSymbol(inputVector[offsetRow][offsetCol])) {
            return 1;
        }
    }

    return 0;
}

int solvePart1(ParsedInput& inputVector) {
    int sumOfValidPartNumbers = 0;

    for (int row = 0; row < inputVector.size(); ++row) {
        for (int col = 0; col < inputVector[row].size(); ++col) {
            if (isDigit(inputVector[row][col])) {
                int len = 1;

                while (isDigit(inputVector[row][col + len])) {
                    len++;
                }

                if (isValidPart(inputVector, row, col, len)) {
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

int gearRatio(ParsedInput& inputVector, int row, int col) {
    std::vector<std::vector<int>> checked = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0},
    };

    std::vector<int> foundNums;

    for (int i = 0; i < DIRECTIONS.size(); ++i) {
        int rowOffset = DIRECTIONS[i][0];
        int colOffset = DIRECTIONS[i][1];

        if (checked[1 + rowOffset][1 + colOffset]) {
            continue;
        }
        checked[1 + rowOffset][1 + colOffset] = 1;

        int offsetRow = row + rowOffset;
        int offsetCol = col + colOffset;
        
        if (
            isOutOfBounds(offsetRow, offsetCol, inputVector.size(), inputVector[row].size())
            || !isDigit(inputVector[offsetRow][offsetCol])
        ) {
            continue;
        }

        int leftGrow = 0;
        int rightGrow = 0;

        while (
            !isOutOfBounds(offsetRow, offsetCol - leftGrow - 1, inputVector.size(), inputVector[row].size())
            && isDigit(inputVector[offsetRow][offsetCol - leftGrow - 1])
        ) {
            leftGrow++;

            if (!isOutOfBounds(1 + rowOffset, 1 + colOffset - leftGrow, 3, 3)) {
                checked[1 + rowOffset][1 + colOffset - leftGrow] = 1;
            }
        }
        
        while (
            !isOutOfBounds(offsetRow, offsetCol + rightGrow + 1, inputVector.size(), inputVector[row].size())
            && isDigit(inputVector[offsetRow][offsetCol + rightGrow + 1])
        ) {
            rightGrow++;

            if (!isOutOfBounds(1 + rowOffset, 1 + colOffset + rightGrow, 3, 3)) {
                checked[1 + rowOffset][1 + colOffset + rightGrow] = 1;
            }
        }

        int len = leftGrow + rightGrow + 1;

        std::string foundNumberString = inputVector[offsetRow].substr(offsetCol - leftGrow, len);

        int foundNumber = stoi(foundNumberString);
        foundNums.push_back(foundNumber);
    }

    if (foundNums.size() == 2) {
        return foundNums[0] * foundNums[1];
    }

    return 0;
}

int solvePart2(ParsedInput& inputVector) {
    int gearRatioSum = 0;

    for (int row = 0; row < inputVector.size(); ++row) {
        for (int col = 0; col < inputVector[col].size(); ++col) {
            if (inputVector[row][col] != '*') {
                continue;
            }

            gearRatioSum += gearRatio(inputVector, row, col);
        }
    }

    return gearRatioSum;
}

int main() {
    ParsedInput inputVector;

    parseInput(INPUT_FILE, inputVector);

    int part1Solution = solvePart1(inputVector);

    std::cout << part1Solution << std::endl;

    int part2Solution = solvePart2(inputVector);

    std::cout << part2Solution << std::endl;
}