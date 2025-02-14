#include "day22.h"

int X_MAX = 0;
int Y_MAX = 0;

int main() {
  std::cout << "AOC 2016 - DAY 22" << '\n';

  std::string input_file_path = "./22/data/input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto nodes = CreateNodes(input_data);
  auto answer = CountValidNodes(nodes);
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto nodes = CreateNodes(input_data);
  Print(CreateMap(nodes));
  auto answer = 0;
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

int CountValidNodes(const std::map<std::string, std::vector<int>>& nodes) {
  int num_valid = 0;
  for (auto& n:nodes) {
    for (auto& n2:nodes) {
      if (n.first == n2.first) {
        continue;
      }
      auto& n_data = n.second;
      auto& n2_data = n2.second;

      if (n_data[1] > 0 && n_data[1] <= n2_data[2]) {
        num_valid++;
      }

    }
  }
  return num_valid;
}

std::vector<std::string> CreateMap(const std::map<std::string, std::vector<int>>& nodes) {
  std::vector<std::string> map;
  std::string goal_key = "x" + std::to_string(X_MAX) + "y" + std::to_string(0);
  auto goal_data = nodes.at(goal_key);
  for (int y=0; y <= Y_MAX; y++) {
    std::string row = "";
    for (int x=0; x <= X_MAX; x++) {
      std::string key = "x" + std::to_string(x) + "y" + std::to_string(y);
      auto& data = nodes.at(key);

      if (x == X_MAX && y == 0) {
        row += 'G';
      } else if (0 == x && 0 == y) {
        row += 'S';
      } else if (data[1] == 0) {
        row += '_';
      } else if (100 < data[0] && 80 < data[3]) {
        row += '#';
      } else {
        row += '.';
      }
    }
    map.emplace_back(row);
  }
  return map;
}

std::map<std::string, std::vector<int>> CreateNodes(const std::vector<std::string>& input_data) {
  std::map<std::string, std::vector<int>> nodes;
  for (auto line : input_data) {
    if ('/' == line[0]) {
      line = RemoveMultipleSpaces(line);
      auto split = SplitString(line, " ");

      auto node_name_split = SplitString(split[0], "-");
      int x_pos = stoi(RemoveNondigits(node_name_split[1]));
      int y_pos = stoi(RemoveNondigits(node_name_split[2]));

      if (y_pos > Y_MAX) {
        Y_MAX = y_pos;
      }

      if (x_pos > X_MAX) {
        X_MAX = x_pos;
      }

      std::string node_name = node_name_split[1] + node_name_split[2];
      int size = stoi(RemoveNondigits(split[1]));
      int used = stoi(RemoveNondigits(split[2]));
      int avail = stoi(RemoveNondigits(split[3]));
      int use_percent = stoi(RemoveNondigits(split[4]));

      nodes.emplace(node_name, std::vector<int>{size, used, avail, use_percent});
    }
  }
  return nodes;
}

// Function to remove non-digit characters from a string
std::string RemoveNondigits(const std::string& input) {
  std::string result;
  for (char c : input) {
      if (std::isdigit(c)) {
          result += c;
      }
  }
  return result;
}

std::string RemoveMultipleSpaces(const std::string& input) {
  std::istringstream iss(input);
  std::ostringstream oss;
  std::string word;
  
  while (iss >> word) {
      if (!oss.str().empty()) {
          oss << " "; // Add a single space between words
      }
      oss << word;
  }
  
  return oss.str();
}