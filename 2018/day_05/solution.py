#!/usr/bin/env python3

import helpers


def solve_part1(data):
    answer = 0
    print(f"\nPart 1: {answer}")


def solve_part2(data):
    answer = 0
    print(f"\nPart 2: {answer}")


def main():
    with open("./test.txt", "r") as f:
        data = [line.strip() for line in f]

    helpers.time_it(solve_part1, data)
    helpers.time_it(solve_part2, data)


if __name__ == "__main__":
    main()