#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

#define INPUT_PATH "inputs/6.txt"

typedef struct {
    std::vector<std::string> times;
    std::vector<std::string> distances;
} ParsedInput;

void parseInput(const char* filename, ParsedInput& inputStruct) {
    std::ifstream file(filename);
    std::string line;

    while (getline(file, line)) {
        if (line[0] == 'T') {
            for (int i = line.size() - 1; i >= 0; --i) {
                const size_t startIndex = line.rfind(' ', i) + 1;

                inputStruct.times.push_back(line.substr(startIndex, i - startIndex + 1));
                i -= 6;
                if (inputStruct.times.size() >= 4) break;
            }
        } else {
            for (int i = line.size() - 1; i >= 0; --i) {
                const size_t startIndex = line.rfind(' ', i) + 1;

                inputStruct.distances.push_back(line.substr(startIndex, i - startIndex + 1));
                i -= 6;
                if (inputStruct.distances.size() >= 4) break;
            }
        }
    }
}

long long concatStringsToLong(std::vector<std::string> nums) {
    std::string concatenaded = "";

    for (auto num : nums) {
        concatenaded = num + concatenaded;
    }

    return stoll(concatenaded);
}

long long getLeniency(long long time, long long distance) {
    long double discriminant = static_cast<long double>(time) * time - 4 * distance;

    if (discriminant < 0) {
        return 0;
    }

    long double discriminantSqrt = std::sqrt(discriminant);

    long double x1 = (time - discriminantSqrt) / 2.0l;
    long double x2 = (time + discriminantSqrt) / 2.0l;
    
    long double lowerBound = std::ceil(x1);
    long double upperBound = std::floor(x2);

    if (lowerBound * upperBound == static_cast<long double>(distance)) {
        ++lowerBound;
        --upperBound;
    }

    if (lowerBound <= upperBound) {
        return upperBound - lowerBound + 1;
    }

    return 0;
}

long long solvePart1(ParsedInput& parsedInput) {
    long long leniencyProduct = 1;

    for (int i = 0; i < parsedInput.times.size(); ++i) {
        long long time = stoll(parsedInput.times[i]);
        long long distance = stoll(parsedInput.distances[i]);
        
        long long leniencies = getLeniency(time, distance);
        
        leniencyProduct *= leniencies;
    }

    return leniencyProduct;
}

int solvePart2(ParsedInput& parsedInput) {
    long long time = concatStringsToLong(parsedInput.times);
    long long distance = concatStringsToLong(parsedInput.distances);

    return getLeniency(time, distance);
}

int main() {
    ParsedInput parsedInput;

    parseInput(INPUT_PATH, parsedInput);

    int part1Solution = solvePart1(parsedInput);

    std::cout << part1Solution << std::endl;

    int part2Solution = solvePart2(parsedInput);

    std::cout << part2Solution << std::endl;
}