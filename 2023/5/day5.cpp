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
        }
    }
}

// optimization: make map of seed values to directly correspond to the almanac entries
// rather than checking for a range every time
// collapse the range beforehand based on the seed inputs to save iterations

// i may be speaking by means of my own rectum here lol

long long findMappedLocation(Almanac& almanac, std::vector<std::string>& keys, int keyIndex, long long currentVal) {
    if (keyIndex >= keys.size()) return currentVal;

    for (auto entry : almanac[keys[keyIndex]]) {
        if (currentVal >= entry.sourceStart && currentVal < entry.sourceStart + entry.range) {
            long long offset = entry.destinationStart - entry.sourceStart;
            long long newVal = currentVal + offset;

            return findMappedLocation(almanac, keys, keyIndex + 1, newVal);
        }
    }

    return findMappedLocation(almanac, keys, keyIndex + 1, currentVal);
}

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

    for (auto seed : parsedInput.seeds) {
        long long mappedLocation = findMappedLocation(parsedInput.almanac, keys, 0, seed);

        if (mappedLocation < lowestLocationNumber) {
            lowestLocationNumber = mappedLocation;
        }
    }

    return lowestLocationNumber;
}

std::vector<std::pair<long long, long long>> getSeedRanges(std::vector<long long> seeds) {
    std::vector<std::pair<long long, long long>> pairVector;

    for (int i = 0; i < seeds.size(); i += 2) {
        std::pair<long long, long long> pair(seeds[i], seeds[i + 1]);

        pairVector.push_back(pair);
    }

    return pairVector;
}

long long solvePart2(ParsedInput& parsedInput) {
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

    auto seedRanges = getSeedRanges(parsedInput.seeds);
    int scannedPairs = 0;
    for (auto pair : seedRanges) {
        for (long long seed = pair.first; seed < pair.first + pair.second; ++seed) {
            long long mappedLocation = findMappedLocation(parsedInput.almanac, keys, 0, seed);

            if (mappedLocation < lowestLocationNumber) {
                lowestLocationNumber = mappedLocation;
            }
        }

        ++scannedPairs;
        std::cout << "Scanned pair range #" << scannedPairs << "...\n";
    }

    return lowestLocationNumber;
}

int main() {
    ParsedInput parsedInput;
    
    parseInput(INPUT_PATH, parsedInput);

    long long part1Solution = solvePart1(parsedInput);

    std::cout << part1Solution << std::endl;

    long long part2Solution = solvePart2(parsedInput);

    std::cout << part2Solution << std::endl;
}