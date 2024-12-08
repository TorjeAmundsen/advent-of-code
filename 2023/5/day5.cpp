#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

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
    size_t startIndex = title.find("to-") + 1;
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
            parsedInput.seeds.push_back(stol(seed));
        }
    }

    AlmanacCategory* currentMapVector;

    while (getline(file, line)) {
        if (line.size() == 0) continue;

        if (!isDigit(line[0])) {
            std::string mapKey = getMapKey(line);
            AlmanacCategory mapVector;
            parsedInput.almanac[mapKey] = mapVector;
            currentMapVector = &mapVector;
        } else {
            std::stringstream stream(line);
            std::string numString;

            std::vector<long long> nums;

            while (getline(stream, numString, ' ')) {
                nums.push_back(stol(numString));
            }

            MapEntry entry = {
                nums[0],
                nums[1],
                nums[2],
            };

            currentMapVector->push_back(entry);
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

    for (auto key : keys) {
        std::cout << key << " map:\n";

        std::cout << (parsedInput.almanac.find(key) != parsedInput.almanac.end()) << std::endl;

        for (auto entry : parsedInput.almanac[key]) {
            std::cout << "dest start: " << entry.destinationStart;
            std::cout << "source start: " << entry.sourceStart;
            std::cout << "range: " << entry.range << std::endl;;
        }
    }

    return lowestLocationNumber;
}

int main() {
    ParsedInput parsedInput;
    
    parseInput(INPUT_PATH, parsedInput);

    auto test = solvePart1(parsedInput);
}