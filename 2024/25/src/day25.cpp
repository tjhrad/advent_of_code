#include "day25.h"

int main(){
  std::cout << '\n' << "AOC 2024 - DAY 25" << '\n' << '\n';

  // Read input
  std::string input_file_path = ".\\25\\data\\input.txt";
  std::vector<std::string> input_file_data = read_text_file(input_file_path);

  // Part 1
  part_one(input_file_data);

  // No Part 2!
  
  return 0;
}

void part_one(const std::vector<std::string>& input_data){
  // Start timer
  auto start = std::chrono::high_resolution_clock::now();
  std::cout << "PART 1" << '\n';

  // Code here
  auto keys = get_keys(input_data);
  auto locks = get_locks(input_data);
  auto answer = count_valid_combinations(keys, locks);
  std::cout << "Answer for part 1: " << answer << '\n';

  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " milliseconds." << '\n' << '\n';
}

std::vector<std::vector<int>> get_keys(const std::vector<std::string>& input_data){
  std::vector<std::vector<int>> keys;

  for (int i=0; i<input_data.size(); i = i + 8){
    std::vector<int> row;
    if (input_data[i+6][0] != '#'){continue;}
    for (int y=0; y<input_data[0].size(); y++){ // Iterate over columns.
      int column_count = 0;
      for (int x=i+5; x>i; x--){
        if (input_data[x][y] == '#'){column_count++;}
      }
      row.push_back(column_count);
    }
    keys.push_back(row);
  }

  return keys;
}

std::vector<std::vector<int>> get_locks(const std::vector<std::string>& input_data){
  std::vector<std::vector<int>> locks;

  for (int i=0; i<input_data.size(); i = i + 8){
    std::vector<int> row;
    if (input_data[i][0] != '#'){continue;}
    for (int y=0; y<input_data[0].size(); y++){ // Iterate over columns.
      int column_count = 0;
      for (int x=i+1; x<i+6; x++){
        if (input_data[x][y] == '#'){column_count++;}
      }
      row.push_back(column_count);
    }
    locks.push_back(row);
  }

  return locks;
}

int count_valid_combinations(const std::vector<std::vector<int>>& keys, const std::vector<std::vector<int>>& locks){
  int count = 0;
  for (const auto& key : keys){ // Test all key - lock combinations.
    for (const auto& lock : locks){
      bool is_valid = true;
      for (int i=0; i<key.size(); i++){
        if ((key[i]+lock[i])>5){
          is_valid=false;
        }
      }
      if (is_valid){
      count++;
    }
    } 
  }
  return count;
}