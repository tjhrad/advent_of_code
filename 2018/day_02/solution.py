#!/usr/bin/env python3

import itertools
import helpers


def solve_part1(data):
    two_count, three_count = 0, 0
    for string in data:
        counts = set([string.count(s) for s in string])
        if 2 in counts:
            two_count += 1 
        if 3 in counts:
            three_count += 1 

    answer = two_count * three_count
    print(f"\nPart 1: {answer}")


def solve_part2(data):
    answer = ""
    for pair in itertools.combinations(data, 2):
        dif = [a for a, b in zip(pair[0], pair[1]) if a == b]
        if len(dif) == (len(pair[0]) - 1):
            answer = "".join(dif)
            break
    print(f"\nPart 2: {answer}")


def main():
    with open("./input.txt", "r") as f:
        data = [line.strip() for line in f]

    helpers.time_it(solve_part1, data)
    helpers.time_it(solve_part2, data)


if __name__ == "__main__":
    main()