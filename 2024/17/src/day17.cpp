#include "day17.h"

std::set<std::pair<int,int>> temporary_box_coordinates;

int main()
{
    std::cout << '\n' << "AOC 2024 - DAY 17" << '\n' << std::endl;

    // Read input
    std::string input_file_path = ".\\17\\data\\input.txt";
    std::vector<std::string> input_file_data = read_text_file(input_file_path);

    // Part 1
    part_one(input_file_data);

    // Part 2
    part_two(input_file_data);

    return 0;
    }

void part_one(const std::vector<std::string>& input_data)
{
    // Start timer
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "PART 1" << std::endl;

    // Code here
    std::string instruction_string = get_instructions(input_data);
    std::vector<long long> register_values = get_register_values(input_data);

    auto instructions = instruction_string_to_int_vector(instruction_string);

    auto answer = compute(instructions, register_values[0], register_values[1], register_values[2]);
    std::cout << "Answer for part 1: " << answer << std::endl;

    // End timer
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time to complete: " << duration.count() << " milliseconds." << std::endl << std::endl;
}

void part_two(const std::vector<std::string>& input_data)
{
    // Start timer
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "PART 2" << std::endl;

    // Code here
    std::string instruction_string = get_instructions(input_data);
    std::vector<long long> register_values = get_register_values(input_data);

    auto instructions = instruction_string_to_int_vector(instruction_string);
    long long a_start = 0;
    int i = 0;
    long long sofar = 0;
    auto answer = get_best_quine_input(instructions, instructions.size() - 1, sofar);

    std::cout << "Answer for part 2: " << answer << std::endl;

    // End timer
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time to complete: " << duration.count() << " milliseconds." << std::endl << std::endl;
}

std::string get_instructions(const std::vector<std::string>& input_data)
{
    std::string instructions = "";

    instructions = split_string(input_data[4], " ")[1];

    return instructions;
}

std::vector<long long> get_register_values(const std::vector<std::string>& input_data)
{
    std::vector<long long> register_values;

    long long a = stoll(split_string(input_data[0]," ")[2]);
    long long b = stoll(split_string(input_data[1]," ")[2]);
    long long c = stoll(split_string(input_data[2]," ")[2]);

    register_values.push_back(a);
    register_values.push_back(b);
    register_values.push_back(c);

    return register_values;
}

std::vector<int> instruction_string_to_int_vector(std::string& input_string)
{
	std::vector<int> instruction_vector;

    std::vector<std::string> strings = split_string(input_string, ",");

	for (std::string s : strings)
	{
		instruction_vector.push_back(stoll(s));
	}

	return instruction_vector;
}

long long opcode_0_adv(long long& a_value, long long& combo_operand)
{
	return a_value/std::pow(2,combo_operand);
}

long long opcode_1_bxl(long long& b_value, int& literal_operand)
{
	return static_cast<long long>(b_value ^ literal_operand);
}

long long opcode_2_bst(long long& combo_operand)
{
	return combo_operand % 8;
}


bool opcode_3_jnz(long long& a_value)
{
	if (a_value == 0) {return false;} // DO NOTHING;

	return true;
}

long long opcode_4_bxc(long long& b_value, long long& c_value, int& literal_operand)
{
	// Yes, this function reads the literal operand and then ignores it. Just like the instructions said. :)
	return static_cast<long long>(b_value ^ c_value);
}

long long opcode_5_out(long long& combo_operand)
{
	return combo_operand % 8;
}

long long opcode_6_bdv(long long& a_value, long long& combo_operand)
{
	return a_value/std::pow(2,combo_operand);
}

long long opcode_7_cdv(long long& a_value, long long& combo_operand)
{
	return a_value/std::pow(2,combo_operand);
}

// Input: Program 3-bit instructions (example: {0,1,5,4,3,0}) and the initial values of Registers A, B, and C.
// Output: Concatinated std::string containing the sequence of integers generated by optcode_5_out().
std::string compute(const std::vector<int>& instructions, long long a_value, long long b_value, long long c_value)
{
	std::string output_string = "";
	int instruction_pointer = 0;

	while(instruction_pointer < instructions.size())
	{
		int opcode = instructions[instruction_pointer];
		int operand = instructions[instruction_pointer + 1];

		bool has_pointer_jumped = false;

		long long combo_operand;
		if (operand < 4) // 0,1,2,3
		{
			combo_operand = operand;
		}
		else if (operand == 4)
		{
			combo_operand = a_value;
		}
		else if (operand == 5)
		{
			combo_operand = b_value;
		}
		else if (operand == 6)
		{
			combo_operand = c_value;	
		}
		else if (operand == 7)
		{
			std::cout << "An error occured in compute(). Invalid operand:" << operand << std::endl;
			return output_string;
		}

		// Execute instructions.
		if (opcode == 0)
		{
			a_value = opcode_0_adv(a_value, combo_operand);
		}
		else if (opcode == 1)
		{
			b_value = opcode_1_bxl(b_value, operand);
		}
		else if (opcode == 2)
		{
			b_value = opcode_2_bst(combo_operand);
		}
		else if (opcode == 3)
		{
			has_pointer_jumped = opcode_3_jnz(a_value);
			if (has_pointer_jumped) {instruction_pointer = operand;}
		}
		else if (opcode == 4)
		{
			b_value = opcode_4_bxc(b_value, c_value, operand);
		}
		else if (opcode == 5)
		{
			if (output_string.size() == 0)
			{
				output_string = output_string + std::to_string(opcode_5_out(combo_operand));
			}
			else
			{
				output_string = output_string + ","+ std::to_string(opcode_5_out(combo_operand));
			}
		}
		else if (opcode == 6)
		{
			b_value = opcode_6_bdv(a_value, combo_operand);
		}
		else if (opcode == 7)
		{
			c_value = opcode_7_cdv(a_value, combo_operand);
		}

		// If the pointer jumped (in opcode 3), don't increment the pointer.
		// Otherwise, the pointer is incremented by 2.
		if (!has_pointer_jumped) 
		{
			instruction_pointer = instruction_pointer + 2;
		}
	}

	return output_string;
}

// Elegant solution by reddit user mental-chaos. I can't take credit for this one.
long long get_best_quine_input(const std::vector<int>& instructions, int cursor, long long sofar) 
{
    long long null = 0;
    for (int candidate = 0; candidate < 8; ++candidate) 
    {
        long long input = sofar * 8 + candidate;
        long long b = 0;
        long long c = 0;
        std::string instruction_string = compute(instructions, input, b, c);
        std::vector<int> result = instruction_string_to_int_vector(instruction_string);
        
        // Check if result matches program from cursor onwards
        if (std::equal(result.begin(), result.end(), instructions.begin() + cursor)) 
        {
            if (cursor == 0) {
                return input;
            }
            
            // Recursive call to find the next input
            auto ret = get_best_quine_input(instructions, cursor - 1, input);
            if (ret > 0) 
            {
                return ret;
            }
        }
    }
    return null;
}
