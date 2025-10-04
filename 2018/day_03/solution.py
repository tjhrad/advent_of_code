#!/usr/bin/env python3

from collections import defaultdict
import helpers


def solve_part1(data):
    grid = defaultdict(int)
    for line in data:
        num, _, start_pos, dim = line.split()
        x, y = tuple(map(int, start_pos[:-1].split(",")))
        w, h = tuple(map(int, dim.split("x")))
        for row in range(w):
            for col in range(h):
                grid[(x + row, y + col)] += 1

    answer = sum(1 for x in grid.values() if x > 1)
    print(f"\nPart 1: {answer}")


def solve_part2(data):
    claimed_positions = defaultdict(set)
    claims = set()
    for line in data:
        num, _, start_pos, dim = line.split()
        x, y = tuple(map(int, start_pos[:-1].split(",")))
        w, h = tuple(map(int, dim.split("x")))
        claims.add(num)
        for row in range(w):
            for col in range(h):
                claimed_positions[(x + row, y + col)].add(num)

    overlapping_ids = set()
    for ids in claimed_positions.values():
        if len(ids) > 1:
            overlapping_ids.update(ids)

    answer = list((claims - overlapping_ids))[0][1:]
    print(f"\nPart 2: {answer}")


def main():
    with open("./input.txt", "r") as f:
        data = [line.strip() for line in f]

    helpers.time_it(solve_part1, data)
    helpers.time_it(solve_part2, data)


if __name__ == "__main__":
    main()