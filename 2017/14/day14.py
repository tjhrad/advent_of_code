#!/usr/bin/env python3

import time
from functools import reduce
import numpy as np
import operator
import aoc_tools


def solve_part1(data):
    answer = 0

    row_num = 0

    for row in range(128):
        input_str = data[0] + "-" + str(row)
        hash = knot_hash(input_str)
        binary = ""
        for char in hash:
            val = format(int(char, 16), "04b")
            for v in val:
                answer += int(v)

    print(f"\nPart 1: {answer}")


def solve_part2(data):
    answer = 0

    matrix = np.zeros((128,128), dtype=int)

    for row in range(128):
        col = 0
        input_str = data[0] + "-" + str(row)
        hash = knot_hash(input_str)
        binary = ""
        for char in hash:
            val = format(int(char, 16), "04b")
            for v in val:
                matrix[row][col] = int(v)
                col += 1
    
    seen = set()
    regions = []

    for row in range(len(matrix)):
        for col in range(len(matrix[0])):
            parent = (row, col)
            
            # Skip if already visited or if it's a 0
            if parent in seen or matrix[row][col] == 0:
                continue

            # Start a new region
            stack = [parent]
            region = set()
            
            while stack:
                node = stack.pop()
                if node in seen:
                    continue
                seen.add(node)

                # Only include it if it's part of the region
                if matrix[node[0]][node[1]] == 1:
                    region.add(node)

                    # Add valid neighbors
                    for neighbor in get_neighbors(node, len(matrix), len(matrix[0])):
                        if neighbor not in seen:
                            stack.append(neighbor)

            if region:
                regions.append(region)

    answer = len(regions)

    print(f"\nPart 2: {answer}")
  

def get_neighbors(node, max_rows, max_cols):
    neighbors = []
    directions = [(0, -1), (0, 1), (-1, 0), (1, 0)]

    for d_row, d_col in directions:
        r, c = node[0] + d_row, node[1] + d_col
        if 0 <= r < max_rows and 0 <= c < max_cols:
            neighbors.append((r, c))

    return neighbors


def knot_hash(input_string, num_iterations=64):
    # Initialize the list of numbers
    numbers = list(range(256))
    
    # Convert input to ASCII codes + standard suffix
    lengths = [ord(c) for c in input_string] + [17, 31, 73, 47, 23]

    skip_size = 0
    start = 0

    # Perform the twist process
    for _ in range(num_iterations):
        for length in lengths:
            end = (start + length - 1) % len(numbers)
            first, last = start, end

            # Reverse 'length' elements in the circular list
            for _ in range(length // 2):
                numbers[first], numbers[last] = numbers[last], numbers[first]
                first = (first + 1) % len(numbers)
                last = (last - 1) % len(numbers)

            # Move the current position forward
            start = (start + length + skip_size) % len(numbers)
            skip_size += 1

    # Build dense hash by XORing blocks of 16
    dense_hash = [
        reduce(operator.xor, numbers[i:i+16]) 
        for i in range(0, 256, 16)
    ]

    # Convert to hex string (always 2 characters per byte)
    return ''.join(format(x, '02x') for x in dense_hash)


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
