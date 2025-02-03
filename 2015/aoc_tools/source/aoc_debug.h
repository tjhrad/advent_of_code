#ifndef AOC_DEBUG_H
#define AOC_DEBUG_H

#include <iostream>
#include <vector>
#include <map>

void Print(const std::vector<std::vector<int>>& input_data);
void Print(const std::vector<std::string>& input_data);
void Print(const std::vector<long long>& input_data);
void Print(const std::vector<int>& input_data);
void Print(const std::vector<std::vector<long long>>& input_data);
void Print(const std::vector<std::vector<unsigned long long>>& input_data);
void Print(const std::vector<std::vector<char>>& input_data);
void Print(const std::multimap<char,std::vector<int>>& input_data);

#endif