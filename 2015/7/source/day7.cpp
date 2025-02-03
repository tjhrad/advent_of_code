#include "day7.h"

int main() {
  std::cout << "AOC 2015 - DAY 7" << '\n';

  std::string input_file_path = ".\\7\\data\\input.txt";
  std::vector<std::string> input_file_data = ReadFile(input_file_path);

  PartOne(input_file_data);
  PartTwo(input_file_data);

  return 0;
}

void PartOne(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto gates = GetGates(input_data);
  auto wires = GetStartingWires(input_data);
  Emulate(wires, gates);
  auto answer = wires.at("a");
  std::cout << "Part 1: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void PartTwo(const std::vector<std::string>& input_data) {
  auto start = std::chrono::high_resolution_clock::now();

  // Code here
  auto gates = GetGates(input_data);
  auto wires = GetStartingWires(input_data);
  Emulate(wires, gates);

  auto a_value = wires.at("a");
  gates = GetGates(input_data);
  wires = GetStartingWires(input_data);
  wires["b"] = a_value;
  Emulate(wires, gates);
  
  auto answer = wires.at("a");
  std::cout << "Part 2: " << answer << '\n';

  auto stop = std::chrono::high_resolution_clock::now();
  PrintTime(start, stop);
}

void Emulate(std::map<std::string, unsigned short int>& wires, std::vector<std::vector<std::string>>& gates) {
  while(true){
    for (auto iter = gates.begin(); iter != gates.end(); ){
      std::vector<std::string> g = *iter;
      if (wires.find(g[3]) != wires.end()) {
        iter = gates.erase(iter);
        continue;
      }

      if (g[1] == "AND" || g[1] == "OR") {
        if (g[0] == "1") {
          if (wires.find(g[2]) == wires.end()) {
            iter++;
            continue;
          }
        } else if (wires.find(g[0]) == wires.end() || wires.find(g[2]) == wires.end()) {
          iter++;
          continue;
        }   
      } else if (g[1] == "RSHIFT" || g[1] == "LSHIFT") {
        if (wires.find(g[0]) == wires.end()) {
          iter++;
          continue;
        }
      } else if (g[1] == "NOT") {
        if (wires.find(g[2]) == wires.end()) {
          iter++;
          continue;
        }
      } else if (wires.find(g[0]) == wires.end() && g[1] == "NAN" ) {
        iter++;
        continue;
      }
      
      if (g[1] == "AND") {
        unsigned short int x;
        if (g[0] == "1") {
          x = stoi(g[0]);
        } else {
          x = wires.at(g[0]);
        }
        unsigned short int y = wires.at(g[2]);
        unsigned short int z = x & y;
        wires[g[3]] = z;
        iter = gates.erase(iter);
      } else if (g[1] == "OR") {
        unsigned short int x;
        if (g[0] == "1") {
          x = stoi(g[0]);
        } else {
          x = wires.at(g[0]);
        }
        unsigned short int y = wires.at(g[2]);
        unsigned short int z = x | y;
        wires[g[3]] = z;
        iter = gates.erase(iter);
      } else if (g[1] == "LSHIFT") {
        unsigned short int x = wires.at(g[0]);
        unsigned short int y = stoi(g[2]);
        unsigned short int z = x << y;
        wires[g[3]] = z;
        iter = gates.erase(iter);
      } else if (g[1] == "RSHIFT") {
        unsigned short int x = wires.at(g[0]);
        unsigned short int y = stoi(g[2]);
        unsigned short int z = x >> y;
        wires[g[3]] = z;
        iter = gates.erase(iter);
      } else if (g[1] == "NOT") {
        unsigned short int y = wires.at(g[2]);
        unsigned short int z = ~y;
        wires[g[3]] = z;
        iter = gates.erase(iter);
      } else if (g[1] == "NAN") {
        unsigned short int y = wires.at(g[0]);
        wires[g[3]] = y;
        iter = gates.erase(iter);
      } else {
        iter++;
      }
    }
    if (gates.size() <= 0){break;}
  }
}

std::map<std::string, unsigned short int> GetStartingWires(const std::vector<std::string>& input_data){
  std::map<std::string, unsigned short int> wires;

  for (std::string s: input_data){
    std::vector<std::string> s_split = SplitString(s, " ");
    if(std::isdigit(s[0]) && s_split.size() == 3) {
      unsigned short int num = stoi(s_split[0]);
      wires.insert({s_split[2], num});
    }
  }

  return wires;
}

std::vector<std::vector<std::string>> GetGates(const std::vector<std::string>& input_data){
  std::vector<std::vector<std::string>> gates;

  for (auto& s: input_data) {
    std::vector<std::string> s_split = SplitString(s, " ");
    std::vector<std::string> current_gate;
    if (s.find("AND") != std::string::npos ||
        s.find("OR") != std::string::npos ||
        s.find("LSHIFT") != std::string::npos ||
        s.find("RSHIFT") != std::string::npos) {
      current_gate.push_back(s_split[0]);
      current_gate.push_back(s_split[1]);
      current_gate.push_back(s_split[2]);
      current_gate.push_back(s_split[4]);
    } else if (s.find("NOT") != std::string::npos) {
      current_gate.push_back("NAN");
      current_gate.push_back(s_split[0]);
      current_gate.push_back(s_split[1]);
      current_gate.push_back(s_split[3]);
    } else if (s_split[0] != "1"){
      current_gate.push_back(s_split[0]);
      current_gate.push_back("NAN");
      current_gate.push_back(s_split[0]);
      current_gate.push_back(s_split[2]);
    }
    gates.push_back(current_gate);
  }

  return gates;
}