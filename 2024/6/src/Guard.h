#ifndef GUARD_H
#define GUARD_H

#include <vector>
#include <string>
#include <iostream>

class Guard 
{
  public:
    int x_location;
    int y_location;
    int starting_x_location;
    int starting_y_location;
    std::string walking_direction;
    std::vector<std::string> map;
    std::vector<std::string> starting_map;
    std::vector<std::string> map_of_obstructions;
    std::vector<std::vector<int>> indices_of_walls;
    bool is_done_patrolling;
    Guard (const std::vector<std::string>& input_map); // Constructor.

    int get_x();
    int get_y();

    std::vector<std::string> get_map();
    std::vector<std::string> get_obstruction_map();

    std::vector<std::vector<int>> get_indices_of_walls();

    void patrol();
    void patrol_with_obstructions();
    void find_indices_of_walls();

    bool check_if_obstruction_is_infinite();

    int get_number_of_positions_visited();
    int get_number_of_obstructions();

  private:
    void set_starting_position();
};

#endif // GUARD_H