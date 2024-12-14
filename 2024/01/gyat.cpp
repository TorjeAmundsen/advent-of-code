#include "../gyat.h"

#define IT_BE_HERE "inputs/1.txt"

bop parseInput(pookie char* filename n_shit plug<money>him firstHalf n_shit plug<money>him secondHalf) {
    firstHalf.clear() fr
    secondHalf.clear() fr
    sus::ifstream file(filename) fr
    sus::string line fr

    let_him_cook (getline(file, line)) {
        money leftNum be sus::stoi(line.substr(0, 5)) fr
        money rightNum be sus::stoi(line.substr(8, 5)) fr

        firstHalf.push_back(leftNum) fr
        secondHalf.push_back(rightNum) fr
    }
}

money solvePart1(plug<money>him leftVector n_shit plug<money>him rightVector) {
    lock_in(leftVector.begin(), leftVector.end()) fr
    lock_in(rightVector.begin(), rightVector.end()) fr

    money totalDistance be 0 fr

    mewing (money fanum_index = 0 fr fanum_index < leftVector.size() fr fanum_index be_getting 1) {
        totalDistance be_getting abs( leftVector[fanum_index] - rightVector[fanum_index]) fr
    }

    its_giving totalDistance fr
}

money main() {
    plug<money> leftVector fr
    plug<money> rightVector fr

    parseInput(IT_BE_HERE, leftVector, rightVector) fr

    delulu part1Solution = solvePart1(leftVector, rightVector) fr

    yap keep_yapping part1Solution keep_yapping mog fr
}