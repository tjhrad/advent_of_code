
#include "day18.h"
#include "Pathfinder.h"

std::set<std::pair<int,int>> temporary_box_coordinates;

int main()
{
    std::cout << '\n' << "AOC 2024 - DAY 18" << '\n' << std::endl;

    // Read input
    std::string input_file_path = ".\\18\\data\\input.txt";
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
    int map_x = 71;
    int map_y = 71;
    int number_of_walls = 1024;

    Node* start_node = new Node(0, 0); // Starting node with position 0,0 (x,y).
    start_node->gCost = 0;
    Node* end_node = new Node(map_x - 1, map_y - 1);

    // Initialize the grid map of size map_x, map_y with '.'
    std::vector<std::string> map(map_y, std::string(map_x,'.'));

    // Convert input strings to std::pair<int, int> coordinates.
    auto wall_coordinates = get_wall_coordinates(input_data);

    // Add bytes to map.
    auto map_with_walls = add_walls_to_map(wall_coordinates, number_of_walls, map);

    // Calculcate shortest path
    auto path = a_star_find_path(map_with_walls, start_node, end_node);

    // Add the path to the map.
    auto map_with_path = add_path_to_map(path, map_with_walls); // CHANGE NAME OF map IF NEEDED.

    // Count the steps taken.
    auto answer = count_all_tiles(map_with_path) - 1;
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
    int map_x = 71;
    int map_y = 71;
    int number_of_walls = 1024;

    Node* start_node = new Node(0, 0); // Starting node with position 0,0 (x,y).
    start_node->gCost = 0;
    Node* end_node = new Node(map_x - 1, map_y - 1);

    // Initialize the grid map of size map_x, map_y with '.'
    std::vector<std::string> map(map_y, std::string(map_x,'.'));

    // Convert input strings to std::pair<int, int> coordinates.
    auto wall_coordinates = get_wall_coordinates(input_data);

    // Add bytes to map.
    auto map_with_walls = add_walls_to_map(wall_coordinates, number_of_walls, map);

    // Remove the bytes that have already been added to the map.
    wall_coordinates.erase(wall_coordinates.begin(), wall_coordinates.begin() + number_of_walls);

    bool is_path_blocked = false;
    std::pair<int, int> blocking_wall;
    while (!is_path_blocked)
    {
        map_with_walls = add_walls_to_map(wall_coordinates, 1, map_with_walls);
        // Calculcate shortest path
        auto path = a_star_find_path(map_with_walls, start_node, end_node);
        if (path.empty())
        {
            is_path_blocked = true;
            blocking_wall = wall_coordinates[0];
            break;
        }
        wall_coordinates.erase(wall_coordinates.begin(), wall_coordinates.begin() + 1);
    }
    
    // Count the steps taken.
    auto answer = std::to_string(blocking_wall.first) + "," + std::to_string(blocking_wall.second);
    std::cout << "Answer for part 2: " << answer << std::endl;

    // End timer
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time to complete: " << duration.count() << " milliseconds." << std::endl << std::endl;
}

std::vector<std::string> add_walls_to_map(const std::vector<std::pair<int,int>>& wall_coordinates, const int& number_of_walls, const std::vector<std::string>& map)
{
    std::vector<std::string> map_with_walls = map;

    for (int i=0; i<number_of_walls; i++)
    {
        map_with_walls[wall_coordinates[i].second][wall_coordinates[i].first] = '#';
    }

    return map_with_walls;
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

int count_all_tiles(const std::vector<std::string>& map)
{
    int count = 0;

    for (std::string s : map)
    {
        for (char c : s)
        {
            if (c == 'O')
            {
                count++;
            }
        }
    }
    return count;
}

std::vector<std::pair<int,int>> get_wall_coordinates(const std::vector<std::string>& input_data)
{
    std::vector<std::pair<int,int>> wall_coordinates;

    for (std::string s : input_data)
    {
        std::vector<std::string> split_s = split_string(s, ",");
        wall_coordinates.push_back(std::make_pair(stoi(split_s[0]), stoi(split_s[1])));
    }

    return wall_coordinates;
}