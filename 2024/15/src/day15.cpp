
#include "day15.h"

std::set<std::pair<int,int>> temporary_box_coordinates;

int main()
{
    std::cout << '\n' << "AOC 2024 - DAY 15" << '\n' << std::endl;

    // Read input
    std::string input_file_path = ".\\15\\data\\input.txt";
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
    auto map_and_instructions = get_map_and_instructions(input_data);
    auto map = map_and_instructions.first;
    auto instructions = map_and_instructions.second;
    auto wall_coordinates = get_wall_coordinates(map);
    auto box_coordinates = get_box_coordinates(map);
    auto robot_coordinates = get_robot_coordinates(map);
    move_robot(robot_coordinates, box_coordinates, wall_coordinates, instructions, map);

    
    int answer = sum_gps_coordinates(box_coordinates);
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
    auto map_and_instructions = get_map_and_instructions(input_data);
    auto expanded_map = get_expanded_map(map_and_instructions.first);
    auto instructions = map_and_instructions.second;

    auto wall_coordinates = get_wall_coordinates(expanded_map);
    auto box_coordinates = get_box_coordinates(expanded_map);
    auto robot_coordinates = get_robot_coordinates(expanded_map);

    move_robot_expanded(robot_coordinates, box_coordinates, wall_coordinates, instructions, expanded_map);

    auto answer = sum_gps_coordinates(box_coordinates);
    std::cout << "Answer for part 2: " << answer << std::endl;

    // End timer
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time to complete: " << duration.count() << " milliseconds." << std::endl << std::endl;
}

std::pair<std::vector<std::string>, std::vector<std::string>> get_map_and_instructions(const std::vector<std::string>& input_data)
{
    std::vector<std::string> map;
    std::vector<std::string> instructions;

    for (const std::string& s: input_data)
    {
        if (s[0] == ' ') {continue;} // Ignore lines that aren't map or instructions

        if (s[0] == '#') // Map
        {
            map.push_back(s);
        }
        else // Instructions
        {
            instructions.push_back(s);
        }
    }

    return std::make_pair(map, instructions);
}

std::set<std::pair<int, int>> get_wall_coordinates(const std::vector<std::string>& input_map)
{
    std::set<std::pair<int, int>> wall_coordinates;

    for (int y=0; y<input_map.size(); y++)
    {
        for (int x=0; x<input_map[0].size(); x++)
        {
            if (input_map[y][x] == '#')
            {
                wall_coordinates.insert({x,y});
            }
        }
    }

    return wall_coordinates;
}

std::set<std::pair<int, int>> get_box_coordinates(const std::vector<std::string>& input_map)
{
    std::set<std::pair<int, int>> box_coordinates;

    for (int y=0; y<input_map.size(); y++)
    {
        for (int x=0; x<input_map[0].size(); x++)
        {
            if (input_map[y][x] == 'O')
            {
                box_coordinates.insert({x,y});
            }
            else if (input_map[y][x] == '[')
            {
                box_coordinates.insert({x,y});
            }
        }
    }

    return box_coordinates;
}

std::pair<int, int> get_robot_coordinates(const std::vector<std::string>& input_map)
{
    std::pair<int, int> coordinates;

    for (int y=0; y<input_map.size(); y++)
    {
        for (int x=0; x<input_map[0].size(); x++)
        {
            if (input_map[y][x] == '@')
            {
                coordinates = std::make_pair(x,y);//.insert({x,y});
                break;
            }
        }
    }

    return coordinates;
}

