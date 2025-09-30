#!/usr/bin/env python3

import time
import numpy as np
from collections import defaultdict
import utils


def solve_part1(data):
    pattern = np.array([
        list(".#."),
        list("..#"),
        list("###")
    ])
    
    pattern_dict = parse_data(data)
    pattern = generate_art(pattern, pattern_dict, 5)
    answer = np.count_nonzero(pattern == "#")
    print(f"\nPart 1: {answer}")


def solve_part2(data):
    pattern = np.array([
        list(".#."),
        list("..#"),
        list("###")
    ])

    pattern_dict = parse_data(data)
    pattern = generate_art(pattern, pattern_dict, 18)
    answer = np.count_nonzero(pattern == "#")
    print(f"\nPart 2: {answer}")



def parse_data(data):
    pattern_dict = defaultdict(str)
    for line in data:
        key, value = line.split(" => ")
        key_arr = string_to_np(key)

        # Precompute all possible orientations and store for O(1) lookups
        orientations = []
        for k in range(4):
            rotated = np.rot90(key_arr, k=k)
            orientations.append(rotated)
            orientations.append(np.fliplr(rotated))

        for orientation in orientations:
            key_str = np_to_string(orientation)
            pattern_dict[key_str] = value

    return pattern_dict


def generate_art(pattern, pattern_dict, num_iterations):
    for _ in range(num_iterations):
        size = np.size(pattern, 0)
        
        tiles = []
        if (size % 2) == 0:
            sections = size / 2
            rows = np.vsplit(pattern, sections)     # split into 2 row-blocks
            tiles = [np.hsplit(r, sections) for r in rows]  # split each row-block into 2 cols
        elif (size % 3) == 0:
            sections = size / 3
            rows = np.vsplit(pattern, sections)
            tiles = [np.hsplit(r, sections) for r in rows]
        
        enhanced_rows = []
        for row_tiles in tiles:
            enhanced_row = []  # collect enhanced tiles for this row
            for tile in row_tiles:
                tile_str = np_to_string(tile)
                if tile_str in pattern_dict:
                    enhanced_row.append(string_to_np(pattern_dict[tile_str]))
                    continue

            enhanced_rows.append(enhanced_row)  # add this row to the full grid

        # Join tiles
        row_arrays = [np.hstack(r) for r in enhanced_rows]
        pattern = np.vstack(row_arrays)
    return pattern


def print_pattern(arr):
    for row in arr:
        print("".join(row))


def string_to_np(string):
    parts = string.split("/")
    arr = np.array([list(row) for row in parts])
    return arr


def np_to_string(arr):
    string = ""
    for row in arr:
        string += "".join(row)
        string += "/"
    return string[:-1]


def main():
    with open("./data/input.txt", "r") as f:
        data = [line.strip('\n') for line in f]

    start_time = time.time()
    solve_part1(data)
    print(utils.format_time(time.time() - start_time))

    start_time = time.time()
    solve_part2(data)
    print(utils.format_time(time.time() - start_time))


if __name__ == "__main__":
    main()
