#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

#define INPUT_PATH "inputs/2.txt"

typedef struct {
    char color;
    int count;
} CubeSet;

typedef std::vector<std::vector<CubeSet>> ParsedInput;

void printVector(std::vector<std::string>& vector) {
    for (auto e : vector) {
        std::cout << e;
    }
    std::cout << std::endl;
}

int isDigit(char c) {
    return c >= '0' && c <= '9';
}

int twoDigitsToInt(char first, char second) {
    return ((first - '0') * 10) + second - '0';
}

int getCubeSetsFromHand(std::vector<CubeSet>& vector, std::string& string) {
    for (int i = 0; i < string.size(); ++i) {
        if (isDigit(string[i])) {
            int count;
            CubeSet set;
            if (isDigit(string[i + 1])) {
                count = twoDigitsToInt(string[i], string[i + 1]);
                ++i;
            } else {
                count = string[i] - '0';
            }
            i += 2;
            
            set = { string[i], count };
            vector.push_back(set);
        }
    }
}

void readFile(const char* filename, ParsedInput& matrix) {
    std::ifstream file(filename);
    std::string line;

    while (getline(file, line)) {
        int startIndex = 5;

        for (startIndex; startIndex < line.size(); ++startIndex) {
            if (line[startIndex] == ':') {
                startIndex ++;
                break;
            }
        }

        std::vector<CubeSet> cubesetVector;

        std::string hand;
        std::stringstream game(line.substr(startIndex));

        while (getline(game, hand, ';')) {
            getCubeSetsFromHand(cubesetVector, hand);
        }

        matrix.push_back(cubesetVector);
    }
}

int solvePart1(ParsedInput& matrix) {
    int sumOfIds = 0;

    for (int i = 0; i < matrix.size(); ++i) {
        int possible = 1;

        for (auto set : matrix[i]) {
            if (set.color == 'r' && set.count > 12) {
                possible = 0;
                break;
            }

            if (set.color == 'g' && set.count > 13) {
                possible = 0;
                break;
            }

            if (set.color == 'b' && set.count > 14) {
                possible = 0;
                break;
            }
        }

        if (possible) {
            sumOfIds += i + 1;
        }
    }

    return sumOfIds;
}

int solvePart2(ParsedInput matrix) {
    int powerSum = 0;

    for (auto vec : matrix) {
        std::unordered_map<char, int> map = {
            {'r', 0},
            {'g', 0},
            {'b', 0},
        };

        for (auto set : vec) {
            if (set.count > map[set.color]) {
                map[set.color] = set.count;
            }
        }

        powerSum += map['r'] * map['g'] * map['b'];
    }

    return powerSum;
}

int main() {
    ParsedInput matrix;

    readFile(INPUT_PATH, matrix);

    int part1Solution = solvePart1(matrix);

    std::cout << part1Solution << std::endl;

    int part2Solution = solvePart2(matrix);

    std::cout << part2Solution << std::endl;
}