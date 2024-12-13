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

namespace aoc {
    typedef std::vector<std::vector<int32_t>> matrix;
    typedef std::vector<std::vector<uint32_t>> umatrix;
    typedef std::vector<std::vector<int64_t>> lmatrix;
    typedef std::vector<std::vector<uint64_t>> ulmatrix;

    std::vector<std::string> get_input(const char* filename);

    int32_t is_digit(char ch);

    int32_t find_digit(std::string& input, int32_t from = 0);
    int32_t find_non_digit(std::string& input, int32_t from = 0);

    std::vector<std::vector<int32_t>> get_i32s(std::vector<std::string>& input);
    std::vector<std::vector<uint32_t>> get_u32s(std::vector<std::string>& input);
    std::vector<std::vector<int64_t>> get_i64s(std::vector<std::string>& input);
    std::vector<std::vector<uint64_t>> get_u64s(std::vector<std::string>& input);

    std::unordered_map<int32_t, int32_t> count(std::vector<int32_t>& nums);
    std::unordered_map<char, int32_t> count(std::string& input);
    std::unordered_map<std::string, int32_t> count(std::vector<std::string>& words);
}

#endif