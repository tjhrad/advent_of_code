#ifndef DAY15H
#define DAY15H

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <map>
#include <filesystem>
#include <chrono>
#include <cmath>
#include <set>
#include <thread>

#include "../../aoc_tools/src/aoc_tools.h"

void part_one(const std::vector<std::string>& input_data);
void part_two(const std::vector<std::string>& input_data);

std::pair<std::vector<std::string>, std::vector<std::string>> get_map_and_instructions(const std::vector<std::string>& input_data);
std::set<std::pair<int, int>> get_wall_coordinates(const std::vector<std::string>& input_map);
std::set<std::pair<int, int>> get_box_coordinates(const std::vector<std::string>& input_map);
std::pair<int, int> get_robot_coordinates(const std::vector<std::string>& input_map);
void move_robot(std::pair<int, int>& robot_coordinates, std::set<std::pair<int,int>>& box_coordinates, std::set<std::pair<int,int>>& wall_coordinates, const std::vector<std::string>& instructions, std::vector<std::string>& map);
void update_all(int x_direction, int y_direction, std::pair<int, int>& robot_coordinates, std::set<std::pair<int,int>>& box_coordinates, std::set<std::pair<int,int>>& wall_coordinates, const std::vector<std::string>& instructions, std::vector<std::string>& map);
int sum_gps_coordinates(const std::set<std::pair<int,int>>& box_coordinates);

std::vector<std::string> get_expanded_map(const std::vector<std::string>& input_data);
void move_robot_expanded(std::pair<int, int>& robot_coordinates, std::set<std::pair<int,int>>& box_coordinates, std::set<std::pair<int,int>>& wall_coordinates, const std::vector<std::string>& instructions, std::vector<std::string>& map);
void update_all_expanded(int x_direction, int y_direction, std::pair<int, int>& robot_coordinates, std::set<std::pair<int,int>>& box_coordinates, std::set<std::pair<int,int>>& wall_coordinates, const std::vector<std::string>& instructions, std::vector<std::string>& map);

void find_all_boxes(int x_start, int y_start, int x_direction, int y_direction, std::vector<std::string>& map);

#endif 
