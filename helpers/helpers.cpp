#include "helpers.h"

namespace aoc {
    void print(std::vector<std::string>& input) {
        for (auto line : input) {
            std::cout << line << std::endl;
        }
    }

    void print(std::vector<int32_t>& input) {
        for (auto num : input) {
            std::cout << num << std::endl;
        }
    }

    void print(matrix& input) {
        for (auto row : input) {
            for (auto num : row) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }
    }

    void print(umatrix& input) {
        for (auto row : input) {
            for (auto num : row) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }
    }

    void print(lmatrix& input) {
        for (auto row : input) {
            for (auto num : row) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }
    }

    void print(ulmatrix& input) {
        for (auto row : input) {
            for (auto num : row) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }
    }

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
                if (is_digit(cur)) {
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
                number_as_str.clear();
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
                        nums_in_line.push_back(std::stoll(number_as_str));
                        number_as_str.clear();
                    }
                }
                ++strptr;
            }
            output.push_back(nums_in_line);
        }

        return output;
    }

    std::vector<std::vector<uint64_t>> get_u64s(std::vector<std::string>& input) {
        std::vector<std::vector<uint64_t>> output;

        for (uint64_t i = 0; i < input.size(); ++i) {
            std::vector<uint64_t> nums_in_line;
            std::string number_as_str;

            int32_t strptr = 0;

            while (strptr < input[i].size()) {
                char cur = input[i][strptr];
                if (cur >= '0' && cur <= '9') {
                    number_as_str.push_back(cur);
                } else {
                    if (number_as_str.size() > 0) {
                        nums_in_line.push_back(std::stoull(number_as_str));
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

    std::vector<int32_t> get_digits(std::string& input) {
        std::vector<int32_t> output;

        for (auto c : input) {
            if (is_digit(c)) {
                output.push_back(c - '0');
            }
        }

        return output;
    }

    std::vector<int32_t> get_digits(std::vector<std::string>& input) {
        std::vector<int32_t> output;
        
        for (auto line : input) {
            for (auto c : line) {
                if (is_digit(c)) {
                    output.push_back(c - '0');
                }
            }
        }

        return output;
    }
    

    int32_t count(std::string& input, const char char_to_count) {
        int32_t output = 0;
        for (auto current : input) {
            if (current == char_to_count) {
                ++output;
            }
        }

        return output;
    }

    int32_t count(std::vector<std::string>& input, const char char_to_count) {
        int32_t output = 0;
        for (auto line : input) {
            for (auto current : line) {
                if (current == char_to_count) {
                    ++output;
                }
            }
        }

        return output;
    }

    std::vector<std::string> rxfilter(std::string& input, const char* regex_expression) {
        std::vector<std::string> output;
        
        std::regex regex(regex_expression);

        auto matched_begin = std::sregex_iterator(input.begin(), input.end(), regex);
        auto matched_end = std::sregex_iterator();

        for (auto i = matched_begin; i != matched_end; ++i) {
            std::string match = (*i).str();

            output.push_back(match);
        }

        return output;
    }

    std::vector<std::vector<std::string>> rxfilter(std::vector<std::string>& input_vector, const char* regex_expression) {
        std::vector<std::vector<std::string>> output;

        for (auto line : input_vector) {
            output.push_back(rxfilter(line, regex_expression));
        }

        return output;
    }
}

