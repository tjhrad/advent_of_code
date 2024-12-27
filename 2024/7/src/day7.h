#ifndef DAY7H
#define DAY7H

#include <iostream>
#include <numeric>
#include <map>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <bitset>
#include <tuple>


#include "../../aoc_tools/src/aoc_tools.h"

long long int part_one(const std::vector<std::string>& input_data);
long long int part_two(const std::vector<std::string>& input_data);

std::vector<long long int> return_equation_answers(const std::vector<std::string>& input_data);
std::vector<std::vector<long long int>> return_equation_numbers(const std::vector<std::string>& input_data);
long long int return_total_calibration_result(std::vector<std::vector<long long int>>& equation_numbers,std::vector<long long int>& equation_answers, std::vector<char>& operators);
bool check_if_valid_equation(std::vector<long long int>& equation_numbers, long long int answer, std::vector<char>& operators);

#endif 
