#!/usr/bin/env python3

import time
from collections import defaultdict
import aoc_tools


def solve_part1(data):
    registers = defaultdict(int)

    for instruction in data:
        register, operation, value, _, cond_register, cond_operator, cond_value = instruction.split()
        value, cond_value = int(value), int(cond_value)

        condition = f"{registers[cond_register]} {cond_operator} {cond_value}"
        if eval(condition):
            if (operation == "inc"):
                registers[register] += value
            else:
                registers[register] -= value
       
    answer = max(registers.values())

    print("\nPart 1: " + str(answer))


def solve_part2(data):
    answer = 0
    registers = defaultdict(int)

    for instruction in data:
        register, operation, value, _, cond_register, cond_operator, cond_value = instruction.split()
        value, cond_value = int(value), int(cond_value)

        condition = f"{registers[cond_register]} {cond_operator} {cond_value}"
        if eval(condition):
            if (operation == "inc"):
                registers[register] += value
            else:
                registers[register] -= value

            if registers[register] > answer:
                answer = registers[register]

    print("\nPart 2: " + str(answer))


def main():
    with open("./data/input.txt", "r") as f:
        data = [line.strip() for line in f]

    start_time = time.time()
    solve_part1(data)
    print(aoc_tools.format_time(time.time() - start_time))

    start_time = time.time()
    solve_part2(data)
    print(aoc_tools.format_time(time.time() - start_time))


if __name__ == "__main__":
    main()
