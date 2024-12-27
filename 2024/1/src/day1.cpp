
#include "day1.h"


int main()
{
  std::string input_file_path = ".\\1\\data\\input.txt";

  std::vector<std::string> input_file_data = read_text_file(input_file_path);

  std::vector<std::vector<int>> sorted_integer_vectors = split_into_two_sorted_integer_vectors(input_file_data);

  std::vector<int> distances =  get_distances(sorted_integer_vectors);
  int result1 = sum_integers(distances);
  std::cout << "Answer for part 1: " << result1 << '\n';

  std::vector<int> similarity_scores = get_similarity_scores(sorted_integer_vectors);
  int result2 = sum_integers(similarity_scores);
  std::cout << "Answer for part 2: " << result2 << '\n';


  return 0;
}

std::vector<std::vector<int>> split_into_two_sorted_integer_vectors(const std::vector<std::string>& input_data)
{
  std::vector<std::vector<int>> integer_vectors;
  std::vector<int> integer_vector1;
  std::vector<int> integer_vector2;

  for (std::string s : input_data)
  {
    std::vector<int> integers = get_integers_from_string(s);
    integer_vector1.push_back(integers[0]);
    integer_vector2.push_back(integers[1]);
  }

  std::sort(integer_vector1.begin(),integer_vector1.end());
  std::sort(integer_vector2.begin(),integer_vector2.end());

  integer_vectors.push_back(integer_vector1);
  integer_vectors.push_back(integer_vector2);

  return integer_vectors;
}

std::vector<int> get_distances(const std::vector<std::vector<int>>& input_data)
{
  std::vector<int> distances;

  int number_of_distances = std::size(input_data[0]);

  for (int x=0; x<number_of_distances; x++)
  {
    distances.push_back(std::abs(input_data[0][x]-input_data[1][x]));
  }

  return distances;
}

std::vector<int> get_similarity_scores(const std::vector<std::vector<int>>& input_data)
{
  std::vector<int> similarity_scores;
  for (int i : input_data[0])
  {
    int same_number_count = 0;
    for (int y : input_data[1])
    {
      if (i == y)
      {
        same_number_count = same_number_count + 1;
      }
    }
    similarity_scores.push_back(i*same_number_count);
  }
  return similarity_scores;
}
