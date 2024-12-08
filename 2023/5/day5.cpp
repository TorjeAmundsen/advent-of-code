#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <climits>

#define INPUT_PATH "inputs/5.txt"

typedef struct {
    long long destinationStart;
    long long sourceStart;
    long long range;
} MapEntry;

typedef std::vector<MapEntry> AlmanacCategory;

typedef std::unordered_map<std::string, AlmanacCategory> Almanac;

typedef struct {
    std::vector<long long> seeds;
    Almanac almanac;
} ParsedInput;

std::string getMapKey(std::string title) {    
    size_t startIndex = title.find("to-") + 3;
    size_t endIndex = title.find(' ', startIndex);

    size_t len = endIndex - startIndex;

    std::string mapKey = title.substr(startIndex, len);

    return mapKey;
}

int isDigit(char c) {
    return c >= '0' && c <= '9';
}

void parseInput(const char* filename, ParsedInput& parsedInput) {
    std::ifstream file(filename);
    std::string line;

    if (getline(file, line)) {
        size_t startIndex = line.find(' ') + 1;

        std::stringstream seedStream(line.substr(startIndex, line.size() - startIndex));
        std::string seed;
        while (getline(seedStream, seed, ' ')) {
            parsedInput.seeds.push_back(stoll(seed));
        }
    }

    std::string currentMapKey;

    while (getline(file, line)) {
        if (line.size() == 0) continue;

        if (!isDigit(line[0])) {
            currentMapKey = getMapKey(line);
        } else {
            AlmanacCategory mapVector;
            std::stringstream stream(line);
            std::string numString;

            std::vector<long long> nums;

            while (getline(stream, numString, ' ')) {
                nums.push_back(stoll(numString));
            }

            MapEntry entry = {
                nums[0],
                nums[1],
                nums[2],
            };

            parsedInput.almanac[currentMapKey].push_back(entry);

            std::cout << "Added entry to almanac[\"" << currentMapKey << "\"]\n";
        }
    }
}

// optimization: make map of seed values to directly correspond to the almanac entries
// rather than checking for a range every time
// collapse the range beforehand based on the seed inputs to save iterations

long long solvePart1(ParsedInput& parsedInput) {
    long long lowestLocationNumber = LLONG_MAX;
    std::vector<std::string> keys = {
        "soil",
        "fertilizer",
        "water",
        "light",
        "temperature",
        "humidity",
        "location",
    };

    int currentKeyIndex = 0;

    for (auto seed : parsedInput.seeds) {
        int currentNum = seed;
        for (auto entry : parsedInput.almanac[keys[currentKeyIndex]]) {
            if (seed >= entry.sourceStart && seed < entry.sourceStart + entry.range) {
                long long offset = entry.destinationStart - entry.sourceStart;
                currentNum = seed + offset;
            }
        }
    }

    return lowestLocationNumber;
}

int main() {
    ParsedInput parsedInput;
    
    parseInput(INPUT_PATH, parsedInput);

    auto test = solvePart1(parsedInput);
}