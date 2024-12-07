#include <vector>
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <string>

#define INPUT_PATH "inputs/4.txt"

typedef struct {
    std::unordered_set<std::string> winningSet;
    std::vector<std::string> myNumbers;
} ScratchCard;

typedef std::vector<ScratchCard> ParsedInput;

void parseInput(const char* filename, ParsedInput& inputVector) {
    std::ifstream file(filename);
    std::string line;

    while (getline(file, line)) {
        ScratchCard card;

        auto splitPoint = line.find('|');

        for (int i = 10; i < splitPoint; i += 3) {
            card.winningSet.insert(line.substr(i, 2));
        }

        for (int i = splitPoint + 2; i < line.size(); i += 3) {
            card.myNumbers.push_back(line.substr(i, 2));
        }

        inputVector.push_back(card);
    }
}

int getWinningNumberCount(ScratchCard& card) {
    int count = 0;

    for (auto num : card.myNumbers) {
        if (card.winningSet.find(num) != card.winningSet.end()) {
            count++;
        }
    }

    return count;
}

int solvePart1(ParsedInput& inputVector) {
    int sumOfPoints = 0;

    for (auto card : inputVector) {
        int points = 0;

        int winningCardCount = getWinningNumberCount(card);

        if (winningCardCount > 0) {
            ++points;

            for (int i = 1; i < winningCardCount; ++i) {
                points *= 2;
            }
        }

        sumOfPoints += points;
    }

    return sumOfPoints;
}

int solvePart2(ParsedInput& inputVector) {
    std::vector<int> copies(inputVector.size(), 1);

    int totalScratchCards = 0;

    for (int i = 0; i < inputVector.size(); ++i) {
        int matches = getWinningNumberCount(inputVector[i]);
        for (int j = 0; j < matches; ++j) {
            copies[i + j + 1] += copies[i];
        }
    }

    for (auto copyCount : copies) {
        totalScratchCards += copyCount;
    }

    return totalScratchCards;
}

int main() {
    ParsedInput inputVector;

    parseInput(INPUT_PATH, inputVector);

    int part1Solution = solvePart1(inputVector);

    std::cout << part1Solution << std::endl;
    
    int part2Solution = solvePart2(inputVector);

    std::cout << part2Solution << std::endl;
}