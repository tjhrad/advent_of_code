#ifndef KEYPAD_H
#define KEYPAD_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

class Keypad{
    private:
        std::string type;
        std::vector<std::vector<char>> keypad_grid;
        std::pair<int, int> starting_position;
        std::map<char,std::pair<int, int>> keypad_coordinates;

    public:
        Keypad(const std::string& keypad_type);
        std::vector<std::string> find_shortest_possible_instructions(const std::string& input_instructions);
        unsigned long long calculate_shortest_length(const std::string& input_instruction, const std::pair<int, int> current_position, int depth);
        bool check_if_valid(const std::string& input, const std::pair<int, int>& start_pos);
};

#endif // KEYPAD_H