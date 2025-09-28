#!/usr/bin/env python3

import time
import aoc_tools


def solve_part1(data):
    STEPS = int(data[0])
    ITERATIONS = 2017
    buffer = [0]

    current_index = 0
    for i in range(ITERATIONS):
        index = ((current_index + STEPS) % len(buffer)) + 1
        buffer.insert(index, i + 1)
        current_index = index

    answer = buffer[current_index + 1]
    print(f"\nPart 1: {answer}")


def solve_part2(data):
    STEPS = int(data[0])
    ITERATIONS = 50_000_000

    index = 0
    answer = 0
    for i in range(1, ITERATIONS + 1):
        index = (index + STEPS) % i
        if index == 0:
            answer = i
        index += 1

    print(f"\nPart 2: {answer}")


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
