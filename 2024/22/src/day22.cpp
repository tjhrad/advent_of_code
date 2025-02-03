#include "day22.h"

int main(){
  std::cout << '\n' << "AOC 2024 - DAY 22" << '\n' << '\n';

  // Read input
  std::string input_file_path = ".\\22\\data\\input.txt";
  std::vector<std::string> input_file_data = read_text_file(input_file_path);

  // Part 1
  part_one(input_file_data);

  // Part 2
  part_two(input_file_data);

  return 0;
}

void part_one(const std::vector<std::string>& input_data){
  // Start timer
  auto start = std::chrono::high_resolution_clock::now();
  std::cout << "PART 1" << '\n';

  // Code here
  unsigned long long answer = 0;
  for (auto s :input_data){
    answer = answer + find_secret(stoull(s), 2000);
  }
  std::cout << "Answer for part 1: " << answer << '\n';

  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " milliseconds." << '\n' << '\n';
}

void part_two(const std::vector<std::string>& input_data){
  // Start timer
  auto start = std::chrono::high_resolution_clock::now();
  std::cout << "PART 2" << '\n';

  // Code here
  std::vector<std::vector<unsigned long long>> secrets;
  for (auto s :input_data){
    secrets.push_back(find_all_prices(stoull(s), 2000));
  }

  std::map<std::string, unsigned long long> global_sale_prices;
  for (auto vull: secrets){
    add_prices_to_global(vull, global_sale_prices);
  }

  std::string key_of_max = "";
  unsigned long long max_price = 0;
  for (const auto& pair : global_sale_prices) {
    if (pair.second > max_price){
      max_price = pair.second;
      key_of_max = pair.first;
    }
  }

  std::cout << key_of_max << " Price: " << max_price << '\n';
  auto answer = max_price;
  std::cout << "Answer for part 2: " << answer << '\n';

  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " milliseconds." << '\n' << '\n';
}

unsigned long long find_secret(const unsigned long long& starting_number, int num){
  unsigned long long secret = starting_number;

  for (int x=0; x<num; x++){
    unsigned long long result = secret * 64;
    secret = secret ^ result;
    secret = secret & (16777216ULL - 1); //secret = secret % MOD;

    result = static_cast<unsigned long long>(std::floor(secret >> 5)); // Same as dividing by 32
    secret = secret ^ result;
    secret = secret & (16777216ULL - 1);

    result = secret * 2048;
    secret = secret ^ result;
    secret = secret & (16777216ULL - 1);
  }
  return secret;
}

std::vector<unsigned long long> find_all_prices(const unsigned long long& starting_number, int num){
  std::vector<unsigned long long> all_prices;
  unsigned long long secret = starting_number;
  all_prices.push_back(secret % 10); // % 10 will get the last digit in the number (The price).

  for (int x=0; x<num; x++){
    unsigned long long result = secret * 64;
    secret = secret ^ result;
    secret = secret & (16777216ULL - 1);

    result = static_cast<unsigned long long>(std::floor(secret >> 5));
    secret = secret ^ result;
    secret = secret & (16777216ULL - 1);

    result = secret * 2048;
    secret = secret ^ result;
    secret = secret & (16777216ULL - 1);
    all_prices.push_back(secret % 10);
  }

  return all_prices;
}

void add_prices_to_global(const std::vector<unsigned long long>& prices, std::map<std::string, unsigned long long>& global_sale_prices){
  std::map<std::string, unsigned long long> local_sale_prices;

  for (int i=0; i<prices.size()-4; i++){
    int diff_1 = prices[i+1] - prices[i];
    int diff_2 = prices[i+2] - prices[i+1];
    int diff_3 = prices[i+3] - prices[i+2];
    int diff_4 = prices[i+4] - prices[i+3];

    std::string key = std::to_string(diff_1) + "," + std::to_string(diff_2) + "," + std::to_string(diff_3) + "," + std::to_string(diff_4);

    // If you have already encountered the sequence, skip over it. (only sell once.)
    if (local_sale_prices.find(key) != local_sale_prices.end()){continue;}

    local_sale_prices.insert(std::make_pair(key, prices[i+4]));
    if (global_sale_prices.find(key) != global_sale_prices.end()){
      global_sale_prices[key] = global_sale_prices[key] + prices[i+4];
    }
    else{
      global_sale_prices.insert(std::make_pair(key, prices[i+4]));
    }
  }

}