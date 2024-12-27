
#include "day3.h"


int main()
{
  std::string input_file_path = ".\\3\\data\\input.txt";

  std::vector<std::string> input_file_data = read_text_file(input_file_path);

  std::vector<std::vector<int>> mul_instructions = get_mul_instructions(input_file_data);
  std::vector<int> product_vector = multiply_mul_instructions(mul_instructions);

  // Part 1
  int result1 = sum_integers(product_vector);
  std::cout << "Answer for part 1: " << result1 << '\n';

  std::vector<std::string> input_file_data_removed = remove_invalid_instructions(input_file_data);
  std::vector<std::vector<int>> mul_instructions2 = get_mul_instructions(input_file_data_removed);
  std::vector<int> product_vector2 = multiply_mul_instructions(mul_instructions2);

  // Part 2
  int result2 = sum_integers(product_vector2);
  std::cout << "Answer for part 2: " << result2 << '\n';

  return 0;
}

std::vector<std::vector<int>> get_mul_instructions(const std::vector<std::string>& input_data)
{
  std::vector<std::vector<int>> mul_instructions;

  std::string substring = "mul(";

  for (std::string s : input_data)
  {
    std::vector<int> positions;

    int position = s.find(substring, 0);

    while (position != std::string::npos)
    {
      positions.push_back(position);
      position = s.find(substring, position + 1);
    }

    for (int i : positions)
    {
      if (s[i+5] != ',' && s[i+6] != ',' && s[i+7] != ',')
      {
        continue;
      }
      if (s[i+7] != ')' && s[i+8] != ')' && s[i+9] != ')' && s[i+10] != ')' && s[i+11] != ')' && s[i+12] != ')')
      {
        continue;
      }
      int comma_position = s.find(',' , i);
      int close_parenthesis_position = s.find(')' , i);

      int open_parenthesis_position = i+substring.length();
      std::string first_number = s.substr(open_parenthesis_position,comma_position-open_parenthesis_position);
      std::string second_number = s.substr(comma_position+1,close_parenthesis_position-comma_position-1);

      if (!is_string_digits(first_number) || !is_string_digits(second_number))
      {
        continue;
      }

      std::vector<int> numbers_vector;

      int first_number_int = std::stoi(first_number);
      int second_number_int = std::stoi(second_number);

      numbers_vector.push_back(first_number_int);
      numbers_vector.push_back(second_number_int);

      mul_instructions.push_back(numbers_vector);

    }
  }
  return mul_instructions;
}

std::vector<int> multiply_mul_instructions(const std::vector<std::vector<int>>& input_data)
{
  std::vector<int> products;

  for (std::vector<int> input : input_data)
  {
    int product = input[0]*input[1];
    products.push_back(product);
  }
  return products;
}

std::vector<std::string> remove_invalid_instructions(const std::vector<std::string>& input_data)
{
  std::vector<std::string> valid_instructions;

  // Not an ideal solution, but I just decided to combine all of the input strings into one large string. 
  // ¯\_(ツ)_/¯
  std::vector<std::string> combined_strings;

  std::string combined_s;
  for (std::string s : input_data)
  {
    combined_s = combined_s + s;
  }
  combined_strings.push_back(combined_s);

  std::string do_substring = "do()";
  std::string dont_substring = "don't()";

  for (std::string s : combined_strings)
  {
    int dont_position = s.find(dont_substring);
    int do_position = s.find(do_substring, dont_position);

    while (dont_position != std::string::npos && do_position != std::string::npos)
    {
      s.erase(dont_position, do_position-dont_position);
      dont_position = s.find(dont_substring);
      do_position = s.find(do_substring,dont_position);
      if (do_position == std::string::npos && dont_position != std::string::npos)
      {
        int length = s.length();
        s.erase(dont_position,length-dont_position);
      }
    }
    valid_instructions.push_back(s);
  }
  return valid_instructions;
}