#ifndef PLOT_H
#define PLOT_H

#include <vector>
#include <string>
#include <iostream>

class Plot
{
    public:
        std::vector<std::vector<int>> plot_coordinates;
        std::vector<std::string> map;
        //std::vector<std::string> plot_map;
        int plot_y;
        int plot_x;
        int price_of_fence;
        int price_with_discount;
        int area = 0;
        int perimeter = 0;
        int number_of_sides = 0;
        char plot_letter;

        Plot (const std::vector<std::string>& input_map, const int starting_y, const int starting_x); // Constructor.
        std::vector<std::vector<int>> get_plot_coordinates();
        int get_price();
        int get_price_with_discount();
        int get_area();
        int get_perimeter();
        int get_sides();
        char get_plot_letter();

    private:
        void find_matching_neighbors(int init_y, int init_x);
        void calculate_price();

};


#endif // PLOT_H