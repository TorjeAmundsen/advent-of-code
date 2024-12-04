#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>

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

static void merge(std::vector<int>& input, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<int> LeftVector(n1);
    std::vector<int> RightVector(n2);

    for (int i = 0; i < n1; ++i) {
        LeftVector[i] = input[left + i];
    }
    for (int i = 0; i < n2; i++) {
        RightVector[i] = input[middle + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (LeftVector[i] <= RightVector[j]) {
            input[k] = LeftVector[i];
            ++i;
        } else {
            input[k] = RightVector[j];
            ++j;
        }

        ++k;
    }

    while (i < n1) {
        input[k] = LeftVector[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        input[k] = RightVector[j];
        ++j;
        ++k;
    }
}

static void mergeSort(std::vector<int>& input, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    mergeSort(input, left, mid);
    mergeSort(input, mid + 1, right);
    merge (input, left, mid, right);
}

int solvePart1(std::vector<int>& leftVector, std::vector<int>& rightVector) {
    mergeSort(leftVector, 0, leftVector.size() - 1);
    mergeSort(rightVector, 0, rightVector.size() - 1);

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


//assumes part 1 is solved beforehand, otherwise the vectors are unsorted
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

int main() {
    std::vector<int> leftHalf;
    std::vector<int> rightHalf;

    readFileToVectors("input.txt", leftHalf, rightHalf);
    
    int part1Solution = solvePart1(leftHalf, rightHalf);

    std::cout << part1Solution << std::endl;

    int part2Solution = solvePart2(leftHalf, rightHalf);

    std::cout << part2Solution << std::endl;

    return 0;
}