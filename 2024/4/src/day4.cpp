
#include "day4.h"


int main()
{
  std::string input_file_path = ".\\4\\data\\input.txt";
  std::string word = "XMAS";

  std::vector<std::string> input_file_data = read_text_file(input_file_path);

  // Part 1
  auto start = std::chrono::high_resolution_clock::now();

  int number_of_occurences = count_occurences_in_data(input_file_data, word);
  std::cout << "Answer for part 1: " << number_of_occurences << '\n';
  
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " microseconds." << std::endl;

  // Part 2
  start = std::chrono::high_resolution_clock::now();

  int number_of_X_MAS = count_occurences_of_X_MAS(input_file_data);
  std::cout << "Answer for part 2: " << number_of_X_MAS << '\n';

  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " microseconds." << std::endl;

  return 0;
}

int count_occurences_in_data(const std::vector<std::string>& input_data, const std::string& input_string)
{
  int number_of_occurences = 0;

  int number_rows = input_data.size();
  int number_columns = input_data[0].length();

  for (int x=0; x<number_columns; x++)
  {
    for (int y=0; y<number_rows; y++)
    {
      if (input_data[x][y] != input_string[0])
        continue;
      

      for (int z=1; z<input_string.length(); z++)
      {
        if (y+z >= number_rows)
          break;

        if (input_data[x][y+z] != input_string[z])
          break;

        if (z == input_string.length()-1)
          number_of_occurences++;
      }

      for (int z=1; z<input_string.length(); z++)
      {
        if (y-z < 0)
          break;

        if (input_data[x][y-z] != input_string[z])
          break;

        if (z == input_string.length()-1)
          number_of_occurences++;
      }

      for (int z=1; z<input_string.length(); z++)
      {
        if (x+z >= number_columns)
          break;

        if (input_data[x+z][y] != input_string[z])
          break;

        if (z == input_string.length()-1)
          number_of_occurences++;
      }

      for (int z=1; z<input_string.length(); z++)
      {
        if (x-z < 0)
          break;

        if (input_data[x-z][y] != input_string[z])
          break;

        if (z == input_string.length()-1)
          number_of_occurences++;
      }

      for (int z=1; z<input_string.length(); z++)
      {
        if (x+z >= number_columns || y+z >= number_rows)
          break;

        if (input_data[x+z][y+z] != input_string[z])
          break;

        if (z == input_string.length()-1)
          number_of_occurences++;
      }

      for (int z=1; z<input_string.length(); z++)
      {
        if (x-z < 0 || y-z < 0)
          break;

        if (input_data[x-z][y-z] != input_string[z])
          break;

        if (z == input_string.length()-1)
          number_of_occurences++;
      }

      for (int z=1; z<input_string.length(); z++)
      {
        if (x-z < 0 || y+z >= number_rows)
          break;

        if (input_data[x-z][y+z] != input_string[z])
          break;

        if (z == input_string.length()-1)
          number_of_occurences++;
      }

      for (int z=1; z<input_string.length(); z++)
      {
        if (y-z < 0 || x+z >= number_rows)
          break;

        if (input_data[x+z][y-z] != input_string[z])
          break;

        if (z == input_string.length()-1)
          number_of_occurences++;
      }
      
    }
  }

  return number_of_occurences;
}

int count_occurences_of_X_MAS(const std::vector<std::string>& input_data)
{
  int number_of_occurences = 0;

  int number_rows = input_data.size();
  int number_columns = input_data[0].length();

  for (int x=0; x<number_columns; x++)
  {
    for (int y=0; y<number_rows; y++)
    {
      if (input_data[x][y] != 'A')
        continue;

      if (x-1 < 0 || y-1 < 0 || x+1 >= number_rows || y+1 >= number_columns)
        continue;
      
      // Check to see if there are valid characters in the X pattern
      if (input_data[x+1][y+1] != 'M' && input_data[x+1][y+1] != 'S' )
        continue;

      if (input_data[x-1][y-1] != 'M' && input_data[x-1][y-1] != 'S' )
        continue;

      if (input_data[x+1][y-1] != 'M' && input_data[x+1][y-1] != 'S' )
        continue;

      if (input_data[x-1][y+1] != 'M' && input_data[x-1][y+1] != 'S' )
        continue;

      // Check to see if the orientation of the charaters is correct.
      if(input_data[x+1][y+1] == 'M' && input_data[x-1][y-1] != 'S')
        continue;

      if(input_data[x+1][y+1] == 'S' && input_data[x-1][y-1] != 'M')
        continue;

      if(input_data[x+1][y-1] == 'M' && input_data[x-1][y+1] != 'S')
        continue;

      if(input_data[x+1][y-1] == 'S' && input_data[x-1][y+1] != 'M')
        continue;
      
      number_of_occurences++;
    }
  }

  return number_of_occurences;
}

