#include "day23.h"

int main(){
  std::cout << '\n' << "AOC 2024 - DAY 23" << '\n' << '\n';

  // Read input
  std::string input_file_path = ".\\23\\data\\input.txt";
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
  std::unordered_map<std::string, std::unordered_set<std::string>> map_of_computers = get_adjacency_list(input_data);
  auto triangles = find_triangles(map_of_computers);

  int count = 0;
  for (const auto& triangle : triangles){
    for (const auto& computer : triangle){
      if (computer[0] == 't'){
        count++;
        break;
      }
    }
  }

  auto answer = count;
  std::cout << "Answer for part 1: " << answer << '\n';

  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " milliseconds." << '\n' << '\n';
}

void part_two(const std::vector<std::string>& input_data){
  // Start timer
  auto start = std::chrono::high_resolution_clock::now();
  std::cout << "PART 1" << '\n';

  // Code here
  std::unordered_map<std::string, std::unordered_set<std::string>> map_of_computers = get_adjacency_list(input_data);
  auto cliques = find_maximal_cliques(map_of_computers);

  int max_size = 0;
  std::unordered_set<std::string> max_clique;
  for (auto clique: cliques){
    if (clique.size() > max_size){
      max_size = clique.size();
      max_clique.clear();
      max_clique = clique;
    }
  }
  std::vector<std::string> max_clique_vector(max_clique.begin(), max_clique.end());

  std::sort(max_clique_vector.begin(), max_clique_vector.end());

  std::string answer = "";
  for (int i=0; i<max_clique_vector.size(); i++){
    answer = answer + max_clique_vector[i];
    if(i != max_clique_vector.size()-1){
      answer = answer + ",";
    }
  }
  std::cout << max_clique.size() << '\n';
  std::cout << "Answer for part 2: " << answer << '\n';

  // End timer
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "Time to complete: " << duration.count() << " milliseconds." << '\n' << '\n';
}

std::unordered_map<std::string, std::unordered_set<std::string>> get_adjacency_list(const std::vector<std::string>& input_data){
  std::unordered_map<std::string, std::unordered_set<std::string>> adjacency_list;

  for (std::string s : input_data){
    std::vector<std::string> split_s = split_string(s, "-");
    adjacency_list[split_s[0]].insert(split_s[1]);
    adjacency_list[split_s[1]].insert(split_s[0]);    
  }

  return adjacency_list;
}

// Finds all sets of three interconnected computers.
std::vector<std::vector<std::string>> find_triangles(const std::unordered_map<std::string, std::unordered_set<std::string>>& adjacency_list){
  std::vector<std::vector<std::string>> triangles;

  for (const auto& [node, neighbors] : adjacency_list) {
    for (const std::string& node_2 : neighbors){
      for (const std::string& node_3 : neighbors){
        // Ignore if there are duplicate nodes.
        if (node_2 == node_3 || node == node_2 || node == node_3) {continue;}

        if (!adjacency_list.at(node_2).count(node_3)){continue;}

        if (triangles.empty()){ // Add the first triangle.
          triangles.push_back({node, node_2, node_3});
        }
        else{
          bool has_triangle_been_added = false;
          for (const std::vector<std::string>& vs: triangles){
            if (std::find(vs.begin(), vs.end(), node) != vs.end() && std::find(vs.begin(), vs.end(), node_2) != vs.end() && std::find(vs.begin(), vs.end(), node_3) != vs.end()){ // Check to see if the triangle has already been added.
                  has_triangle_been_added = true;
            }
          }
          if (!has_triangle_been_added){
            triangles.push_back({node, node_2, node_3});
          }
        }
      }
    }
  }

  return triangles;
}

// Utility function to call Bron–Kerbosch.
std::vector<std::unordered_set<std::string>> find_maximal_cliques(const std::unordered_map<std::string, std::unordered_set<std::string>> &graph) {
  std::unordered_set<std::string> R;
  std::unordered_set<std::string> P;
  std::unordered_set<std::string> X;

  for (const auto &pair : graph) {
    P.insert(pair.first);
  }

  std::vector<std::unordered_set<std::string>> maximalCliques;
  bron_kerbosch(graph, R, P, X, maximalCliques);
  return maximalCliques;
}

// Function to find maximal cliques using the Bron–Kerbosch algorithm.
void bron_kerbosch(const std::unordered_map<std::string, std::unordered_set<std::string>> &graph, std::unordered_set<std::string> R, std::unordered_set<std::string> P, std::unordered_set<std::string> X, std::vector<std::unordered_set<std::string>> &maximalCliques) {
  if (P.empty() && X.empty()) {
    // Found a maximal clique
    maximalCliques.push_back(R);
    return;
  }

  auto P_copy = P; // Copy of P to allow modification during iteration
  for (const auto &v : P_copy) {
    std::unordered_set<std::string> R_new = R;
    R_new.insert(v);

    // P ∩ N(v)
    std::unordered_set<std::string> P_new;
    for (const auto &u : P) {
      if (graph.at(v).count(u)) {
        P_new.insert(u);
      }
    }

    // X ∩ N(v)
    std::unordered_set<std::string> X_new;
    for (const auto &u : X) {
      if (graph.at(v).count(u)) {
        X_new.insert(u);
      }
    }

    bron_kerbosch(graph, R_new, P_new, X_new, maximalCliques);

    // Move v from P to X
    P.erase(v);
    X.insert(v);
  }
}