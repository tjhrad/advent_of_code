#include "day24.h"

int main(){
  std::cout << '\n' << "AOC 2024 - DAY 24" << '\n' << '\n';

  // Read input
  std::string input_file_path = ".\\24\\data\\input.txt";
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
  auto wires = get_wires(input_data);
  auto gates = get_gates(input_data);
  simulate(wires, gates);
  auto binary = get_binary_output(wires);
  auto answer = binary_2_decimal(binary);
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
  auto wires = get_wires(input_data);
  auto gates = get_gates(input_data);
  auto suspicious_gates = find_suspicious_gates(wires, gates);

  std::set<std::string> sus_gates_sorted;
  for (auto& a : suspicious_gates){
    sus_gates_sorted.insert(a[3]);
  }

  std::string answer = "";
  int i = 0;
  for (auto& sus: sus_gates_sorted){
    if (i < sus_gates_sorted.size()-1){
      answer +=  sus + ",";
    }
    else {
      answer += sus;
    }
    i++;    
  }

  std::cout << "Answer for part 2: " << answer << '\n';

  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " milliseconds." << '\n' << '\n';
}

std::map<std::string, int> get_wires(const std::vector<std::string>& input_data){
  std::map<std::string, int> wires;

  // Initialize wires based on input (0 or 1). -1 if no starting input was given.
  for (std::string s: input_data){
    if (s.find(':') != std::string::npos){
      std::vector<std::string> s_split = split_string(s,": ");
      wires.insert({s_split[0], stoi(s_split[1])});
    }
    else if (s.find("->") != std::string::npos){
      std::vector<std::string> s_split = split_string(s, " -> ");
      if (wires.find(s_split[1]) != wires.end()) {continue;} // If the wire has already been added, continue.
      wires.insert({s_split[1], -1}); // Initialize the empty wires to '-1'.
    }
  }

  return wires;
}

std::vector<std::vector<std::string>> get_gates(const std::vector<std::string>& input_data){
  std::vector<std::vector<std::string>> gates;

  for (auto& s: input_data){
    if (s.find("->") == std::string::npos){continue;}
    std::vector<std::string> s_split = split_string(s, " ");
    std::vector<std::string> current_gate;
    current_gate.push_back(s_split[0]);
    current_gate.push_back(s_split[1]);
    current_gate.push_back(s_split[2]);
    current_gate.push_back(s_split[4]);
    gates.push_back(current_gate);
  }

  return gates;
}

void simulate(std::map<std::string, int>& wires, std::vector<std::vector<std::string>>& gates){
  while(true){
    for (auto iter = gates.begin(); iter != gates.end(); ){
      std::vector<std::string> g = *iter;
      int x = wires.at(g[0]);
      int y = wires.at(g[2]);
      int z = wires.at(g[3]);

      if (x < 0 || y < 0) {
        iter++;
        continue;
      } // If the input wires have not been initialized.

      if (g[1] == "AND"){
        if (x == 1 && y == 1){wires[g[3]] = 1;}
        else {wires[g[3]] = 0;}
        iter = gates.erase(iter);
      }
      else if (g[1] == "XOR"){
        if (x != y){wires[g[3]] = 1;}
        else {wires[g[3]] = 0;}
        iter = gates.erase(iter);
      }
      else if (g[1] == "OR"){
        if (x == 1 || y == 1){wires[g[3]] = 1;}
        else {wires[g[3]] = 0;}
        iter = gates.erase(iter);
      }
      else if (z > 0){
        iter = gates.erase(iter);
      }
      else{
        iter++;
      }
    }
    if (gates.size() <= 0){break;}
  }
}


std::vector<std::vector<std::string>> find_suspicious_gates(std::map<std::string, int>& wires, std::vector<std::vector<std::string>>& gates){
  std::vector<std::vector<std::string>> suspicious_gates;
  //while(true){
  for (auto iter = gates.begin(); iter != gates.end(); iter++){
    std::vector<std::string> g = *iter;
    std::string wire1 = g[0];
    std::string wire2 = g[2];
    std::string oper = g[1];
    std::string out_wire = g[3];

    if (oper == "XOR"){
      if (out_wire[0] == 'z'){continue;}
      if ((wire1[0] == 'x' && wire2[0] == 'y') || (wire2[0] == 'x' && wire1[0] == 'y')) {
        bool is_valid_gate = false;
        for (auto iter_2 = gates.begin(); iter_2 != gates.end(); iter_2++){
          std::vector<std::string> g2 = *iter_2;
          std::string i = g2[0];
          std::string i2 = g2[2];
          std::string oper_2 = g2[1];
          if (i != out_wire && i2 != out_wire){continue;}
          if (oper_2 == "XOR"){
            is_valid_gate = true;
          }
        }
        if (!is_valid_gate){suspicious_gates.push_back(g);}
        continue;
      }
      suspicious_gates.push_back(g);
    }
    if (oper != "XOR"){
      if (out_wire[0] == 'z' && out_wire != "z45"){
        suspicious_gates.push_back(g);
      }
    }
    if (oper == "AND"){
      bool is_valid_gate = false;
      if (wire1 == "x00" || wire1 == "y00") {continue;}
      for (auto iter_2 = gates.begin(); iter_2 != gates.end(); iter_2++){
        std::vector<std::string> g2 = *iter_2;
        std::string i = g2[0];
        std::string i2 = g2[2];
        std::string oper_2 = g2[1];
        if (i != out_wire && i2 != out_wire){continue;}
        if (oper_2 == "OR"){
          is_valid_gate = true;
        }
      }
      if (!is_valid_gate){suspicious_gates.push_back(g);}
      continue;
    }
  }
  return suspicious_gates;
}

std::string get_binary_output(const std::map<std::string, int>& wires){
  std::string binary = "";
  for (auto& w : wires){
    if (w.first[0] == 'z'){
      binary += std::to_string(w.second);
    }
  }
  std::reverse(binary.begin(), binary.end());
  return binary;
}

unsigned long long binary_2_decimal(const std::string& binary_string) {
  unsigned long long decimal = 0;
  unsigned long long power = 0;

  // Iterate through the binary string in reverse order
  for (int i = binary_string.length() - 1; i >= 0; i--) {
    char digit = binary_string[i];

    // Check if the digit is valid (0 or 1)
    if (digit != '0' && digit != '1') {
      std::cout << "Invalid binary string" << '\n';
      return 0;
    }

    // Calculate the decimal value for the current digit
    if (digit == '1') {
      decimal += std::pow(2, power);
    }

    power++;
  }

  return decimal;
}