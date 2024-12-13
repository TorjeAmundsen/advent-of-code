#include "helpers.h"

namespace aoc {
    std::vector<std::string> get_input(const char* filename) {
        std::vector<std::string> output;

        std::ifstream file(filename);
        std::string line;

        while (getline(file, line)) {
            output.push_back(line);
        }

        return output;
    }

    int32_t is_digit(char ch) {
        return ch >= '0' && ch <= '9';
    }

    int32_t find_digit(std::string input, int32_t from = 0) {
        for (int32_t i = from; i < input.size(); ++i) {
            if (is_digit(input[i])){
                return i;
            }
        }

        return -1;
    }

    int32_t find_non_digit(std::string input, int32_t from = 0) {
        for (int32_t i = from; i < input.size(); ++i) {
            if (!is_digit(input[i])) {
                return i;
            }
        }
    }

    std::vector<std::vector<int32_t>> get_i32s(std::vector<std::string>& input) {
        std::vector<std::vector<int32_t>> output;

        for (int32_t i = 0; i < input.size(); ++i) {
            std::vector<int32_t> nums_in_line;
            std::string number_as_str;

            int32_t strptr = 0;

            while (strptr < input[i].size()) {
                char cur = input[i][strptr];
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
            output.push_back(nums_in_line);
        }

        return output;
    }
    std::vector<std::vector<uint32_t>> get_u32s(std::vector<std::string>& input) {
        std::vector<std::vector<uint32_t>> output;

        for (uint32_t i = 0; i < input.size(); ++i) {
            std::vector<uint32_t> nums_in_line;
            std::string number_as_str;

            int32_t strptr = 0;

            while (strptr < input[i].size()) {
                char cur = input[i][strptr];
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
            output.push_back(nums_in_line);
        }

        return output;
    }

    std::vector<std::vector<int64_t>> get_i64s(std::vector<std::string>& input) {
        std::vector<std::vector<int64_t>> output;

        for (int64_t i = 0; i < input.size(); ++i) {
            std::vector<int64_t> nums_in_line;
            std::string number_as_str;

            int32_t strptr = 0;

            while (strptr < input[i].size()) {
                char cur = input[i][strptr];
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
            output.push_back(nums_in_line);
        }

        return output;
    }

    std::unordered_map<int32_t, int32_t> count(std::vector<int32_t>& nums) {
        std::unordered_map<int32_t, int32_t> map;

        for (auto num : nums) {
            if (map.find(num) == map.end()) {
                map[num] == 1;
            } else {
                map[num] += 1;
            }
        }

        return map;
    }

    std::unordered_map<char, int32_t> count(std::string& input) {
        std::unordered_map<char, int32_t> map;

        for (auto ch : input) {
            if (map.find(ch) == map.end()) {
                map[ch] == 1;
            } else {
                map[ch] += 1;
            }
        }

        return map;
    }

    std::unordered_map<std::string, int32_t> count(std::vector<std::string>& words) {
        std::unordered_map<std::string, int32_t> map;

        for (auto word : words) {
            if (map.find(word) == map.end()) {
                map[word] == 1;
            } else {

            }
        }

        return map;
    }

}