void move_robot(std::pair<int, int>& robot_coordinates, std::set<std::pair<int,int>>& box_coordinates, std::set<std::pair<int,int>>& wall_coordinates, const std::vector<std::string>& instructions, std::vector<std::string>& map)
{
    std::vector up_vector = {0,-1};//{-1,0};
    std::vector down_vector = {0,1};//{1,0};
    std::vector right_vector = {1,0};//{0,1};
    std::vector left_vector = {-1,0};//{0,-1};

    for (const std::string& s:instructions)
    {
        for (const char& instruction: s)
        {
            if (instruction == '^')
            {
                update_all(up_vector[0], up_vector[1], robot_coordinates, box_coordinates, wall_coordinates, instructions, map);
            }
            else if (instruction == '>')
            {
                update_all(right_vector[0], right_vector[1], robot_coordinates, box_coordinates, wall_coordinates, instructions, map);
            }
            else if (instruction == 'v')
            {
                update_all(down_vector[0], down_vector[1], robot_coordinates, box_coordinates, wall_coordinates, instructions, map);
            }
            else if (instruction == '<')
            {
                update_all(left_vector[0], left_vector[1], robot_coordinates, box_coordinates, wall_coordinates, instructions, map);
            }
        }
    }
}

void move_robot_expanded(std::pair<int, int>& robot_coordinates, std::set<std::pair<int,int>>& box_coordinates, std::set<std::pair<int,int>>& wall_coordinates, const std::vector<std::string>& instructions, std::vector<std::string>& map)
{
    std::vector up_vector = {0,-1};//{-1,0};
    std::vector down_vector = {0,1};//{1,0};
    std::vector right_vector = {1,0};//{0,1};
    std::vector left_vector = {-1,0};//{0,-1};

    for (const std::string& s:instructions)
    {
        for (const char& instruction: s)
        {
            if (instruction == '^')
            {
                update_all_expanded(up_vector[0], up_vector[1], robot_coordinates, box_coordinates, wall_coordinates, instructions, map);
            }
            else if (instruction == '>')
            {
                update_all_expanded(right_vector[0], right_vector[1], robot_coordinates, box_coordinates, wall_coordinates, instructions, map);
            }
            else if (instruction == 'v')
            {
                update_all_expanded(down_vector[0], down_vector[1], robot_coordinates, box_coordinates, wall_coordinates, instructions, map);
            }
            else if (instruction == '<')
            {
                update_all_expanded(left_vector[0], left_vector[1], robot_coordinates, box_coordinates, wall_coordinates, instructions, map);
            }
        }
    }
}

void update_all(int x_direction, int y_direction, std::pair<int, int>& robot_coordinates, std::set<std::pair<int,int>>& box_coordinates, std::set<std::pair<int,int>>& wall_coordinates, const std::vector<std::string>& instructions, std::vector<std::string>& map)
{
    std::vector<std::vector<int>> temporary_box_coordinates;
    int new_x = robot_coordinates.first + x_direction;
    int new_y = robot_coordinates.second + y_direction;

    if (wall_coordinates.find({new_x, new_y}) != wall_coordinates.end()) 
    {
        return;
    }
    else if (box_coordinates.find({new_x, new_y}) != box_coordinates.end()) 
    {
        // perform wall checks and move boxes and robot if possible.
        temporary_box_coordinates.push_back({new_x, new_y}); // Add wall to temporary walls
        bool is_done = false;
        int temp_x = new_x;
        int temp_y = new_y;

        while (!is_done) // Loop until you find a wall or all of the boxes.
        {
            temp_x = temp_x + x_direction;
            temp_y = temp_y + y_direction;

            if (wall_coordinates.find({temp_x, temp_y}) != wall_coordinates.end())
            {
                // Don't move boxes or robot.
                is_done = true;
                temporary_box_coordinates.clear();
                return;
            }
            else if (box_coordinates.find({temp_x, temp_y}) != box_coordinates.end())
            {
                // Add boxes to the temporary vector.
                temporary_box_coordinates.push_back({temp_x, temp_y});
            }
            else
            {
                // Move robot and boxes.
                is_done = true;
                // Move Robot.
                map[robot_coordinates.second][robot_coordinates.first] = '.';
                map[new_y][new_x] = '@';
                robot_coordinates.first = new_x;
                robot_coordinates.second = new_y;

                //Move boxes.
                if (temporary_box_coordinates.empty()) {continue;}
                for (std::vector<int> vi : temporary_box_coordinates)
                {
                    // Remove from the box coordinates
                    std::pair<int, int> to_remove = std::make_pair(vi[0], vi[1]);
                    auto it = box_coordinates.find(to_remove); 
                    if (it != box_coordinates.end()) {box_coordinates.erase(it);}
                }
                for (std::vector<int> vi : temporary_box_coordinates)
                {
                    map[vi[1] + y_direction][vi[0] + x_direction] = 'O';   
                    box_coordinates.insert({vi[0] + x_direction, vi[1] + y_direction});
                }
                temporary_box_coordinates.clear();
            }
        }
        return;
    }
    else
    {
        // Update map and robot coordinates.
        map[robot_coordinates.second][robot_coordinates.first] = '.';
        map[new_y][new_x] = '@';
        robot_coordinates.first = new_x;
        robot_coordinates.second = new_y;
    }
}

