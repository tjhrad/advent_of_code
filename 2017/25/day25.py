#!/usr/bin/env python3

from collections import defaultdict
import utils


def solve_part1(data):
    states = get_states(data)
    num_steps = int(data[1].split()[5])
    answer = run_turing(states, num_steps)
    print(f"\nPart 1: {answer}")


def run_turing(states, num_steps):
    tape = defaultdict(int)

    DIRECTIONS = {
        "right":1,
        "left":-1
    }

    current_state = "A"
    current_pos = 0
    tape[current_pos] = 0

    for _ in range(num_steps):
        write_0, move_0, next_0, write_1, move_1, next_1 = states[current_state]
        if tape[current_pos] == 0:
            tape[current_pos] = int(write_0)
            current_pos += DIRECTIONS[move_0]
            current_state = next_0
        else:
            tape[current_pos] = int(write_1)
            current_pos += DIRECTIONS[move_1]
            current_state = next_1

    return sum(tape.values())


def get_states(data):
    states = defaultdict(list)
    line_num = 0
    while line_num < len(data):
        if "In state " in data[line_num]:
            state = data[line_num].split()[2][:-1]
            write_0 = data[line_num + 2].split()[4][:-1]
            move_0 = data[line_num + 3].split()[6][:-1]
            next_0 = data[line_num + 4].split()[4][:-1]

            write_1 = data[line_num + 6].split()[4][:-1]
            move_1 = data[line_num + 7].split()[6][:-1]
            next_1 = data[line_num + 8].split()[4][:-1]
            states[state].extend([write_0, move_0, next_0, write_1, move_1, next_1])

        line_num += 1
    return states


def main():
    with open("./data/input.txt", "r") as f:
        data = [line.strip() for line in f]

    utils.time_it(solve_part1, data)


if __name__ == "__main__":
    main()