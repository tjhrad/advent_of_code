
#include "day5.h"


int main()
{
  std::cout << '\n' << "AOC 2024 - DAY 5" << '\n' << std::endl;

  // Read input
  std::string input_file_path = ".\\5\\data\\input.txt";
  std::vector<std::string> input_file_data = read_text_file(input_file_path);

  // Part 1
  int answer_one = part_one(input_file_data);
  std::cout << "Answer for part 1: " << answer_one << std::endl << std::endl;

  // Part 2
  int answer_two = part_two(input_file_data);
  std::cout << "Answer for part 2: " << answer_two << std::endl << std::endl;

  return 0;
}

int part_one(const std::vector<std::string>& input_data)
{
  // Start timer
  auto start = std::chrono::high_resolution_clock::now();

  std::cout << "PART 1" << std::endl;

  // Code here
  int answer = 0;
  std::multimap<int, int> page_ordering_rules = get_page_ordering_rules(input_data);
  std::vector<std::vector<int>> pages_to_produce = get_pages_to_produce(input_data);
  std::vector<std::vector<int>> correctly_ordered_pages = return_correctly_ordered_updates(pages_to_produce,page_ordering_rules);
  answer = add_middle_page_numbers(correctly_ordered_pages);

  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " microseconds." << std::endl;

  return answer;
}

int part_two(const std::vector<std::string>& input_data)
{
  // Start timer
  auto start = std::chrono::high_resolution_clock::now();

  std::cout << "PART 2" << std::endl;
  
  // Code here
  int answer = 0;
  std::multimap<int, int> page_ordering_rules = get_page_ordering_rules(input_data);
  std::vector<std::vector<int>> pages_to_produce = get_pages_to_produce(input_data);
  std::vector<std::vector<int>> incorrectly_ordered_pages = return_incorrectly_ordered_updates(pages_to_produce,page_ordering_rules);
  std::vector<std::vector<int>> corrected_pages = correct_incorrectly_ordered_updates(incorrectly_ordered_pages,page_ordering_rules);
  answer = add_middle_page_numbers(corrected_pages);
  
  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " microseconds." << std::endl;

  return answer;
}

std::multimap<int, int> get_page_ordering_rules(const std::vector<std::string>& input_data)
{
  std::multimap<int, int> page_ordering_rules;

  for (std::string s : input_data)
  {
    if (s.find('|') == std::string::npos)
    {
      continue;
    }

    std::vector<std::string> strings = split_string(s,"|");
    int key = std::stoi(strings[0]);
    int value = std::stoi(strings[1]);
    page_ordering_rules.insert(std::pair<int,int>(key,value));
  }

  return page_ordering_rules;
}

std::vector<std::vector<int>> get_pages_to_produce(const std::vector<std::string>& input_data)
{
  std::vector<std::vector<int>> pages_to_produce;

  for (std::string s : input_data)
  {
    if (s.find(',') == std::string::npos)
    {
      continue;
    }

    std::vector<std::string> strings = split_string(s,",");
    std::vector<int> integers;

    for (std::string s2 : strings)
    {
      integers.push_back(std::stoi(s2));
    }
    pages_to_produce.push_back(integers);
  }
  
  return pages_to_produce;
}

std::vector<std::vector<int>> return_correctly_ordered_updates(const std::vector<std::vector<int>>& input_data, const std::multimap<int, int>& ordering_rules)
{
  std::vector<std::vector<int>> correctly_ordered_updates;

  for (std::vector<int> vi : input_data)
  {
    bool is_correctly_ordered = true;
    for (int i=0; i<vi.size(); i++)
    {
      // If the page is not in the ordering rules keys, continue.
      if(ordering_rules.find(vi[i]) == ordering_rules.end())
      {
        continue;
      }

      for (int x = 0; x<vi.size(); x++)
      {
        if (x == i)
        {
          continue;
        }

        auto range = ordering_rules.equal_range(vi[i]);
        for (auto it = range.first; it != range.second; ++it) 
        {
          // If the order breaks the rules, stop the loop early and move on.
          if (it->second == vi[x] && x < i)
          {
            is_correctly_ordered = false;
            break;
          }
        }

        if (!is_correctly_ordered)
        {
          break;
        }

      }
      
    }

    if (is_correctly_ordered)
    {
      correctly_ordered_updates.push_back(vi);
    }
    
  }

  return correctly_ordered_updates;
}

int add_middle_page_numbers (const std::vector<std::vector<int>>& input_data)
{
  int sum = 0;

  for (std::vector<int> vi : input_data)
  {
    int middle_index = (vi.size()-1)/2;
    sum = sum + vi[middle_index];
  }

  return sum;
}

std::vector<std::vector<int>> return_incorrectly_ordered_updates(const std::vector<std::vector<int>>& input_data, const std::multimap<int, int>& ordering_rules)
{
  std::vector<std::vector<int>> incorrectly_ordered_updates;

  for (std::vector<int> vi : input_data)
  {
    bool is_correctly_ordered = true;
    for (int i=0; i<vi.size(); i++)
    {
      // If the page is not in the ordering rules keys, continue.
      if(ordering_rules.find(vi[i]) == ordering_rules.end())
      {
        continue;
      }

      for (int x = 0; x<vi.size(); x++)
      {
        if (x == i)
        {
          continue;
        }

        auto range = ordering_rules.equal_range(vi[i]);
        for (auto it = range.first; it != range.second; ++it) 
        {
          // If the order breaks the rules, stop the loop early and move on.
          if (it->second == vi[x] && x < i)
          {
            is_correctly_ordered = false;
            break;
          }
        }

        if (!is_correctly_ordered)
        {
          break;
        }

      }
      
    }

    if (!is_correctly_ordered)
    {
      incorrectly_ordered_updates.push_back(vi);
    }
    
  }

  return incorrectly_ordered_updates;
}

std::vector<std::vector<int>> correct_incorrectly_ordered_updates(const std::vector<std::vector<int>>& input_data, const std::multimap<int, int>& ordering_rules)
{
  std::vector<std::vector<int>> corrected_pages;

  for (std::vector<int> vi : input_data)
  {
    for (int i=0; i<vi.size(); i++)
    {
      // If the page is not in the ordering rules keys, continue.
      if(ordering_rules.find(vi[i]) == ordering_rules.end())
      {
        continue;
      }

      for (int x = 0; x<vi.size(); x++)
      {
        if (x == i)
        {
          continue;
        }

        auto range = ordering_rules.equal_range(vi[i]);
        for (auto it = range.first; it != range.second; ++it) 
        {
          // If the order breaks the rules, swap the pages and move on.
          if (it->second == vi[x] && x < i)
          {
            std::swap(vi[x],vi[i]);
            break;
          }
        }
      } 
    }
    corrected_pages.push_back(vi);
  }

  return corrected_pages;
}