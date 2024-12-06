#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#define INPUT_PATH "inputs/2.txt"

typedef struct {
    char color;
    int count;
} CubeSet;

void readFile(const char* filename, std::vector<std::vector<CubeSet>>& vector) {
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        int whitespaces = 0;
        int start_i = 0;
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] == ' ') {
                ++whitespaces;
                if (whitespaces == 2) {
                    start_i = i + 1;
                    break;
                }
            }
        }

        std::string game = line.substr(start_i);
        
        
    }
}

int main() {
    std::vector<std::vector<CubeSet>> input;

    readFile(INPUT_PATH, input);
}