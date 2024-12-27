
#include "day16.h"
#include "Pathfinder.h"

std::set<std::pair<int,int>> temporary_box_coordinates;

int main()
{
    std::cout << '\n' << "AOC 2024 - DAY 16" << '\n' << std::endl;

    // Read input
    std::string input_file_path = ".\\16\\data\\input.txt";
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
    auto path = find_path(input_data, start_node, end_node);

    auto map_with_path = add_path_to_map(path, input_data);
    
    int answer = get_cost(path);
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
    auto paths = aStar_all_best_paths(input_data, start_node, end_node);

    std::cout << paths.size() << std::endl;
    auto end_map = input_data;
    std::set<int> path_costs;
    for (auto p : paths)
    {
        path_costs.insert(new_get_cost(p));
        end_map = add_path_to_map(p, end_map);
    }

    auto answer = count_all_tiles(end_map);
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
    Node* starting_node = new Node(start_x, start_y, "RIGHT");
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
    Node* end_node = new Node(start_x, start_y, "");
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

int get_cost(std::vector<Node*> path)
{
    int cost = 0;
    int previous_cost = cost;

    for (Node* n: path)
    {
        if (n->gCost == 0) {continue;}
        if (n->gCost > previous_cost + 999)
        {
            cost += 1001;
            previous_cost = n->gCost;
        }
        else
        {
            cost += 1;
        }
    }

    return cost;
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

int new_get_cost(std::vector<Node*> path)
{
    int cost = 0;
    int previous_cost = cost;

    int current_x = path[0]->x; 
    int current_y = path[0]->y;

    std::string direction = "HORIZONTAL";

    for (Node* n: path)
    {
        if (current_x == n->x && current_y == n->y) {continue;}

        if (direction == "HORIZONTAL" && std::abs(n->y - current_y) !=0)
        {
            direction = "VERTICAL";
            cost = cost + 1001;
            current_x = n->x;
            current_y = n->y;
        }
        else if (direction == "VERTICAL" && std::abs(n->x - current_x) !=0)
        {
            direction = "HORIZONTAL";
            cost = cost + 1001;
            current_x = n->x;
            current_y = n->y;
        }
        else
        {
            cost = cost + 1;
            current_x = n->x;
            current_y = n->y;
        }        
    }
    return cost;
}