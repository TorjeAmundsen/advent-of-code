#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <array>
#include <map>

#define INPUT_PATH "inputs/1.txt"

void readFileToVector(const char* filename, std::vector<std::string>& stringVector) {
	stringVector.clear();

	std::ifstream file(filename);
	std::string line;

	while (getline(file, line)) {
		stringVector.push_back(line);
	}
}

int firstAndLastDigitsCombined(std::string input) {
	int leftNumber = 0;
	int rightNumber = 0;

	for (int i = 0; i < input.size(); ++i) {
		char leftChar = input[i];

		if (leftChar >= '1' && leftChar <= '9') {
			leftNumber = leftChar - '0';
			break;
		}
	}

	for (int i = input.size() - 1; i >= 0; --i) {
		char rightChar = input[i];

		if (rightChar >= '1' && rightChar <= '9') {
			rightNumber = rightChar - '0';
			break;
		}
	}

	return (leftNumber * 10) + rightNumber;
}

int calculatePart1(std::vector<std::string>& input) {
	int total = 0;

	for (int i = 0; i < input.size(); ++i) {
		total += firstAndLastDigitsCombined(input[i]);
	}

	return total;
}

int calculatePart2Line(std::string input, std::array<std::string, 9>& digitStrings, std::map<std::string, int>& stringMap) {
	size_t firstIndex = input.size();
	size_t lastIndex = 0;
	int firstNumber = 0;
	int lastNumber = 0;

	for (int i = 0; i < input.size(); ++i) {
		char currentChar = input[i];

		if (currentChar >= '1' && currentChar <= '9') {
			firstNumber = currentChar - '0';
			firstIndex = i;
			break;
		}
	}

	for (int i = input.size() - 1; i >= 0; --i) {
		char currentChar = input[i];

		if (currentChar >= '1' && currentChar <= '9') {
			lastNumber = currentChar - '0';
			lastIndex = i;
			break;
		}
	}

	for (int i = 0; i < digitStrings.size(); ++i) {
		size_t firstStringIndex = input.find(digitStrings[i]);

		if (firstStringIndex != std::string::npos && firstStringIndex < firstIndex) {
			firstNumber = stringMap[digitStrings[i]];
			firstIndex = static_cast<int>(firstStringIndex);
		}

		size_t lastStringIndex = input.rfind(digitStrings[i]);

		if (lastStringIndex != std::string::npos && lastStringIndex > lastIndex) {
			lastNumber = stringMap[digitStrings[i]];
			lastIndex = static_cast<int>(lastStringIndex);
		}
	}

	return (firstNumber * 10) + lastNumber;
}

int calculatePart2(std::vector<std::string>& input) {
	int total = 0;
	std::array<std::string, 9> digitStrings = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	std::map<std::string, int> stringMap = {
		{"one", 1},
		{"two", 2},
		{"three", 3},
		{"four", 4},
		{"five", 5},
		{"six", 6},
		{"seven", 7},
		{"eight", 8},
		{"nine", 9},
	};

	for (int i = 0; i < input.size(); ++i) {
		total += calculatePart2Line(input[i], digitStrings, stringMap);
	}

	return total;
}

int main() {
	std::vector<std::string> input;
	readFileToVector(INPUT_PATH, input);

    int part1Solution = calculatePart1(input);

	std::cout << part1Solution << std::endl;

    int part2Solution = calculatePart2(input);

	std::cout << part2Solution << std::endl;

	return 0;
}