void update_all_expanded(int x_direction, int y_direction, std::pair<int, int>& robot_coordinates, std::set<std::pair<int,int>>& box_coordinates, std::set<std::pair<int,int>>& wall_coordinates, const std::vector<std::string>& instructions, std::vector<std::string>& map)
{
    int new_x = robot_coordinates.first + x_direction;
    int new_y = robot_coordinates.second + y_direction;

    if (map[new_y][new_x] == '#') 
    {
        return;
    }
    else if (map[new_y][new_x] == '[' || map[new_y][new_x] == ']') 
    {
        int temp_x = new_x;
        int temp_y = new_y;

        if (map[new_y][new_x] == ']')
        {
            temp_x = temp_x - 1;
        }
        find_all_boxes(temp_x, temp_y, x_direction, y_direction, map);

        std::set<std::pair<int, int>> new_coordinates;
        for (std::pair<int,int> p: temporary_box_coordinates)
        {
            if (y_direction == 0 && x_direction != 1 && map[p.second + y_direction][p.first + x_direction] == '#')
            {
                temporary_box_coordinates.clear();
                new_coordinates.clear();
                break;
            }
            else if (y_direction == 0 && x_direction == 1 && map[p.second + y_direction][p.first + x_direction + 1] == '#')
            {
                temporary_box_coordinates.clear();
                new_coordinates.clear();
                break;
            }
            else if (y_direction != 0 && (map[p.second + y_direction][p.first + x_direction] == '#' || map[p.second + y_direction][p.first + x_direction + 1] == '#'))
            {
                temporary_box_coordinates.clear();
                new_coordinates.clear();
                break;
            }
            else
            {
                new_coordinates.insert(std::make_pair(p.first + x_direction, p.second + y_direction));
            }
        }

        if (!temporary_box_coordinates.empty() || !new_coordinates.empty())
        {
            //Move boxes.
            for (std::pair<int,int> p : temporary_box_coordinates)
            {   
                // Remove from the box coordinates
                std::pair<int, int> to_remove = std::make_pair(p.first, p.second);
                map[to_remove.second][to_remove.first] = '.';
                map[to_remove.second][to_remove.first + 1] = '.';
                auto it = box_coordinates.find(to_remove); 
                if (it != box_coordinates.end()) {box_coordinates.erase(it);}
            }
            for (std::pair<int,int> p : temporary_box_coordinates)
            {
                map[p.second + y_direction][p.first + x_direction] = '[';
                map[p.second + y_direction][p.first + x_direction + 1] = ']'; 
                box_coordinates.insert({p.first + x_direction, p.second + y_direction});
            }

            temporary_box_coordinates.clear();
            // Move robot and boxes.
            map[robot_coordinates.second][robot_coordinates.first] = '.';
            map[new_y][new_x] = '@';
            robot_coordinates.first = new_x;
            robot_coordinates.second = new_y;
            return;
        }

        temporary_box_coordinates.clear();
        new_coordinates.clear();
        return;
    }
    else
    {
        // Update map and robot coordinates.
        map[robot_coordinates.second][robot_coordinates.first] = '.';
        map[new_y][new_x] = '@';
        robot_coordinates.first = new_x;
        robot_coordinates.second = new_y;
    }
}

