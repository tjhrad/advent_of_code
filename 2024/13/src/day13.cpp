
#include "day13.h"

int main()
{
    std::cout << '\n' << "AOC 2024 - DAY 13" << '\n' << std::endl;

    // Read input
    std::string input_file_path = ".\\13\\data\\input.txt";
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
    auto equation_numbers = get_equation_integers(input_data);
    int answer = calculate_total_tokens(equation_numbers);
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
    auto equation_numbers = get_equation_integers(input_data);
    long long answer = calculate_total_tokens_part_two(equation_numbers);
    std::cout << "Answer for part 2: " << answer << std::endl;

    // End timer
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time to complete: " << duration.count() << " milliseconds." << std::endl << std::endl;
}

std::vector<std::vector<int>> get_equation_integers(const std::vector<std::string>& input_data)
{
    std::vector<std::vector<int>> equation_numbers;

    for (int y=0; y<input_data.size(); y=y+4)
    {
        std::string button_a_string = input_data[y];
        std::string button_b_string = input_data[y+1];
        std::string prize_string = input_data[y+2];

        std::vector<std::string> split_a = split_string(button_a_string, ":");
        std::vector<std::string> split_a2 = split_string(split_a[1], ",");
        std::vector<std::string> a_x = split_string(split_a2[0], "+");
        std::vector<std::string> a_y = split_string(split_a2[1], "+");

        equation_numbers.push_back({stoi(a_x[1]), stoi(a_y[1])});

        std::vector<std::string> split_b = split_string(button_b_string, ":");
        std::vector<std::string> split_b2 = split_string(split_b[1], ",");
        std::vector<std::string> b_x = split_string(split_b2[0], "+");
        std::vector<std::string> b_y = split_string(split_b2[1], "+");

        equation_numbers.push_back({stoi(b_x[1]), stoi(b_y[1])});

        std::vector<std::string> split_p = split_string(prize_string, ":");
        std::vector<std::string> split_p2 = split_string(split_p[1], ",");
        std::vector<std::string> p_x = split_string(split_p2[0], "=");
        std::vector<std::string> p_y = split_string(split_p2[1], "=");

        equation_numbers.push_back({stoi(p_x[1]), stoi(p_y[1])});
        
    }

    return equation_numbers;
}

int calculate_total_tokens(const std::vector<std::vector<int>>& input_data)
{
    int total_tokens = 0;

    for (int y=0; y<input_data.size(); y=y+3)
    {
        Eigen::Matrix2d A(2,2);
        A << input_data[y][0], input_data[y+1][0],
            input_data[y][1], input_data[y+1][1];

        Eigen::VectorXd b(2);
        b << input_data[y+2][0], input_data[y+2][1];

        Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);

        float a_tokens = static_cast<float>(x(0));
        float b_tokens = static_cast<float>(x(1));

        if (std::fmod(a_tokens, 1.0) == 0.0 && std::fmod(b_tokens, 1.0) == 0.0)
        {
            total_tokens = total_tokens + (a_tokens*3);
            total_tokens = total_tokens + (b_tokens);
        }      
    }

    return total_tokens;
}

long long calculate_total_tokens_part_two(const std::vector<std::vector<int>>& input_data)
{
    long long total_tokens = 0;

    for (int y=0; y<input_data.size(); y=y+3)
    {
        Eigen::Matrix2d A(2,2);
        A << input_data[y][0], input_data[y+1][0],
            input_data[y][1], input_data[y+1][1];

        long long left_prize = input_data[y+2][0] + 10000000000000;
        long long right_prize = input_data[y+2][1]  + 10000000000000;
        Eigen::VectorXd b(2);
        b << left_prize, right_prize;

        Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);

        long double a_tokens = static_cast<long double>(x(0));
        long double b_tokens = static_cast<long double>(x(1));

        if (std::floor(a_tokens) == a_tokens && std::floor(b_tokens) == b_tokens)
        {
            total_tokens = total_tokens + (a_tokens*3);
            total_tokens = total_tokens + (b_tokens);
        }
        else if (std::abs(std::round(a_tokens) - a_tokens) < 0.001 && std::abs(std::round(b_tokens) - b_tokens) < 0.001 ) // Precision errors...
        {
            total_tokens = total_tokens + (std::round(a_tokens)*3);
            total_tokens = total_tokens + (std::round(b_tokens));
        }

    }

    return total_tokens;
}