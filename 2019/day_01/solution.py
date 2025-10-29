#!/usr/bin/env python3

import helpers


def part1(data):
    answer = sum([((int(x) // 3) - 2) for x in data])
    print(f"\nPart 1: {answer}")


def part2(data):
    answer = 0
    for x in data:
        fuel = int(x)
        while True:
            next_fuel = (fuel // 3) - 2

            if next_fuel <= 0:
                break

            answer += next_fuel
            fuel = next_fuel

    print(f"\nPart 2: {answer}")


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]

helpers.time_it(part1, data)
helpers.time_it(part2, data)
