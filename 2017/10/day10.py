#!/usr/bin/env python3

import time
from functools import reduce
import operator
import aoc_tools


def solve_part1(data):
    answer = 0

    numbers = [x for x in range(256)]
    lengths = data[0].split(",")

    numbers = knot_hash(numbers, lengths, 1)

    answer = numbers[0] * numbers[1]
    
    print("\nPart 1: " + str(answer))


def solve_part2(data):
    numbers = [x for x in range(256)]
    lengths = [ord(c) for c in data[0]]
    lengths.extend([17, 31, 73, 47, 23])

    sparse_hash = knot_hash(numbers, lengths, 64)

    dense_hash = get_dense_hash(sparse_hash)
    answer = get_hexadecimal(dense_hash)

    print("\nPart 2: " + str(answer))


def knot_hash(numbers, lengths, num_iterations):
    skip_size = 0
    start = 0
    for x in range(num_iterations):
        for l in lengths:
            end = (start + int(l) - 1) % len(numbers)
            last_start = start
            for x in range(int((int(l))/2)):
                numbers[start], numbers[end] = numbers[end], numbers[start]

                start += 1
                end -= 1

                if (start >= len(numbers)):
                    start = 0
                if (end < 0):
                    end = len(numbers) - 1

            start = (last_start + int(l) + skip_size) % len(numbers)
            skip_size += 1
    return numbers


def get_dense_hash(sparse_hash):
    dense_hash = []
    for x in range(16):
        dense_hash.append(reduce(operator.xor,sparse_hash[:16]))
        sparse_hash = sparse_hash[16:]
    return dense_hash


def get_hexadecimal(sparse_hash):
    hexadecimal = ""
    for i in sparse_hash:
        hex_str = format(i, "02x")
        hexadecimal += hex_str
    return hexadecimal


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
