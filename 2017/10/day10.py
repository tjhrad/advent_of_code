#!/usr/bin/env python3

import time
import aoc_tools


def solve_part1(data):
    answer = 0
    
    print("\nPart 1: " + str(answer))


def solve_part2(data):
    answer = 0

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
