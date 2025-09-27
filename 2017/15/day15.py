#!/usr/bin/env python3

import time
import aoc_tools


def solve_part1(data):
    answer = 0

    generator_a = int(data[0].split()[4])
    generator_b = int(data[1].split()[4])

    MOD = 2147483647
    FACTOR_A = 16807
    FACTOR_B = 48271
    MASK = 0xFFFF

    for _ in range(40_000_000):
        generator_a = (generator_a * FACTOR_A) % MOD
        generator_b = (generator_b * FACTOR_B) % MOD

        if (generator_a & MASK) == (generator_b & MASK):
            answer += 1


    print(f"\nPart 1: {answer}")


def solve_part2(data):
    answer = 0

    generator_a = int(data[0].split()[4])
    generator_b = int(data[1].split()[4])

    MOD = 2147483647
    FACTOR_A = 16807
    FACTOR_B = 48271
    MASK = 0xFFFF
    PAIRS = 5_000_000

    values_a = []
    values_b = []

    while len(values_a) < PAIRS:
        generator_a = (generator_a * FACTOR_A) % MOD
        if (generator_a % 4) == 0:
            values_a.append(generator_a)

    while len(values_b) < PAIRS:
        generator_b = (generator_b * FACTOR_B) % MOD
        if (generator_b % 8) == 0:
            values_b.append(generator_b)
    
    for x in range(PAIRS):
        if (values_a[x] & MASK) == (values_b[x] & MASK):
            answer += 1

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
