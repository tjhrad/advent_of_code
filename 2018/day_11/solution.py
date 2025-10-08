#!/usr/bin/env python3

import numpy as np
import helpers


def solve_part1(data):
    grid = build_grid(data)
    i, j, power = find_max_power(grid, 3)
    answer = f"{j + 1},{i + 1}"
    print(f"\nPart 1: {answer}")    


def solve_part2(data):
    grid = build_grid(data)
    max_power = float('-inf')
    max_i = max_j = size = 0

    for w in range(1, 301):
        i, j, power = find_max_power(grid, w)
        if power > max_power:
            max_power = power
            max_i, max_j, size = i, j, w

    answer = f"{max_j + 1},{max_i + 1},{size}"
    print(f"\nPart 2: {answer}")


def build_grid(data):
    rack_ids = np.zeros((300, 300), dtype=int)
    rack_ids = np.tile(np.arange(1, 301) + 10, (300, 1))
    grid = rack_ids * np.tile(np.arange(1, 301), (300, 1)).T
    grid += int(data[0])
    grid *= rack_ids
    grid = (grid // 100) % 10 
    grid -= 5
    
    return grid


def find_max_power(grid, window_size):
    shape = (grid.shape[0] - window_size + 1,
            grid.shape[1] - window_size + 1,
            window_size, window_size)

    strides = grid.strides + grid.strides

    # Create a 4D view of overlapping 3×3 windows (no copies!)
    windows = np.lib.stride_tricks.as_strided(grid, shape=shape, strides=strides)

    # Sum each 3×3 block
    power_grid = windows.sum(axis=(2, 3))

    # Find maximum power and its position
    max_power = power_grid.max()
    max_i, max_j = np.unravel_index(power_grid.argmax(), power_grid.shape)

    return max_i, max_j, max_power


def main():
    with open("./input.txt", "r") as f:
        data = [line.strip() for line in f]

    helpers.time_it(solve_part1, data)
    helpers.time_it(solve_part2, data)


if __name__ == "__main__":
    main()