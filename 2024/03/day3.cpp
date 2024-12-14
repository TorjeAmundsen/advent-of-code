#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>

#define INPUT_PATH "inputs/3.txt"

void parseInput(const char* filename, std::vector<std::string>& inputVector) {
    std::ifstream file(filename);
    std::string line;

    while (getline(file, line)) {
        inputVector.push_back(line);
    }
}

// mul(571,436)

int solvePart1(std::vector<std::string>& inputVector) {
    std::regex regex("mul\\(\\d{1,3},\\d{1,3}\\)");

    int sumOfValidMultiplications = 0;

    for (auto line : inputVector) {
        auto matchedBegin = std::sregex_iterator(line.begin(), line.end(), regex);
        auto matchedEnd = std::sregex_iterator();

        for (auto i = matchedBegin; i != matchedEnd; ++i) {
            std::string match = (*i).str();
            size_t commaPosition = match.find(',', 5);
            int firstNum = stoi(match.substr(4, commaPosition - 4));
            int secondNum = stoi(match.substr(commaPosition + 1, match.size() - commaPosition - 1));

            int product = firstNum * secondNum;

            sumOfValidMultiplications += product;
        }
    }

    return sumOfValidMultiplications;
}

int solvePart2(std::vector<std::string>& inputVector) {
    std::regex regex("(mul\\(\\d{1,3},\\d{1,3}\\))|(do\\(\\))|(don't\\(\\))");

    int sumOfValidMultiplications = 0;

    int doing = 1;
    
    for (auto line : inputVector) {
        

        auto matchedBegin = std::sregex_iterator(line.begin(), line.end(), regex);
        auto matchedEnd = std::sregex_iterator();

        for (auto i = matchedBegin; i != matchedEnd; ++i) {
            

            std::string match = (*i).str();

            if (match[2] == '(') {
                doing = 1;
            } else if (match[2] == 'n') {
                doing = 0;
            } else if (doing) {
                size_t commaPosition = match.find(',', 5);
                int firstNum = stoi(match.substr(4, commaPosition - 4));
                int secondNum = stoi(match.substr(commaPosition + 1, match.size() - commaPosition - 1));

                int product = firstNum * secondNum;

                sumOfValidMultiplications += product;
            }
        }
    }

    return sumOfValidMultiplications;
}

int main() {
    std::vector<std::string> inputVector;

    parseInput(INPUT_PATH, inputVector);

    int part1Solution = solvePart1(inputVector);

    std::cout << part1Solution << std::endl;

    int part2Solution = solvePart2(inputVector);

    std::cout << part2Solution << std::endl;
}