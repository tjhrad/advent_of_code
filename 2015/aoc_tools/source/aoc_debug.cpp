#include "aoc_debug.h"

void Print(const std::vector<std::vector<int>>& input_data)
{
  for (std::vector<int> vi : input_data)
  {
    for (int i : vi)
    {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }
}

void Print(const std::vector<std::string>& input_data)
{
  for (std::string s: input_data)
  {
    std::cout << s << std::endl;
  }
}

void Print(const std::vector<long long>& input_data)
{
  for (long long ll: input_data)
  {
    std::cout << ll << std::endl;
  }
  std::cout << std::endl;

}

void Print(const std::vector<int>& input_data)
{
  for (int i: input_data)
  {
    std::cout << i << ' ';
  }
  std::cout << '\n';
}

void Print(const std::vector<std::vector<long long>>& input_data)
{
  for (std::vector<long long> vll : input_data)
  {
    for (long long ll : vll)
    {
      std::cout << ll << " ";
    }
    std::cout << std::endl;
  }
}

void Print(const std::vector<std::vector<unsigned long long>>& input_data)
{
  for (std::vector<unsigned long long> vull : input_data)
  {
    for (unsigned long long ull : vull)
    {
      std::cout << ull << " ";
    }
    std::cout << std::endl;
  }
}

void Print(const std::vector<std::vector<char>>& input_data)
{
  for (std::vector<char> vc : input_data)
  {
    for (char c : vc)
    {
      std::cout << c << " ";
    }
    std::cout << std::endl;
  }
}

void Print(const std::multimap<char,std::vector<int>>& input_data)
{
  for (const auto& pair : input_data)
  {
    std::cout << "Key: " << pair.first << ", Values: ";
    for (const auto& value : pair.second)
    {
      std::cout << value << " ";
    }
    std::cout << std::endl;
  }
}