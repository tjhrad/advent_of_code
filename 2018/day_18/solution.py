#!/usr/bin/env python3

import helpers
import numpy as np


def part_1(data):
    grid = parse_data(data)
    grid = evolve(grid)
    
    answer = np.count_nonzero(grid == 1) * np.count_nonzero(grid == 2)
    print(f"\nPart 1: {answer}")   


def part_2(data):
    grid = parse_data(data)
    grid = evolve(grid, n_epochs=1_000_000_000)
    
    answer = np.count_nonzero(grid == 1) * np.count_nonzero(grid == 2)
    print(f"\nPart 2: {answer}")


def parse_data(data):
    rows = []
    for line in data:
        row = []
        for c in line:
            if c == ".":
                row.append(0)
            elif c == "#":
                row.append(1)
            elif c == "|":
                row.append(2)
        rows.append(row)

    arr = np.array([row for row in rows])
    return arr


def evolve(grid, n_epochs=10):
    NEIGHBORS = [(-1, -1), (-1, 0), (-1, 1),
                 ( 0, -1),           ( 0, 1),
                 ( 1, -1), ( 1, 0), ( 1, 1)]

    # open acre = "." = 0, lumberyard = "#" = 1, tree = "|" = 2
    seen = {}

    for epoch in range(n_epochs):
        starting_grid = grid.copy()

        h = grid.tobytes()

        if h in seen:
            start = seen[h]
            period = epoch - start
            remaining = (n_epochs - epoch) % period
            grid = evolve(grid, n_epochs = remaining)
            break
                
        seen[h] = epoch

        for y in range(len(grid)):
            for x in range(len(grid[0])):
                neighbor_counts = {0:0, 1:0, 2:0}
                for n in NEIGHBORS:
                    new_x, new_y = x + n[0], y + n[1]
                    if 0 <= new_x < len(grid[0]) and 0 <= new_y < len(grid):
                        neighbor_counts[starting_grid[new_y][new_x]] += 1
                    
                if grid[y][x] == 0 and neighbor_counts[2] >= 3:
                    grid[y][x] = 2
                elif grid[y][x] == 2 and neighbor_counts[1] >= 3:
                    grid[y][x] = 1

                elif grid[y][x] == 1:
                    if neighbor_counts[1] >= 1 and neighbor_counts[2] >= 1:
                        continue
                    else:
                        grid[y][x] = 0
                
    return grid


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]

helpers.time_it(part_1, data)
helpers.time_it(part_2, data)