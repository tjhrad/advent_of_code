#!/usr/bin/env python3

import helpers


def part_1(data):
    answer = 0
    print(f"\nPart 1: {answer}")


def part_2(data):
    answer = 0
    print(f"\nPart 2: {answer}")


with open("./text.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]

helpers.time_it(part_1, data)
helpers.time_it(part_2, data)
