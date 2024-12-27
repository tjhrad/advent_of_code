#ifndef DAY5H
#define DAY5H

#include <iostream>
#include <numeric>
#include <map>
#include <filesystem>
#include <chrono>


#include "../../aoc_tools/src/aoc_tools.h"

int part_one(const std::vector<std::string>& input_data);
int part_two(const std::vector<std::string>& input_data);
std::multimap<int, int> get_page_ordering_rules(const std::vector<std::string>& input_data);
std::vector<std::vector<int>> get_pages_to_produce(const std::vector<std::string>& input_data);
std::vector<std::vector<int>> return_correctly_ordered_updates(const std::vector<std::vector<int>>& input_data, const std::multimap<int, int>& ordering_rules);
int add_middle_page_numbers (const std::vector<std::vector<int>>& input_data);
std::vector<std::vector<int>> return_incorrectly_ordered_updates(const std::vector<std::vector<int>>& input_data, const std::multimap<int, int>& ordering_rules);
std::vector<std::vector<int>> correct_incorrectly_ordered_updates(const std::vector<std::vector<int>>& input_data, const std::multimap<int, int>& ordering_rules);

#endif 
