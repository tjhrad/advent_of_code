#!/usr/bin/env python3

import time
from collections import defaultdict
import aoc_tools


def solve_part1(data):
    layers = {}
    for line in data:
        depth, rng = map(int, line.split(": "))
        layers[depth] = rng

    answer = 0
    for depth, rng in layers.items():
        # Period = the total number of steps in a cycle for each scanner.
        # (range - 1) = the number of steps for half the period. Hence, 2 x (R - 1).
        period = 2 * (rng - 1)
        if (depth) % period == 0:
            answer += depth * rng

    print(f"\nPart 1: {answer}")


def solve_part2(data):
    layers = {}
    for line in data:
        depth, rng = map(int, line.split(": "))
        layers[depth] = rng

    delay = 0
    while True:
        # Check if caught at this delay
        caught = False
        for depth, rng in layers.items():
            period = 2 * (rng - 1)
            if (delay + depth) % period == 0:
                caught = True
                break
        if not caught:
            break
        delay += 1

    answer = delay
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
