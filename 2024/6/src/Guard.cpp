#include "Guard.h"

Guard::Guard(const std::vector<std::string>& input_map)
{
    is_done_patrolling = false;
    map = input_map;
    starting_map = map;
    map_of_obstructions = input_map;
    set_starting_position();
}

int Guard::get_x() {return x_location;}
int Guard::get_y() {return y_location;}

std::vector<std::string> Guard::get_map() {return map;}
std::vector<std::string> Guard::get_obstruction_map() {return map_of_obstructions;}
std::vector<std::vector<int>> Guard::get_indices_of_walls() {return indices_of_walls;}

void Guard::set_starting_position()
{
    for(int y=0; y<map.size(); y++)
    {
        std::size_t x_up = map[y].find('^');
        std::size_t x_right = map[y].find('>');
        std::size_t x_left = map[y].find('<');
        std::size_t x_down = map[y].find('v');

        if (x_up == std::string::npos && 
            x_right == std::string::npos && 
            x_left == std::string::npos && 
            x_down == std::string::npos) 
            {continue;}

        if (x_up != std::string::npos)
        {
            walking_direction = "UP";
            x_location = x_up;
            y_location = y;
        }

        if (x_right != std::string::npos)
        {
            walking_direction = "RIGHT";
            x_location = x_right;
            y_location = y;
        }

        if (x_left != std::string::npos)
        {
            walking_direction = "LEFT";
            x_location = x_left;
            y_location = y;
        }

        if (x_down != std::string::npos)
        {
            walking_direction = "DOWN";
            x_location = x_down;
            y_location = y;
        }
        starting_y_location = y_location;
        starting_x_location = x_location;
    }
}

bool Guard::check_if_obstruction_is_infinite()
{
    bool is_infinite = false;
    bool is_done = false;

    int current_x_location = starting_x_location;
    int current_y_location = starting_y_location;
    int obstruction_x_location;
    int obstruction_y_location;

    std::string starting_walking_direction = "UP";
    std::string temporary_walking_direction = starting_walking_direction;

    std::vector<std::vector<int>> temporary_wall_indices;

    while (!is_done)
    {
        int smallest_y_distance;
        int smallest_x_distance;

        int temporary_x_index = -1;
        int temporary_y_index = -1;

        bool is_wall_found = false;

        if (temporary_walking_direction == "UP")
        {
            smallest_y_distance = std::abs(current_y_location+1);   
            // Find the y,x indices of the first wall the guard would encounter.
            for (std::vector<int> vi : indices_of_walls)
            {
                if (vi[1] == current_x_location && vi[0] < current_y_location)
                {
                    if (std::abs(current_y_location-vi[0]) < smallest_y_distance)
                    {
                        is_wall_found = true;
                        smallest_y_distance = std::abs(current_y_location-vi[0]);
                        temporary_y_index = vi[0];
                        temporary_x_index = vi[1];
                    }
                }
            }
            if (is_wall_found)
            {
                if(!temporary_wall_indices.empty())
                {
                    for (std::vector<int> vi : temporary_wall_indices)
                    {
                        if (vi[0] == temporary_y_index && vi[1] == temporary_x_index && vi[2] == 0)
                        {
                            return true;
                        }
                    }
                }
                temporary_wall_indices.push_back({temporary_y_index,temporary_x_index,0});
                current_x_location = temporary_x_index;
                current_y_location = temporary_y_index + 1;

                temporary_walking_direction = "RIGHT";
                is_wall_found = false;
                continue;
            }
            if (!is_wall_found)
            {
                return false;
            }
        }
        else if (temporary_walking_direction == "RIGHT")
        {
            smallest_x_distance = std::abs(int(map[0].length()-current_x_location));
            // Find the y,x indices of the first wall the guard would encounter.
            for (std::vector<int> vi : indices_of_walls)
            {
                if (vi[0] == current_y_location && vi[1] > current_x_location)
                {
                    if (std::abs(current_x_location-vi[1]) < smallest_x_distance)
                    {
                        is_wall_found = true;
                        smallest_x_distance = std::abs(current_x_location-vi[1]);
                        temporary_y_index = vi[0];
                        temporary_x_index = vi[1];
                    }
                }
            }
            if (is_wall_found)
            {
                if(!temporary_wall_indices.empty())
                {
                    for (std::vector<int> vi : temporary_wall_indices)
                    {
                        if (vi[0] == temporary_y_index && vi[1] == temporary_x_index && vi[2] == 1)
                        {
                            return true;
                        }
                    }
                }
                temporary_wall_indices.push_back({temporary_y_index,temporary_x_index,1});
                current_x_location = temporary_x_index - 1;
                current_y_location = temporary_y_index;
                temporary_walking_direction = "DOWN";
                is_wall_found = false;
                continue;
            }
            if (!is_wall_found)
            {
                return false;
            }
        }
        else if (temporary_walking_direction == "DOWN")
        {
            smallest_y_distance = std::abs(int(map.size() - current_y_location));
            // Find the y,x indices of the first wall the guard would encounter.
            for (std::vector<int> vi : indices_of_walls)
            {
                if (vi[1] == current_x_location && vi[0] > current_y_location)
                {
                    if (std::abs(current_y_location-vi[0]) < smallest_y_distance)
                    {
                        is_wall_found = true;
                        smallest_y_distance = std::abs(current_y_location-vi[0]);
                        temporary_y_index = vi[0];
                        temporary_x_index = vi[1];
                    }
                }
            }
            if (is_wall_found)
            {
                if(!temporary_wall_indices.empty())
                {
                    for (std::vector<int> vi : temporary_wall_indices)
                    {
                        if (vi[0] == temporary_y_index && vi[1] == temporary_x_index && vi[2] == 2)
                        {
                            return true;
                        }
                    }
                }
                temporary_wall_indices.push_back({temporary_y_index,temporary_x_index,2});
                current_x_location = temporary_x_index;
                current_y_location = temporary_y_index - 1;

                temporary_walking_direction = "LEFT";
                is_wall_found = false;
                continue;
            }
            if (!is_wall_found)
            {
                return false;
            }

        }
        else if (temporary_walking_direction == "LEFT")
        {
            smallest_x_distance = std::abs(current_x_location+1);
            // Find the y,x indices of the first wall the guard would encounter.
            for (std::vector<int> vi : indices_of_walls)
            {
                if (vi[0] == current_y_location && vi[1] < current_x_location)
                {
                    if (std::abs(current_x_location-vi[1]) < smallest_x_distance)
                    {
                        is_wall_found = true;
                        smallest_x_distance = std::abs(current_x_location-vi[1]);
                        temporary_y_index = vi[0];
                        temporary_x_index = vi[1];
                    }
                }
            }

            if (is_wall_found)
            {
                if(!temporary_wall_indices.empty())
                {
                    for (std::vector<int> vi : temporary_wall_indices)
                    {
                        if (vi[0] == temporary_y_index && vi[1] == temporary_x_index && vi[2] == 3)
                        {
                            return true;
                        }
                    }
                }
                temporary_wall_indices.push_back({temporary_y_index,temporary_x_index,3});
                current_x_location = temporary_x_index + 1;
                current_y_location = temporary_y_index;

                temporary_walking_direction = "UP";
                is_wall_found = false;
                continue;
            }
            if (!is_wall_found)
            {
                return false;
            }
        }
    }  
    return is_infinite;
}

