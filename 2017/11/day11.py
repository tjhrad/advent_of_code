#!/usr/bin/env python3

import time
import aoc_tools

# Define hexagonal grid coordinates (using cube coordinates)
neighbors = [
    (0, 1, -1), (1, 0, -1), (1, -1, 0),
    (-1, 1, 0), (-1, 0, 1), (0, -1, 1)
]

# Define directions
directions = [
    "nw", "n", "ne",
    "sw", "s", "se"
]

def solve_part1(data):
    answer = 0

    start = (0, 0, 0)
    end = start
    for direction in data[0].split(","):
        end = [a + b for a, b in zip(end, neighbors[directions.index(direction)])]
    
    # Calculate distance between start and end
    answer = max(abs(start[0] - end[0]), abs(start[1] - end[1]), abs(start[2] - end[2]))

    print("\nPart 1: " + str(answer))


def solve_part2(data):
    answer = 0

    start = (0, 0, 0)
    end = start
    for direction in data[0].split(","):
        end = [a + b for a, b in zip(end, neighbors[directions.index(direction)])]
        distance = max(abs(start[0] - end[0]), abs(start[1] - end[1]), abs(start[2] - end[2]))
        if distance > answer:
            answer = distance

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
