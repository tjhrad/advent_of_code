#!/usr/bin/env python3

import helpers

def part1(data):
    password_range = tuple(int(n) for n in data[0].split("-"))
    answer = sum([1 for n in range(password_range[0], password_range[1] + 1) if is_valid(n)])
    print(f"\nPart 1: {answer}")


def part2(data):
    password_range = tuple(int(n) for n in data[0].split("-"))
    answer = sum([1 for n in range(password_range[0], password_range[1] + 1) if is_valid(n, pairs_only=True)])
    print(f"\nPart 2: {answer}")


def is_valid(password, pairs_only = False):
    password_str = str(password)

    for i in range(5):
        if password_str [i] > password_str [i + 1]:
            return False

    if len(set(password_str)) < 6 and not pairs_only:
        return True

    if len(set(password_str)) < 6 and pairs_only:
        counts = [password_str.count(c) for c in password_str]
        if 2 in counts:
            return True

    return False

with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]

helpers.time_it(part1, data)
helpers.time_it(part2, data)
