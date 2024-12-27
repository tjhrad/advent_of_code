
#include "day14.h"

int main()
{
    std::cout << '\n' << "AOC 2024 - DAY 14" << '\n' << std::endl;

    // Read input
    std::string input_file_path = ".\\14\\data\\input.txt";
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
    auto coords_and_velocities = get_starting_coordinates_and_velocities(input_data);
    auto starting_coordinates = coords_and_velocities.first;
    auto starting_velocities = coords_and_velocities.second;
    int width = 101;
    int height = 103;

    auto end_coordinates = get_end_coordinates(starting_coordinates, starting_velocities, 100, width, height);    
    int answer = calculate_safety_score(end_coordinates, width, height);
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
    auto coords_and_velocities = get_starting_coordinates_and_velocities(input_data);
    auto starting_coordinates = coords_and_velocities.first;
    auto starting_velocities = coords_and_velocities.second;
    int width = 101;
    int height = 103;
    auto answer = count_until_xmas_tree(starting_coordinates, starting_velocities, width, height);
    std::cout << "Answer for part 2: " << answer << std::endl;

    // End timer
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time to complete: " << duration.count() << " milliseconds." << std::endl << std::endl;
}

std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> get_starting_coordinates_and_velocities(const std::vector<std::string>& input_data)
{
    std::vector<std::vector<int>> starting_coordinates;
    std::vector<std::vector<int>> starting_velocities;

    for (std::string s: input_data)
    {
        std::vector<std::string> s_split = split_string(s, " ");
        std::vector<std::string> s_split2 = split_string(s_split[0], "=");
        std::vector<std::string> s_split3 = split_string(s_split2[1], ",");

        starting_coordinates.push_back({stoi(s_split3[0]), stoi(s_split3[1])});

        std::vector<std::string> s_split_vel = split_string(s_split[1], "=");
        std::vector<std::string> s_split_vel2 = split_string(s_split_vel[1], ",");

        starting_velocities.push_back({stoi(s_split_vel2[0]), stoi(s_split_vel2[1])});
    }

    return std::make_pair(starting_coordinates, starting_velocities);
}

std::vector<std::vector<int>> get_end_coordinates(const std::vector<std::vector<int>>& starting_coordinates, const std::vector<std::vector<int>>& starting_velocities, const int number_of_seconds, const int width, const int height)
{
    std::vector<std::vector<int>> end_coordinates;

    for (int y=0; y< starting_coordinates.size(); y++)
    {
        int x_current = starting_coordinates[y][0];
        int y_current = starting_coordinates[y][1];

        int x_velocity = starting_velocities[y][0];
        int y_velocity = starting_velocities[y][1];

        for (int count = 0; count<number_of_seconds; count++)
        {
            if (x_current + x_velocity >= width)
            {
                x_current = x_current + x_velocity - width;
            }
            else if (x_current + x_velocity < 0)
            {
                x_current = x_current + x_velocity + width;
            }
            else
            {
                x_current = x_current + x_velocity;
            }

            if (y_current + y_velocity >= height)
            {
                y_current = y_current + y_velocity - height;
            }
            else if (y_current + y_velocity < 0)
            {
                y_current = y_current + y_velocity + height;
            }
            else
            {
                y_current = y_current + y_velocity;
            }
        }
        end_coordinates.push_back({x_current,y_current});
    }
    return end_coordinates;
}

int calculate_safety_score(const std::vector<std::vector<int>>& end_coordinates, int width, int height)
{
    int safety_score = 0;
    int middle_x = (width-1)/2; // 5
    int middle_y = (height-1)/2; // 3
    int top_left_count = 0;
    int top_right_count = 0;
    int bottom_left_count = 0;
    int bottom_right_count = 0;

    for (std::vector<int> vi : end_coordinates)
    {
        if (vi[0] < middle_x && vi[1] < middle_y)
        {
            top_left_count++;
        }
        else if (vi[0] < middle_x && vi[1] > middle_y)
        {
            bottom_left_count++;
        }
        else if (vi[0] > middle_x && vi[1] > middle_y)
        {
            bottom_right_count++;
        }
        else if (vi[0] > middle_x && vi[1] < middle_y)
        {
            top_right_count++;
        }
    }

    safety_score = top_left_count * top_right_count * bottom_left_count * bottom_right_count;

    return safety_score;
}

// Not an efficient method to find the tree, but it works.
int count_until_xmas_tree(const std::vector<std::vector<int>>& starting_coordinates, const std::vector<std::vector<int>>& starting_velocities, const int width, const int height)
{
    std::vector<std::vector<int>> end_coordinates;
    int seconds_until_tree = 0;

    bool is_tree_found = false;

    end_coordinates = starting_coordinates;

    int most_close_robots = 0;
    while (!is_tree_found)
    {
        seconds_until_tree++;
        for (int y=0; y < end_coordinates.size(); y++)
        {
            int x_current = end_coordinates[y][0];
            int y_current = end_coordinates[y][1];

            int x_velocity = starting_velocities[y][0];
            int y_velocity = starting_velocities[y][1];

            if (x_current + x_velocity >= width)
            {
                end_coordinates[y][0] = x_current + x_velocity - width;
            }
            else if (x_current + x_velocity < 0)
            {
                end_coordinates[y][0] = x_current + x_velocity + width;
            }
            else
            {
                end_coordinates[y][0] = x_current + x_velocity;
            }

            if (y_current + y_velocity >= height)
            {
                end_coordinates[y][1] = y_current + y_velocity - height;
            }
            else if (y_current + y_velocity < 0)
            {
                end_coordinates[y][1] = y_current + y_velocity + height;
            }
            else
            {
                end_coordinates[y][1] = y_current + y_velocity;
            }
        }

        int count_of_close_robots = 0;
        for (std::vector<int> vi: end_coordinates)
        {
            for (std::vector<int> vi2: end_coordinates)
            {
                if (vi[0] == vi2[0] && std::abs(vi[1] - vi2[1]) < 28 && vi[1] != vi2[1])
                {
                    count_of_close_robots++;
                }
            }
            if (count_of_close_robots > most_close_robots)
            {
                most_close_robots = count_of_close_robots;
            }
            count_of_close_robots = 0;
        }
         
        if (most_close_robots > 25)
        {
            std::cout << "TREE FOUND!" << std::endl;
            is_tree_found = true;
            print_vector(return_image(end_coordinates, width, height));
        }
        count_of_close_robots = 0;
    }

    return seconds_until_tree;
}

std::vector<std::vector<char>> return_image(const std::vector<std::vector<int>>& end_coordinates, int width, int height)
{
    std::vector<std::vector<char>> image(height, std::vector<char>(width, ' '));

    for (std::vector<int> vi : end_coordinates)
    {
        image[vi[1]][vi[0]] = 'X';
    }

    return image;
}