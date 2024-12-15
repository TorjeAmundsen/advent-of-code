#pragma once

#ifndef AOC_HELPERS
#define AOC_HELPERS

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <unordered_map>
#include <regex>

namespace aoc {
    typedef std::vector<std::vector<int32_t>> matrix;
    typedef std::vector<std::vector<uint32_t>> umatrix;
    typedef std::vector<std::vector<int64_t>> lmatrix;
    typedef std::vector<std::vector<uint64_t>> ulmatrix;

    void print(std::vector<std::string>& input);
    void print(std::vector<int32_t>& input);
    void print(matrix& input);
    void print(umatrix& input);
    void print(lmatrix& input);
    void print(ulmatrix& input);

    std::vector<std::string> get_input(const char* filename);

    int32_t is_digit(char ch);

    int32_t find_digit(std::string& input, int32_t from = 0);
    int32_t find_non_digit(std::string& input, int32_t from = 0);

    std::vector<std::vector<int32_t>> get_i32s(std::vector<std::string>& input);
    std::vector<std::vector<uint32_t>> get_u32s(std::vector<std::string>& input);
    std::vector<std::vector<int64_t>> get_i64s(std::vector<std::string>& input);
    std::vector<std::vector<uint64_t>> get_u64s(std::vector<std::string>& input);

    std::vector<int32_t> get_digits(std::string& input);
    std::vector<int32_t> get_digits(std::vector<std::string>& input);

    std::unordered_map<int32_t, int32_t> count(std::vector<int32_t>& nums);
    std::unordered_map<char, int32_t> count(std::string& input);
    std::unordered_map<std::string, int32_t> count(std::vector<std::string>& words);
    int32_t count (std::string& input, const char char_to_count);
    int32_t count (std::vector<std::string>& input, const char char_to_count);

    std::vector<std::string> rxfilter(std::string& input, const char* regex_expression);
    std::vector<std::vector<std::string>> rxfilter(std::vector<std::string>& input_vector, const char* regex_expression);
}

#endif