#!/usr/bin/env python3

from itertools import cycle
import helpers


def solve_part1(data):
    answer = sum(int(x) for x in data)
    print(f"\nPart 1: {answer}")


def solve_part2(data):
    frequency, seen = 0, {0}
    for x in cycle(map(int, data)):
        frequency += x
        if frequency in seen: break
        seen.add(frequency)
            
    answer = frequency
    print(f"\nPart 2: {answer}")


def main():
    with open("./input.txt", "r") as f:
        data = [line.strip() for line in f]

    helpers.time_it(solve_part1, data)
    helpers.time_it(solve_part2, data)


if __name__ == "__main__":
    main()