void Guard::patrol_with_obstructions()
{
    patrol();
    std::vector<std::string> patrolled_map = map;
    map = starting_map;
    std::vector<std::string> temporary_map;
    for (int y=0; y<patrolled_map.size(); y++)
    {
        for (int x=0; x<patrolled_map[0].size(); x++)
        {
            if (patrolled_map[y][x] == 'X' && starting_map[y][x] != '^')
            {
                map[y][x] = '#';
                find_indices_of_walls();
                
                if (check_if_obstruction_is_infinite())
                {
                    map_of_obstructions[y][x] = 'O';
                }
                map = starting_map;
            }
        }
    }

}

void Guard::patrol()
{
    is_done_patrolling = false;
    while (!is_done_patrolling)
    {
        if (walking_direction == "UP")
        {
            map[y_location][x_location] = 'X';
            if (y_location-1 < 0) 
            {
                is_done_patrolling = true;
                continue;
            }
            if (map[y_location-1][x_location] == '#')
            {
                walking_direction = "RIGHT";
            }
            else
            {
                y_location = y_location - 1;
            }
        }
        else if (walking_direction == "RIGHT")
        {
            map[y_location][x_location] = 'X';
            if (x_location+1 >= map[0].length()) 
            {
                is_done_patrolling = true;
                continue;
            }
            if (map[y_location][x_location+1] == '#')
            {
                walking_direction = "DOWN";
            }
            else
            {
                x_location = x_location + 1;
            }
        }
        else if (walking_direction == "DOWN")
        {
            map[y_location][x_location] = 'X';
            if (y_location+1 >= map.size()) 
            {
                is_done_patrolling = true;
                continue;
            }
            if (map[y_location+1][x_location] == '#')
            {
                walking_direction = "LEFT";
            }
            else
            {
                y_location = y_location + 1;
            }
        }
        else if (walking_direction == "LEFT")
        {
            map[y_location][x_location] = 'X';
            if (x_location-1 < 0) 
            {
                is_done_patrolling = true;
                continue;
            }
            if (map[y_location][x_location-1] == '#')
            {
                walking_direction = "UP";
            }
            else
            {
                x_location = x_location - 1;
            }
        }
    }
}

int Guard::get_number_of_positions_visited()
{
    int count = 0;
    for (std::string s : map)
    {
        for (char c : s)
        {
            if (c == 'X'){count++;}
        }
    }
    return count;
}

int Guard::get_number_of_obstructions()
{
    int count = 0;
    for (std::string s : map_of_obstructions)
    {
        for (char c : s)
        {
            if (c == 'O'){count++;}
        }
    }
    return count;
}

void Guard::find_indices_of_walls()
{
    if (!indices_of_walls.empty())
    {
        indices_of_walls.clear();
    }
    
    for (int y=0; y<map.size(); y++)
    {  
        for (int x=0; x<map[0].length(); x++)
        {
            if (map[y][x] == '#')
            {
                std::vector<int> indices;
                indices_of_walls.push_back({y,x});
            }
        }
    }
}