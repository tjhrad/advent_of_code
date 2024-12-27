#include "Pathfinder.h"
#include "day20.h"

int main()
{
    std::cout << '\n' << "AOC 2024 - DAY 20" << '\n' << std::endl;

    // Read input
    std::string input_file_path = ".\\20\\data\\input.txt";
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
    Node* start_node = get_start_node(input_data);
    start_node->gCost = 0;
    Node* end_node = get_end_node(input_data);
    auto path = a_star_find_path(input_data, start_node, end_node);

    auto map_with_path = add_path_to_map(path, input_data);
    
    auto answer = count_cheats(input_data, path);
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
    Node* start_node = get_start_node(input_data);
    start_node->gCost = 0;
    Node* end_node = get_end_node(input_data);
    auto path = a_star_find_path(input_data, start_node, end_node);

    auto map_with_path = add_path_to_map(path, input_data);
    
    auto answer = count_long_cheats(input_data, path);
    std::cout << "Answer for part 2: " << answer << std::endl;

    // End timer
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time to complete: " << duration.count() << " milliseconds." << std::endl << std::endl;
}

Node* get_start_node(const std::vector<std::string>& input_map)
{
    int start_x = 0;
    int start_y = 0;

    for (int y=0; y<input_map.size(); y++)
    {
        for (int x=0; x<input_map[0].size(); x++)
        {
            if (input_map[y][x] == 'S')
            {
                start_x = x;
                start_y = y;
            }
        }
    }
    Node* starting_node = new Node(start_x, start_y);
    return starting_node;
}

Node* get_end_node(const std::vector<std::string>& input_map)
{
    int start_x = 0;
    int start_y = 0;

    for (int y=0; y<input_map.size(); y++)
    {
        for (int x=0; x<input_map[0].size(); x++)
        {
            if (input_map[y][x] == 'E')
            {
                start_x = x;
                start_y = y;
            }
        }
    }
    Node* end_node = new Node(start_x, start_y);
    return end_node;
}

std::vector<std::string> add_path_to_map(std::vector<Node*> path, const std::vector<std::string>& map)
{
    std::vector<std::string> out_map = map;

    for (Node* n: path)
    {
        out_map[n->y][n->x] = 'O';
    }

    return out_map;
}

int count_cheats(const std::vector<std::string>& input_map, const std::vector<Node*>& starting_path)
{
    int count = 0;
    std::map<std::string, int> valid_cheats;///////

    // Define possible movements (4 directions: up, down, left, right)
    int x_direction[4] = {-1, 0, 1, 0};
    int y_direction[4] = {0, 1, 0, -1};
    
    for (int y=0; y<starting_path.size(); y++)
    {
        Node* node = starting_path[y];
        int start_x = node->x;
        int start_y = node->y;

        for (int i=0; i<4; i++)
        {
            int new_x = start_x + x_direction[i];
            int new_y = start_y + y_direction[i];
            
            if (new_x + x_direction[i] < 0 || new_x + x_direction[i] >= input_map[0].size() || new_y + y_direction[i] < 0 || new_y + y_direction[i] >= input_map.size()) {continue;}
            else if (input_map[new_y][new_x] != '#') {continue;}
            else if (input_map[new_y + y_direction[i]][new_x + x_direction[i]] == '#') {continue;}

            bool is_valid_end_position = false;
            int end_index = 0;
            for (int x=y; x<starting_path.size(); ++x)
            {
                if (new_y + y_direction[i] == starting_path[x]->y && new_x + x_direction[i] == starting_path[x]->x)
                {
                    end_index = x;
                    is_valid_end_position = true;
                }
            }

            if(!is_valid_end_position) {continue;}

            int time_saved = end_index - y - 2;

            std::string key = std::to_string(start_x) + "," + std::to_string(start_y) + "-" + std::to_string(new_x + x_direction[i]) + "," + std::to_string(new_y + y_direction[i]);

            valid_cheats.insert(std::make_pair(key, time_saved));
        }
    }

    for (auto cheat : valid_cheats)
    {
        if (cheat.second >= 100)
        {
            count++;
        }
    } 

    return count;
}

long long count_long_cheats(const std::vector<std::string>& input_map, const std::vector<Node*>& starting_path)
{
    long long count = 0;
    std::map<std::string, int> valid_cheats;

    // Define possible movements (4 directions: up, down, left, right)
    const int x_direction[4] = {-1, 0, 1, 0};
    const int y_direction[4] = {0, 1, 0, -1};
    
    for (int y=0; y<starting_path.size(); y++)
    {
        Node* node = starting_path[y];
        int start_x = node->x;
        int start_y = node->y;
        for (int i=y; i<starting_path.size(); ++i)
        {

            int cheat_length = std::abs(starting_path[i]->x - start_x) + std::abs(starting_path[i]->y - start_y);
            if (cheat_length > 20) {continue;}

            std::string key = std::to_string(start_x) + "," + std::to_string(start_y) + " --> " + std::to_string(starting_path[i]->x) + "," + std::to_string(starting_path[i]->y);
            
            if (valid_cheats.find(key) != valid_cheats.end()) {continue;}
            
            int time_saved = i - y - cheat_length;
            valid_cheats.insert(std::make_pair(key, time_saved));
            
        }
    }

    for (auto cheat : valid_cheats)
    {
        if (cheat.second >= 100)
        {
            count++;
        }
    } 

    return count;
}