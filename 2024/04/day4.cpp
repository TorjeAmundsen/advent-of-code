#include <vector>
#include <iostream>
#include <fstream>

#define INPUT_PATH "inputs/4.txt"
#define DIRECTIONS_SIZE 8
#define DIAGONALS_SIZE 4

const std::string XMAS = "XMAS";

const int32_t DIRECTIONS[DIRECTIONS_SIZE][2] = {
    {-1,  0}, // up
    { 1,  0}, // down
    { 0, -1}, // left
    { 0,  1}, // right
    {-1,  1}, // up-right
    { 1,  1}, // down-right
    {-1, -1}, // down-left
    { 1, -1}, // up-left
};

int32_t is_out_of_bounds(std::vector<std::string>& input, int32_t row, int32_t col) {
    if (row < 0 || col < 0 || row >= input.size() || col >= input[0].size()) {
        return true;
    }

    return false;
}

int32_t get_xmases(std::vector<std::string>& input, int32_t row, int32_t col) {
    int32_t xmas_count = 0;

    for (int32_t i = 0; i < DIRECTIONS_SIZE; ++i) {
        int32_t row_dir = DIRECTIONS[i][0];
        int32_t col_dir = DIRECTIONS[i][1];

        for (int32_t j = 1; j < XMAS.size(); ++j) {
            int32_t row_offset = row_dir * j;
            int32_t col_offset = col_dir * j;

            if (is_out_of_bounds(input, row + row_offset, col + col_offset) || input[row + row_offset][col + col_offset] != XMAS[j]) {
                break;
            }

            if (j == 3) {
                ++xmas_count;
            }
        }
    }

    return xmas_count;
}

int32_t solve_part_1(std::vector<std::string>& input) {
    int32_t xmas_count = 0;

    for (int32_t row = 0; row < input.size(); ++row) {
        for (int32_t col = 0; col < input[row].size(); ++col) {
            if (input[row][col] == 'X') {
                xmas_count += get_xmases(input, row, col);
            }
        }
    }

    return xmas_count;
}

const int32_t DIAGONALS[DIAGONALS_SIZE][2] = {
    {-1,  1}, // up-right
    {-1, -1}, // down-left
    { 1,  1}, // down-right
    { 1, -1}, // up-left
};

int32_t solve_part_2(std::vector<std::string>& input) {
    int32_t x_mas_count = 0;

    for (int32_t row = 0; row < input.size(); ++row) {
        for (int32_t col = 0; col < input[row].size(); ++col) {
            if (input[row][col] == 'A') {
                int32_t any_oob = 0;

                for (int32_t i = 0; i < DIAGONALS_SIZE; ++i) {
                    int32_t new_row = row + DIAGONALS[i][0];
                    int32_t new_col = col + DIAGONALS[i][1];

                    if (is_out_of_bounds(input, new_row, new_col)) {
                        any_oob = 1;
                        break;
                    }
                }

                if (any_oob) {
                    continue;
                }

                char up_left = input[row - 1][col - 1];
                char down_right = input[row + 1][col + 1];

                char up_right = input[row - 1][col + 1];
                char down_left = input[row + 1][col - 1];

                if (
                    ((up_left == 'M' || up_left == 'S') &&
                    (down_right == 'M' || down_right == 'S') &&
                    (up_right == 'M' || up_right == 'S') &&
                    (down_left == 'M' || down_left == 'S')) &&
                    (up_left != down_right && up_right != down_left)
                ) {
                    ++x_mas_count;
                }
            }
        }
    }

    return x_mas_count;
}

std::vector<std::string> parse_input(const char* filename) {
    std::vector<std::string> output;
    
    std::ifstream file(filename);
    std::string line;

    while (getline(file, line)) {
        output.push_back(line);
    }

    return output;
}

int main() {
    auto input = parse_input(INPUT_PATH);

    int32_t part_1_solution = solve_part_1(input);

    std::cout << part_1_solution << std::endl;

    int32_t part_2_solution = solve_part_2(input);

    std::cout << part_2_solution << std::endl;
}