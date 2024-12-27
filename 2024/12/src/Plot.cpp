#include "Plot.h"

Plot::Plot(const std::vector<std::string>& input_map, const int starting_y, const int starting_x)
{
    plot_y = starting_y;
    plot_x = starting_x;
    map = input_map;
    plot_letter = map[plot_y][plot_x];
    //plot_map(map.size());

    //plot_map[plot_y][plot_x] = plot_letter;
    area++;
    plot_coordinates.push_back({plot_y,plot_x});
    find_matching_neighbors(plot_y,plot_x);
    calculate_price();
}

std::vector<std::vector<int>> Plot::get_plot_coordinates() {return plot_coordinates;}
int Plot::get_price() {return price_of_fence;}
int Plot::get_price_with_discount() {return area*number_of_sides;}
int Plot::get_area() {return area;}
int Plot::get_perimeter() {return perimeter;}
int Plot::get_sides() {return number_of_sides;}
char Plot::get_plot_letter() {return plot_letter;}

void Plot::find_matching_neighbors(int init_y, int init_x)
{
    std::vector up_vector = {-1,0};
    std::vector down_vector = {1,0};
    std::vector right_vector = {0,1};
    std::vector left_vector = {0,-1};

    int new_x;
    int new_y;

    int up_x = init_x + up_vector[1];
    int up_y = init_y + up_vector[0];
    int down_x = init_x + down_vector[1];
    int down_y = init_y + down_vector[0];
    int right_x = init_x + right_vector[1];
    int right_y = init_y + right_vector[0];
    int left_x = init_x + left_vector[1];
    int left_y = init_y + left_vector[0];

    // Corner cases
    if (up_y < 0 && left_x < 0)
    {
        number_of_sides++;
    }
    if (up_y < 0 && right_x >= map[0].size())
    {
        number_of_sides++;
    }
    if (down_y >= map.size() && left_x < 0)
    {
        number_of_sides++;
    }
    if (down_y >= map.size() && right_x >= map[0].size())
    {
        number_of_sides++;
    }

    if (right_x >= map[0].size())
    {
        if (up_y >= 0)
        {
            if(map[up_y][up_x] != plot_letter)
            {
                number_of_sides++;
            }
        }

        if (down_y < map.size())
        {
            if(map[down_y][down_x] != plot_letter)
            {
                number_of_sides++;
            }
        }
    }

    if (left_x < 0)
    {
        if (up_y >= 0)
        {
            if(map[up_y][up_x] != plot_letter)
            {
                number_of_sides++;
            }
        }

        if (down_y < map.size())
        {
            if(map[down_y][down_x] != plot_letter)
            {
                number_of_sides++;
            }
        }
    }

    if (up_y < 0)
    {
        if (left_x >= 0)
        {
            if(map[left_y][left_x] != plot_letter)
            {
                number_of_sides++;
            }
        }

        if (right_x < map[0].size())
        {
            if(map[right_y][right_x] != plot_letter)
            {
                number_of_sides++;
            }
        }
    }

    if (down_y >= map.size())
    {
        if (left_x >= 0)
        {
            if(map[left_y][left_x] != plot_letter)
            {
                number_of_sides++;
            }
        }

        if (right_x < map[0].size())
        {
            if(map[right_y][right_x] != plot_letter)
            {
                number_of_sides++;
            }
        }
    }

    // 00 
    // 0X
    if (up_y >= 0 && left_x >= 0)
    {
        if (map[up_y][up_x] != plot_letter && map[left_y][left_x] != plot_letter) 
        {
            //std::cout << "Corner top left" << std::endl;
            number_of_sides++;
        }
    }

    // 00 
    // X0
    if (up_y >= 0 && right_x < map[0].size())
    {
        if (map[up_y][up_x] != plot_letter && map[right_y][right_x] != plot_letter) 
        {
            //std::cout << "Corner top right" << std::endl;
            number_of_sides++;
        }
    }
    
    // 0X 
    // 00
    if (down_y < map.size() && left_x >= 0)
    {
        if (map[down_y][down_x] != plot_letter && map[left_y][left_x] != plot_letter) 
        {
            //std::cout << "Corner bottom left" << std::endl;
            number_of_sides++;
        }
    }

    // X0 
    // 00
    if (down_y < map.size() && right_x < map[0].size())
    {
        if (map[down_y][down_x] != plot_letter && map[right_y][right_x] != plot_letter) 
        {
            //std::cout << "Corner bottom right" << std::endl;
            number_of_sides++;
        }
    }

    // 0X 
    // XX
    if (up_y >= 0 && left_x >= 0 && init_y-1 >= 0 && init_x-1 >= 0)
    {
        if (map[up_y][up_x] == plot_letter && map[left_y][left_x] == plot_letter && map[init_y-1][init_x-1] != plot_letter) 
        {
            //std::cout << "Inside top left" << std::endl;
            number_of_sides++;
        }
    }

    // X0 
    // XX
    if (up_y >= 0 && right_x < map[0].size() && init_y-1 >= 0 && init_x+1 < map[0].size())
    {
        
        if (map[up_y][up_x] == plot_letter && map[right_y][right_x] == plot_letter  && map[init_y-1][init_x+1] != plot_letter) 
        {
            //std::cout << "Inside top right" << std::endl;
            number_of_sides++;
        }
    }
    
    // XX 
    // 0X
    if (down_y < map.size() && left_x >= 0 && init_y+1 < map.size() && init_x-1 >= 0)
    {
        if (map[down_y][down_x] == plot_letter && map[left_y][left_x] == plot_letter && map[init_y+1][init_x-1] != plot_letter) 
        {
            //std::cout << "Inside bottom left" << std::endl;
            number_of_sides++;
        }
    }
    
    // XX 
    // X0
    if (down_y < map.size() && right_x < map[0].size() && init_y+1 < map.size() && init_x+1 < map[0].size())
    {
        if (map[down_y][down_x] == plot_letter && map[right_y][right_x] == plot_letter && map[init_y+1][init_x+1] != plot_letter) 
        {
            //std::cout << "Inside bottom right" << std::endl;
            number_of_sides++;
        }
    }
    

    for (int i=0; i<4; i++)
    {
        switch (i)
        {
            case 0:
                new_x = init_x + up_vector[1];
                new_y = init_y + up_vector[0];
                break;
            case 1:
                new_x = init_x + down_vector[1];
                new_y = init_y + down_vector[0];
                break;
            case 2:
                new_x = init_x + right_vector[1];
                new_y = init_y + right_vector[0];
                break;
            case 3:
                new_x = init_x + left_vector[1];
                new_y = init_y + left_vector[0];
                break;
        }
        if (new_y < 0 || new_y >= map.size() || new_x < 0 || new_x >= map[0].size()) 
        {
            perimeter++;
            continue;
        }

        bool is_coordinate_used = false;
        if (!plot_coordinates.empty())
        {
            for (std::vector<int> vi: plot_coordinates) 
            {
                if (vi[0] == new_y && vi[1] == new_x) {is_coordinate_used = true;}
            }
        }
        
        if (map[new_y][new_x] != plot_letter) 
        {
            perimeter++;
        }

        if (map[new_y][new_x] == plot_letter && !is_coordinate_used)
        {
            area++;
            //plot_map[new_y][new_x] = plot_letter;
            plot_coordinates.push_back({new_y, new_x});
            find_matching_neighbors(new_y, new_x);
        }

    }
   
}

void Plot::calculate_price()
{
    price_of_fence = area * perimeter;
}
