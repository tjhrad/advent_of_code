#!/usr/bin/env python3

import numpy as np
import helpers


def solve_part1(data):
    starting_positions, velocities = parse_data(data)

    min_area = float('inf')
    best_time = 0

    # Find the time when the bounding box is the smallest (points are more ordered)
    for t in range(15_000):
        positions = starting_positions + t * velocities
        area = bounding_box_area(positions)
        if area < min_area:
            min_area = area
            best_time = t

    print(f"\nPart 1:")
    display_positions(starting_positions, velocities, best_time)
    


def solve_part2(data):
    starting_positions, velocities = parse_data(data)

    min_area = float('inf')
    best_time = 0

    for t in range(15_000):
        positions = starting_positions + t * velocities
        area = bounding_box_area(positions)
        if area < min_area:
            min_area = area
            best_time = t

    answer = best_time
    print(f"\nPart 2: {answer}")


def parse_data(data):
    starting_positions = np.zeros((len(data), 2), dtype=int)
    velocities = np.zeros((len(data), 2), dtype=int)
    
    for row, line in enumerate(data):
        line = (line.replace("position=<", "")
                    .replace("velocity=<", "")
                    .replace(">", "")
                    .replace(",", ""))
        x_pos, y_pos, x_vel, y_vel = map(int, line.split())
        starting_positions[row] = [x_pos, y_pos]
        velocities[row] = [x_vel, y_vel]
    
    return starting_positions, velocities


def bounding_box_area(points):
    xs, ys = points[:, 0], points[:, 1]
    return (xs.max() - xs.min()) * (ys.max() - ys.min())


def display_positions(starting_positions, velocities, t):
    points = starting_positions + velocities * t
    xs, ys = points[:,0], points[:,1]
    xs -= xs.min()
    ys -= ys.min()
    grid = np.full((ys.max() + 1, xs.max() + 1), ' ')
    grid[ys, xs] = "#"
    print("\n".join("".join(row) for row in grid))


def main():
    with open("./input.txt", "r") as f:
        data = [line.strip() for line in f]

    helpers.time_it(solve_part1, data)
    helpers.time_it(solve_part2, data)


if __name__ == "__main__":
    main()