#include "Keypad.h"

// Keypad constructor.
Keypad::Keypad(const std::string& keypad_type){
    type = keypad_type;
    if (type == "directional"){
        keypad_grid.push_back({'#','^','A'});
        keypad_grid.push_back({'<','v','>'});
        starting_position = {0,2}; // Always start at 'A'.
    }
    else if (type == "numeric"){
        keypad_grid.push_back({'7','8','9'});
        keypad_grid.push_back({'4','5','6'});
        keypad_grid.push_back({'1','2','3'});
        keypad_grid.push_back({'#','0','A'});
        starting_position = {3,2}; // Always start at 'A'.
    }
    else{
        std::cout << "Invalid keypad type: " << type << std::endl;
    }
    // Add coordinates of the keypad to a map for quick reference.
    for (int x=0; x<keypad_grid.size(); x++){
        for (int y=0; y<keypad_grid[0].size(); y++){
            keypad_coordinates.insert({keypad_grid[x][y],std::make_pair(x,y)});
        }
    }
}

std::vector<std::string> Keypad::find_shortest_possible_instructions(const std::string& input_instructions){

    std::vector<std::string> all_combinations;
    std::string z = "";
    all_combinations.push_back(z);

    std::pair last_coordinates = starting_position;
    std::string all_current_instructions = "";
    std::vector<std::string> temp_vector;
    for (char c : input_instructions){
        std::string current_instruction = "";
        std::pair new_coordinates = keypad_coordinates[c];
        int delta_x = new_coordinates.first - last_coordinates.first;
        int delta_y = new_coordinates.second - last_coordinates.second;
        int number_of_moves_needed = std::abs(delta_x + delta_y);

        if (delta_y < 0){
            for (int i=0; i<std::abs(delta_y); i++){
            current_instruction = current_instruction + "<";
            }
        }
        if (delta_y > 0){
                for (int i=0; i<delta_y; i++){
                current_instruction = current_instruction + ">";
            }
        }   
        if (delta_x > 0){
                for (int i=0; i<delta_x; i++){
                current_instruction = current_instruction + "v";
            }
        }
        if (delta_x < 0){
                for (int i=0; i<std::abs(delta_x); i++){
                current_instruction = current_instruction + "^";
            }
        }

        std::sort(current_instruction.begin(), current_instruction.end());

        //std::cout << current_instruction << std::endl;

        std::vector<std::string> temp_vector;
        do {
            for (std::string s : all_combinations){
                if (check_if_valid(current_instruction, last_coordinates)){
                    //std::cout << "Valid input: " << current_instruction << std::endl;
                    temp_vector.push_back(s + current_instruction + "A");
                }
            }
        } while (std::next_permutation(current_instruction.begin(), current_instruction.end()));

        all_combinations.clear();
        all_combinations = temp_vector;
        temp_vector.clear();

        last_coordinates = new_coordinates;
    }

    return all_combinations;
}

// The magic is here. The function above this one was much slower, but I kept it for the final solution.
// Too tired to do any more optimization. ¯\_(ツ)_/¯
std::map<std::string, unsigned long long> cache;
unsigned long long Keypad::calculate_shortest_length(const std::string& input_instruction, const std::pair<int, int> current_position, int depth){
    unsigned long long length = 0;

    if (depth == 0)
    {
        return input_instruction.size();
    }

    std::pair last_coordinates = current_position;
    for (char c: input_instruction){
        std::string current_instruction = "";
        std::pair new_coordinates = keypad_coordinates[c];
        int delta_x = new_coordinates.first - last_coordinates.first;
        int delta_y = new_coordinates.second - last_coordinates.second;
        int number_of_moves_needed = std::abs(delta_x + delta_y);

        if (delta_y < 0){
            for (int i=0; i<std::abs(delta_y); i++){
            current_instruction = current_instruction + "<";
            }
        }
        if (delta_y > 0){
                for (int i=0; i<delta_y; i++){
                current_instruction = current_instruction + ">";
            }
        }   
        if (delta_x > 0){
                for (int i=0; i<delta_x; i++){
                current_instruction = current_instruction + "v";
            }
        }
        if (delta_x < 0){
                for (int i=0; i<std::abs(delta_x); i++){
                current_instruction = current_instruction + "^";
            }
        }

        std::sort(current_instruction.begin(), current_instruction.end());

        std::vector<std::string> temp_vector;
        unsigned long long current_shortest = ULLONG_MAX;
        do {
            if (check_if_valid(current_instruction, last_coordinates)){
                std::string temp_instruction = current_instruction + "A";
                std::string key = temp_instruction + "-" + std::to_string(depth-1);

                unsigned long long instruction_length = 0;
                if (cache.find(key) != cache.end()){
                    instruction_length = cache[key];
                }
                else{
                    std::pair<int, int> position = {0,2};
                    instruction_length = calculate_shortest_length(temp_instruction, starting_position, depth - 1);
                    cache.insert(std::make_pair(key, instruction_length));
                }
                if (instruction_length < current_shortest){
                    current_shortest = instruction_length;
                }
            }
        } while (std::next_permutation(current_instruction.begin(), current_instruction.end()));

        length = length + current_shortest;

        last_coordinates = new_coordinates;

    }
    return length;
}

bool Keypad::check_if_valid(const std::string& input, const std::pair<int, int>& start_pos){
    bool is_valid = true;

    int x = start_pos.first;
    int y = start_pos.second;
    
    for (char c: input){
        if (c == '^'){
            if (keypad_grid[x-1][y] == '#'){
                is_valid = false;   
            }
            x = x - 1;
        }
        else if (c == '>'){
            if (keypad_grid[x][y+1] == '#'){
                is_valid = false;  
            }
            y = y + 1;
        }
        else if (c == 'v'){
            if (keypad_grid[x+1][y] == '#'){
                is_valid = false;
            }
            x = x + 1;
        }
        else if (c == '<'){
            if (keypad_grid[x][y-1] == '#'){
                is_valid = false;
            }
            y = y - 1;
        }
    }

    return is_valid;
}