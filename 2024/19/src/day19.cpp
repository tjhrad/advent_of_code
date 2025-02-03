#include "Trie.h"
#include "day19.h"

int main()
{
    std::cout << '\n' << "AOC 2024 - DAY 19" << '\n' << std::endl;

    // Read input
    std::string input_file_path = ".\\19\\data\\input.txt";
    std::vector<std::string> input_file_data = read_text_file(input_file_path);

    // Part 1
    part_one(input_file_data);

    // Part 2
    part_two(input_file_data);

    return 0;
}

void part_one(const std::vector<std::string>& input_data)
{
    // Start timer
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "PART 1" << std::endl;

    // Code here
    Trie towel_pattern_substrings = get_trie(input_data);

    std::vector<std::string> desired_designs = input_data;
    desired_designs.erase(desired_designs.begin(), desired_designs.begin() + 2);

    auto answer = count_possible_designs(desired_designs, towel_pattern_substrings);
    std::cout << "Answer for part 1: " << answer << std::endl;

    // End timer
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time to complete: " << duration.count() << " milliseconds." << std::endl << std::endl;
}

void part_two(const std::vector<std::string>& input_data)
{
    // Start timer
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "PART 2" << std::endl;

    // Code here
    Trie towel_pattern_substrings = get_trie(input_data);

    std::vector<std::string> desired_designs = input_data;
    desired_designs.erase(desired_designs.begin(), desired_designs.begin() + 2);

    auto answer = count_all_arrangements(desired_designs, towel_pattern_substrings);
    std::cout << "Answer for part 2: " << answer << std::endl;

    // End timer
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time to complete: " << duration.count() << " milliseconds." << std::endl << std::endl;
}

Trie get_trie(const std::vector<std::string>& input_data)
{
    Trie trie;

    std::vector<std::string> split_s = split_string(input_data[0], ", ");

    for (std::string s : split_s)
    {
        trie.insert(s);
    }

    return trie;
}

int count_possible_designs(const std::vector<std::string>& designs, Trie& towels)
{
    int count = 0;

    for (std::string s : designs)
    {
        if (check_design(s, towels)) 
        {
            count++;
        }
    }

    return count;
}

bool check_design(std::string& design, Trie& towels)
{
    if (towels.search(design)) {return true;}

    for (int i=0; i<design.size(); i++)
    {
        std::string substring = design.substr(0, i);

        if (towels.search(substring))
        {
            std::string next_part_of_word = design.substr(i,design.size()-1);
            if (!check_design(next_part_of_word, towels)) {continue;}
            else {return true;}
        }
    }

    return false;
}

long long count_all_arrangements(const std::vector<std::string>& designs, Trie& towels)
{
    long long count = 0;

    for (std::string s : designs)
    {
        long long num_combinations = count_arrangements(s, towels);
        //std::cout << s << ": " << num_combinations << std::endl;
        count = count + num_combinations;
    }

    return count;
}

// Memoization 
std::map<std::string, long long> cache;
long long count_arrangements(std::string& design, Trie& towels)
{
    long long count = 0;
    if (towels.search(design)) {count = count + 1;}

    for (int i=0; i<design.size(); i++)
    {
        std::string substring = design.substr(0, i);

        if (towels.search(substring))
        {
            std::string next_part_of_word = design.substr(i,design.size());
            if (cache.find(next_part_of_word) != cache.end())
            {
                count = count + cache[next_part_of_word];
            }
            else
            {
                long long arrangements = count_arrangements(next_part_of_word, towels);
                cache.insert(std::make_pair(next_part_of_word, arrangements));
                count = count + arrangements;
            }
        }        
    }

    return count;
}