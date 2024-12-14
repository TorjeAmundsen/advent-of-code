#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <algorithm>

#define INPUT_PATH "inputs/1.txt"

static void readFileToVectors(const char* filename, std::vector<int>& firstHalf, std::vector<int>& secondHalf) {
    firstHalf.clear();
    secondHalf.clear();
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        int leftNum = std::stoi( line.substr(0, 5) );
        int rightNum = std::stoi( line.substr(8, 5) );

        firstHalf.push_back(leftNum);
        secondHalf.push_back(rightNum);
    }
}

int solvePart1(std::vector<int>& leftVector, std::vector<int>& rightVector) {
    int totalDistance = 0;
    for (int i = 0; i < leftVector.size(); ++i) {
        totalDistance += abs( leftVector[i] - rightVector[i] );
    }

    return totalDistance;
}

void printVector(std::vector<int>& vector) {
    for (int i = 0; i < vector.size(); ++i) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}

int solvePart2(std::vector<int>& leftVector, std::vector<int>& rightVector) {

    int similarityScore = 0;

    std::unordered_map<int, int> map;
    
    for (int i = 0; i < rightVector.size(); ++i) {
        if (map.find(rightVector[i]) == map.end()) {
            map[rightVector[i]] = 1;
        } else {
            map[rightVector[i]] += 1;
        }
    }

    for (int i = 0; i < leftVector.size(); ++i) {
        similarityScore += leftVector[i] * map[leftVector[i]];
    }

    return similarityScore;
}

int comparator(int a, int b) { return a >= b; }

int main() {
    std::vector<int> leftHalf;
    std::vector<int> rightHalf;

    readFileToVectors(INPUT_PATH, leftHalf, rightHalf);

    std::sort(leftHalf.begin(), leftHalf.end(), comparator);
    std::sort(rightHalf.begin(), rightHalf.end(), comparator);
    
    int part1Solution = solvePart1(leftHalf, rightHalf);

    std::cout << part1Solution << std::endl;

    int part2Solution = solvePart2(leftHalf, rightHalf);

    std::cout << part2Solution << std::endl;

    return 0;
}