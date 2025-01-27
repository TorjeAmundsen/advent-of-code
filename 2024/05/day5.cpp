#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>

#define INPUT_PATH "inputs/5.txt"

std::vector<int32_t> get_i32s(std::string& input) {
        std::vector<int32_t> nums_in_line;
        std::string number_as_str;

        int32_t strptr = 0;

        while (strptr < input.size()) {
            char cur = input[strptr];
            if (cur >= '0' && cur <= '9') {
                number_as_str.push_back(cur);
            } else {
                if (number_as_str.size() > 0) {
                    nums_in_line.push_back(std::stoi(number_as_str));
                    number_as_str.clear();
                }
            }
            ++strptr;
        }
        
        if (number_as_str.size() > 0) {
            nums_in_line.push_back(std::stoi(number_as_str));
        }

        return nums_in_line;
}

void parse_input(
    const char* filename,
    std::unordered_map<int32_t, std::unordered_set<int32_t>>& rules,
    std::vector<std::vector<int32_t>>& pages
) {

    std::ifstream file(filename);
    std::string line;

    while (getline(file, line) && line.size()) {
        std::string left_str = line.substr(0, 2);
        std::string right_str = line.substr(3, 2);
        int32_t left_num = std::stoi(left_str);
        int32_t right_num = std::stoi(right_str);

        if (rules.find(left_num) == rules.end()) {
            std::unordered_set<int32_t> num_set;
            num_set.insert(right_num);
            rules[left_num] = num_set;
        } else {
            rules[left_num].insert(right_num);
        }
    }

    while (getline(file, line)) {
        std::vector<int32_t> nums_in_line = get_i32s(line);
        pages.push_back(nums_in_line);
    }
}

int32_t solve_part_1(std::unordered_map<int32_t, std::unordered_set<int32_t>>& rules,
    std::vector<std::vector<int32_t>>& pages
) {
    int32_t output = 0;

    std::vector<std::vector<int32_t>> valid_lines;

    for (auto line : pages) {
        std::vector<int32_t> seen_nums;

        int32_t valid_line = 1;
        for (auto num : line) {
            if (rules.find(num) != rules.end()) {
                for (auto seen_page : seen_nums) {
                    for (auto y_rule : rules[num]) {
                        if (seen_page == y_rule) {
                            valid_line = 0;
                            break;
                        }
                    }
                    if (valid_line == 0) {
                        break;
                    }
                }
            }

            seen_nums.push_back(num);
        }
        if (valid_line = 1) {
            valid_lines.push_back(line);
        }
    }

    std::cout << valid_lines.size() << std::endl;

    return output;
}

int main() {
    std::unordered_map<int32_t, std::unordered_set<int32_t>> rules;
    std::vector<std::vector<int32_t>> pages;

    parse_input(INPUT_PATH, rules, pages);

    solve_part_1(rules, pages);
}