void find_all_boxes(int x_start, int y_start, int x_direction, int y_direction, std::vector<std::string>& map)
{
    if (map[y_start][x_start] == '#') {return;}
    if (map[y_start][x_start] == '.') {return;}
    if (y_direction != 0)
    {
        if (map[y_start][x_start] == '[')
        {
            temporary_box_coordinates.insert(std::make_pair(x_start, y_start));
            find_all_boxes(x_start + x_direction, y_start + y_direction, x_direction, y_direction, map);
            if (map[y_start + y_direction][x_start + 1] == '[')
            {
                find_all_boxes(x_start + x_direction + 1, y_start + y_direction, x_direction, y_direction, map);
            }
            if (map[y_start + y_direction][x_start - 1] == '[')
            {
                find_all_boxes(x_start + x_direction - 1, y_start + y_direction, x_direction, y_direction, map);
            }
        }
        else if (map[y_start][x_start] == ']')
        {
            temporary_box_coordinates.insert(std::make_pair(x_start - 1, y_start));
            find_all_boxes(x_start + x_direction - 1, y_start + y_direction, x_direction, y_direction, map);
            if (map[y_start][x_start + 1] == '[')
            {
                temporary_box_coordinates.insert(std::make_pair(x_start + 1, y_start));
                find_all_boxes(x_start + x_direction + 1, y_start + y_direction, x_direction, y_direction, map);
            }
        }
    }
    else
    {
        if (x_direction == 1)
        {
            if (map[y_start][x_start] == '[')
            {
                temporary_box_coordinates.insert(std::make_pair(x_start, y_start));
                find_all_boxes(x_start + x_direction + 1, y_start + y_direction, x_direction, y_direction, map);
            }
            else if (map[y_start][x_start] == ']')
            {
                temporary_box_coordinates.insert(std::make_pair(x_start - 1, y_start));
                find_all_boxes(x_start + x_direction - 1, y_start + y_direction, x_direction, y_direction, map);
            }
        }
        else
        {
            if (map[y_start][x_start] == '[')
            {
                temporary_box_coordinates.insert(std::make_pair(x_start, y_start));
                find_all_boxes(x_start + x_direction, y_start + y_direction, x_direction, y_direction, map);
            }
            else if (map[y_start][x_start] == ']')
            {
                temporary_box_coordinates.insert(std::make_pair(x_start - 1, y_start));
                find_all_boxes(x_start + x_direction - 1, y_start + y_direction, x_direction, y_direction, map);
            }
        }
        
    }
}

int sum_gps_coordinates(const std::set<std::pair<int,int>>& box_coordinates)
{
    int sum = 0;

    for (std::pair<int,int> p : box_coordinates)
    {
        sum = sum + p.second*100 + p.first;
    }

    return sum;
}

std::vector<std::string> get_expanded_map(const std::vector<std::string>& input_data)
{
    std::vector<std::string> expanded_map;

    for (int y=0; y<input_data.size(); y++)
    {
        std::string current_string = "";
        for (int x=0; x<input_data[0].size(); x++)
        {
            if (input_data[y][x] == '#')
            {
                current_string += "##";
            }
            else if (input_data[y][x] == 'O')
            {
                current_string += "[]";
            }
            else if (input_data[y][x] == '.')
            {
                current_string += "..";
            }
            else if (input_data[y][x] == '@')
            {
                current_string += "@.";
            }
        }  
        expanded_map.push_back(current_string);
    }

    return expanded_map;
}