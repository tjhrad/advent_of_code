#ifndef AOC_TOOLS_H
#define AOC_TOOLS_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>
#include <chrono>

std::vector<std::string> ReadFile(const std::string& file_name);
std::vector<std::string> SplitString(std::string string_to_split,std::string delimiter);

std::string ConvertIntegerToBaseN(int num, int base);
std::string RemoveNonalphaCharacters(std::string s);
std::string RemoveNonalphanumericCharacters(std::string s);
std::vector<int> ConvertStringsToInt(const std::string& input_data);
std::vector<int> ConvertStringsToInt(const std::vector<std::string>& input_strings);
std::vector<long long int> ConvertStringsToLongLongInt(const std::vector<std::string>& input_strings);
std::vector<std::vector<char>> StringsToChars(const std::vector<std::string>& strings);
std::vector<std::vector<int>> Subtract2DVectors(const std::vector<std::vector<int>>& vector1, const std::vector<std::vector<int>>& vector2);
std::vector<std::vector<int>> Multiply2DVectors(const std::vector<std::vector<int>>& vector1, const std::vector<std::vector<int>>& vector2);

long long CombineIntInString(const std::string& input_data);
int SumIntegers(const std::vector<int>& v);
bool StringIsDigits(const std::string& input_string);

void PrintTime(const std::chrono::system_clock::time_point& start, const std::chrono::system_clock::time_point& stop);

#endif