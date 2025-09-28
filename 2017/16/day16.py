#!/usr/bin/env python3

import time
from collections import deque
from collections import defaultdict
import aoc_tools


def solve_part1(data):
    programs = 'abcdefghijklmnop'
    instructions = data[0].split(",")
    
    answer = dance(instructions, programs)

    print(f"\nPart 1: {answer}")


def solve_part2(data):
    programs = 'abcdefghijklmnop'
    instructions = data[0].split(",")
    
    programs = dance(instructions, programs)
    
    # Find the length of the cycle
    i = 1
    while programs != 'abcdefghijklmnop':
        programs = dance(instructions, programs)
        i += 1
    
    j = 1_000_000_000 % i

    for _ in range(j):
        programs = dance(instructions, programs)

    answer = programs
    print(f"\nPart 2: {answer}")


def dance(instructions, string):
    for inst in instructions:
        if (inst[0] == "s"):
            string = string[-int(inst[1:]):] + string[:-int(inst[1:])]
        elif (inst[0] == "x"):
            index_1, index_2 = [int(x) for x in inst[1:].split("/")]
            string = string.replace(string[index_1], 'x').replace(string[index_2], 'y').replace('x', string[index_2]).replace('y',string[index_1])
        elif (inst[0] == "p"):
            item_1, item_2 = [x for x in inst[1:].split("/")]
            index_1, index_2 = string.index(item_1), string.index(item_2)
            string = string.replace(string[index_1], 'x').replace(string[index_2], 'y').replace('x', string[index_2]).replace('y',string[index_1])
    
    return ''.join(string)


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
