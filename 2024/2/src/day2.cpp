
#include "day2.h"


int main()
{
  std::string input_file_path = ".\\2\\data\\input.txt";

  std::vector<std::string> input_file_data = read_text_file(input_file_path);

  std::vector<std::vector<int>> integer_vectors = convert_strings_to_integers(input_file_data);

  // Part 1
  std::vector<int> safety_vector = get_safety_vector(integer_vectors);
  int result1 = sum_integers(safety_vector);
  std::cout << "Answer for part 1: " << result1 << '\n';

  // Part 2
  std::vector<int> safety_vector2 = get_safety_vector_with_dampener(integer_vectors);
  int result2 = sum_integers(safety_vector2);
  std::cout << "Answer for part 2: " << result2 << '\n';

  return 0;
}

std::vector<std::vector<int>> convert_strings_to_integers(const std::vector<std::string>& input_data)
{
  std::vector<std::vector<int>> output_vector;
  for (std::string s : input_data)
  {
    output_vector.push_back(get_integers_from_string(s));
  }

  return output_vector;
}

std::vector<int> get_safety_vector(const std::vector<std::vector<int>>& input_data)
{
  std::vector<int> safety_vector;

  for (std::vector<int> vi : input_data)
  {
    safety_vector.push_back(calculate_safety_value(vi));
  }

  return safety_vector;
}

// Returns 1 if safe and 0 if unsafe.
int calculate_safety_value(const std::vector<int>& input_data)
{
  int starting_integer;
  int last_integer;
  int count = 0;
  int last_difference = 0;
  for (int i : input_data)
  {
    if (count != 0)
    {
      int abs_difference = std::abs(last_integer - i);
      int current_difference = last_integer - i;

      if (abs_difference < 1 || abs_difference > 3)
      {
        return 0;
      }
      if (last_difference != 0)
      {
        if (last_difference > 0 && current_difference < 0)
        {
          return 0;
        }
        if (last_difference < 0 && current_difference > 0)
        {
          return 0;
        }
      }

      last_integer = i;
      last_difference = current_difference;
    }
    else
    {
      starting_integer = i;
      last_integer = i;
    }
    count++;
  }
  return 1;
}

std::vector<int> get_safety_vector_with_dampener(const std::vector<std::vector<int>>& input_data)
{
  std::vector<int> safety_vector;

  for (std::vector<int> vi : input_data)
  {
    int safety_value = calculate_safety_value(vi);
    if (safety_value == 0)
    {
      for (int x = 0; x < std::size(vi); x++)
      {
        std::vector<int> new_input = vi;
        new_input.erase(new_input.begin() + x);
        int new_safety_value = calculate_safety_value(new_input);
        if (new_safety_value == 1)
        {
          safety_value = 1;
        }
      }
    }
    safety_vector.push_back(safety_value);
  }
  return safety_vector;
}