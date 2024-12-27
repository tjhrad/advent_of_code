#include "Keypad.h"
#include "day21.h"

int main(){
    std::cout << '\n' << "AOC 2024 - DAY 21" << '\n' << std::endl;

    // Read input
    std::string input_file_path = ".\\21\\data\\input.txt";
    std::vector<std::string> input_file_data = read_text_file(input_file_path);

    // Part 1
    part_one(input_file_data);

    // Part 2
    part_two(input_file_data);

    return 0;
}

void part_one(const std::vector<std::string>& input_data){
    // Start timer
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "PART 1" << std::endl;

    // Code here
    Keypad numeric_keypad("numeric");
    Keypad directional_keypad("directional");
    unsigned long long complexity = 0;
    for (std::string s : input_data){
        std::vector<std::string> instructions = numeric_keypad.find_shortest_possible_instructions(s);

        std::pair<int, int> position = {0,2};
        unsigned long long length = ULLONG_MAX;
        for (std::string ss: instructions){
            unsigned long long temp_length = directional_keypad.calculate_shortest_length(ss, position, 2);
            if (temp_length < length){
                length = temp_length;
            }
            
        }
        std::cout << s << ": " << length << std:: endl;
        complexity = complexity + calculate_complexity(s, length);
    }

    auto answer = complexity;
    std::cout << "Answer for part 1: " << answer << std::endl;

    // End timer
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time to complete: " << duration.count() << " milliseconds." << std::endl << std::endl;
}

void part_two(const std::vector<std::string>& input_data){
    // Start timer
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "PART 2" << std::endl;

    // Code here
    Keypad numeric_keypad("numeric");
    Keypad directional_keypad("directional");
    unsigned long long complexity = 0;
    for (std::string s : input_data){
        std::vector<std::string> instructions = numeric_keypad.find_shortest_possible_instructions(s);

        std::pair<int, int> position = {0,2};
        unsigned long long length = ULLONG_MAX;
        for (std::string ss: instructions){
            unsigned long long temp_length = directional_keypad.calculate_shortest_length(ss, position, 25);
            if (temp_length < length){
                length = temp_length;
            }
            
        }
        std::cout << s << ": " << length << std:: endl;
        complexity = complexity + calculate_complexity(s, length);
    }

    auto answer = complexity;
    std::cout << "Answer for part 2: " << answer << std::endl;

    // End timer
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time to complete: " << duration.count() << " milliseconds." << std::endl << std::endl;
}

unsigned long long calculate_complexity(const std::string& code, const unsigned long long& length){
    long long complexity = 0;

    std::string code_numbers = std::regex_replace(code, std::regex(R"([\D])"), "");
    
    long long code_as_ll = std::stoll(code_numbers);
    complexity = length * code_as_ll;

    return complexity;
}
