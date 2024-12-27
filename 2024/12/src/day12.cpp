
#include "day12.h"
#include "Plot.h"

int main()
{
  std::cout << '\n' << "AOC 2024 - DAY 12" << '\n' << std::endl;

  // Read input
  std::string input_file_path = ".\\12\\data\\input.txt";
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
  int total_price = 0;
  std::vector<std::vector<int>> used_indices;

  for (int y=0; y<input_data.size(); y++)
  {
    for (int x=0; x<input_data[0].size(); x++)
    {
      bool index_already_used = false;
      if (!used_indices.empty())
      {
        for (std::vector<int> vi: used_indices)
        {
          if (vi[0] == y && vi[1] == x) {index_already_used = true;}
        }
      }
      
      if (index_already_used) {continue;}

      Plot p(input_data, y, x);
      std::vector<std::vector<int>> plot_coords = p.get_plot_coordinates();
      total_price = total_price + p.get_price();
      //std::cout << "Plot: " << p.get_plot_letter() << " Area: " << p.get_area() << " Perimeter: " << p.get_perimeter() << " Price: " << p.get_price() << " Total Price: " << total_price << std::endl;
      for (std::vector<int> vi : plot_coords) {used_indices.push_back({vi[0],vi[1]});}

    }
  }

  auto answer = total_price;
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
  int total_price = 0;
  std::vector<std::vector<int>> used_indices;

  for (int y=0; y<input_data.size(); y++)
  {
    for (int x=0; x<input_data[0].size(); x++)
    {
      bool index_already_used = false;
      if (!used_indices.empty())
      {
        for (std::vector<int> vi: used_indices)
        {
          if (vi[0] == y && vi[1] == x) {index_already_used = true;}
        }
      }
      
      if (index_already_used) {continue;}

      Plot p(input_data, y, x);
      std::vector<std::vector<int>> plot_coords = p.get_plot_coordinates();
      total_price = total_price + p.get_price_with_discount();
      //std::cout << "Plot: " << p.get_plot_letter() << " Area: " << p.get_area() << " Sides: " << p.get_sides() << " Price: " << p.get_price() << " Total Price: " << total_price << std::endl;
      for (std::vector<int> vi : plot_coords) {used_indices.push_back({vi[0],vi[1]});}

    }
  }

  auto answer = total_price;
  std::cout << "Answer for part 2: " << answer << std::endl;

  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " milliseconds." << std::endl << std::endl;
}
