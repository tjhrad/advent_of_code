
#include "day7.h"

int main()
{
  std::cout << '\n' << "AOC 2024 - DAY 7" << '\n' << std::endl;

  // Read input
  std::string input_file_path = ".\\7\\data\\input.txt";
  std::vector<std::string> input_file_data = read_text_file(input_file_path);

  // Part 1
  long long int answer_one = part_one(input_file_data);
  std::cout << "Answer for part 1: " << answer_one << std::endl << std::endl;

  // Part 2
  long long int answer_two = part_two(input_file_data);
  std::cout << "Answer for part 2: " << answer_two << std::endl << std::endl;

  return 0;
}

long long int part_one(const std::vector<std::string>& input_data)
{
  // Start timer
  auto start = std::chrono::high_resolution_clock::now();

  std::cout << "PART 1" << std::endl;

  // Code here
  std::vector<char> operators = {'+','*'};
  auto equation_answers = return_equation_answers(input_data);
  auto equation_numbers = return_equation_numbers(input_data);
  long long int answer = return_total_calibration_result(equation_numbers, equation_answers, operators);
  
  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " microseconds." << std::endl;

  return answer;
}

long long int part_two(const std::vector<std::string>& input_data)
{
  // Start timer
  auto start = std::chrono::high_resolution_clock::now();

  std::cout << "PART 2" << std::endl;
  
  // Code here
  std::vector<char> operators = {'+','*','|'};
  auto equation_answers = return_equation_answers(input_data);
  auto equation_numbers = return_equation_numbers(input_data);
  long long int answer = return_total_calibration_result(equation_numbers, equation_answers, operators);
  
  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " microseconds." << std::endl;

  return answer;
}

std::vector<long long int> return_equation_answers(const std::vector<std::string>& input_data)
{
  std::vector<long long int> answers;

  for (std::string s : input_data)
  {
    std::vector<std::string> ss = split_string(s,":");
    answers.push_back(std::stoll(ss[0]));
  }
  return answers;
}

std::vector<std::vector<long long int>> return_equation_numbers(const std::vector<std::string>& input_data)
{
  std::vector<std::vector<long long int>> numbers;
  for (std::string s : input_data)
  {
    std::vector<long long int> numbers_for_current_equation;
    std::vector<std::string> ss = split_string(s,":");
    std::vector<std::string> ss2 = split_string(ss[1]," ");
    for (std::string number_string : ss2)
    {
      if (is_string_digits(number_string) && number_string.size() > 0)
      {
        numbers_for_current_equation.push_back(std::stoll(number_string));
      }
    }
    numbers.push_back(numbers_for_current_equation);
  }
  return numbers;
}

long long int return_total_calibration_result(std::vector<std::vector<long long int>>& equation_numbers,std::vector<long long int>& equation_answers, std::vector<char>& operators)
{
  long long int total_calibration_result = 0;
  for (int x=0; x<equation_answers.size(); x++)
  {
    if (check_if_valid_equation(equation_numbers[x], equation_answers[x], operators))
    {
      total_calibration_result = total_calibration_result + equation_answers[x];
    }
  }
  return total_calibration_result;
}

bool check_if_valid_equation(std::vector<long long int>& equation_numbers, long long int answer, std::vector<char>& operators)
{
  bool is_valid = false;

  int number_operators = equation_numbers.size() - 1;
  int number_of_possible_equations = std::pow(operators.size(),number_operators);

  for (int x=0; x<number_of_possible_equations; x++)
  {
    std::string base_n_string = convert_int_to_base_n(x,operators.size());

    // Add trailing 0's
    while (base_n_string.size()<number_operators)
    {
      base_n_string = "0" + base_n_string;
    }

    long long int temporary_solution = equation_numbers[0];
    for (int j=0; j<base_n_string.size(); j++)
    {
      char current_operator = base_n_string[j];
      if (current_operator == '0')
      {
        temporary_solution = temporary_solution + equation_numbers[j+1];
      }
      else if (current_operator == '1')
      {
        temporary_solution = temporary_solution * equation_numbers[j+1];
      }
      else if (current_operator == '2')
      {
        std::string n1_string = std::to_string(temporary_solution);
        std::string n2_string = std::to_string(equation_numbers[j+1]);
        std::string answer_string = n1_string + n2_string;
        temporary_solution = std::stoll(answer_string);
      }
    }

    if (temporary_solution == answer)
    {
      is_valid = true;
      break;
    }
  }

  return is_valid;
}