#!/usr/bin/env python3

import time
import aoc_tools

input_file_path = "./data/input.txt"

with open(input_file_path, "r") as f:
    data = [line.strip() for line in f]


def part1():
    answer = 0

    data_split = data[0].split()

    memory_banks = [int(s) for s in data_split]

    seen = set()
    key = "".join([str(i) for i in memory_banks])
    seen.add(key)

    while True:
        answer += 1
        max_value = max(memory_banks)
        index = memory_banks.index(max_value)
        memory_banks[index] = 0
        for x in range(max_value):
            index += 1
            if index == len(memory_banks):
                index = 0
            memory_banks[index] += 1
        key = "".join([str(i) for i in memory_banks])
        if key in seen:
            break
        seen.add(key)

    print("\nPart 1: " + str(answer))


def part2():
    answer = 0

    data_split = data[0].split()

    memory_banks = [int(s) for s in data_split]

    seen = set()
    key = "".join([str(i) for i in memory_banks])
    seen.add(key)

    while True:
        max_value = max(memory_banks)
        index = memory_banks.index(max_value)
        memory_banks[index] = 0
        for x in range(max_value):
            index += 1
            if index == len(memory_banks):
                index = 0
            memory_banks[index] += 1
        key = "".join([str(i) for i in memory_banks])
        if key in seen:
            break
        seen.add(key)

    while True:
        answer += 1
        max_value = max(memory_banks)
        index = memory_banks.index(max_value)
        memory_banks[index] = 0
        for x in range(max_value):
            index += 1
            if index == len(memory_banks):
                index = 0
            memory_banks[index] += 1
        key_2 = "".join([str(i) for i in memory_banks])
        if key_2 == key:
            break

    print("\nPart 2: " + str(answer))


def main():
    start_time = time.time()
    part1()
    print(aoc_tools.format_time(time.time() - start_time))

    start_time = time.time()
    part2()
    print(aoc_tools.format_time(time.time() - start_time))


if __name__ == "__main__":
    main()
