#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#define INPUT_PATH "inputs/6.txt"

typedef struct {
    std::vector<int> times;
    std::vector<int> distances;
} ParsedInput;

void parseInput(const char* filename, ParsedInput& inputStruct) {
    std::ifstream file(filename);
    std::string line;

    while (getline(file, line)) {
        if (line[0] == 'T') {
            for (int i = line.size() - 1; i >= 0; --i) {
                const size_t startIndex = line.rfind(' ', i) + 1;

                inputStruct.times.push_back(stoi(line.substr(startIndex, i - startIndex + 1)));
                i -= 6;
                if (inputStruct.times.size() >= 4) break;
            }
        } else {
            for (int i = line.size() - 1; i >= 0; --i) {
                const size_t startIndex = line.rfind(' ', i) + 1;

                inputStruct.distances.push_back(stoi(line.substr(startIndex, i - startIndex + 1)));
                i -= 6;
                if (inputStruct.distances.size() >= 4) break;
            }
        }
    }
}

int solvePart1(ParsedInput& parsedInput) {
    int leniencyProduct = 1;

    for (int i = 0; i < parsedInput.times.size(); ++i) {
        int currentTime = parsedInput.times[i];
        int currentRequiredDistance = parsedInput.distances[i];
        int leniency = 0;

        for (int j = 0; j < currentTime; ++j) {
            int currentAttempt = j * (currentTime - j);

            if (currentAttempt > currentRequiredDistance) {
                ++leniency;
            }
        }

        leniencyProduct *= leniency;
    }

    return leniencyProduct;
}


int main() {
    ParsedInput parsedInput;

    parseInput(INPUT_PATH, parsedInput);

    int part1Solution = solvePart1(parsedInput);

    std::cout << part1Solution << std::endl;
}