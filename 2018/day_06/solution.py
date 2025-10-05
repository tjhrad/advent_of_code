#!/usr/bin/env python3


import numpy as np
import helpers


def solve_part1(data):
    # Parse data into numpy array
    coordinates = np.array([list(map(int, x.split(", "))) for x in data])

    # Define grid edges
    x_min, y_min = coordinates.min(axis=0)
    x_max, y_max = coordinates.max(axis=0)

    # Loop through each x, y coordinate in the grid and calculate the mh distance to each coordinate.
    areas = np.zeros(len(coordinates), dtype=int)
    infinite = set()
    for x in range(x_min, x_max + 1):
        for y in range(y_min, y_max + 1):
            # Vectorized MH distance calculations
            distances = np.abs(coordinates[:,0] - x) + np.abs(coordinates[:,1] - y)
            min_distance = np.min(distances)

            # If only one point is the smallest, increment the area.
            if (distances == min_distance).sum() == 1:
                min_index = np.argmin(distances)
                areas[min_index] += 1

                # Define "infinite" coordinates
                if x in (x_min, x_max) or y in (y_min, y_max):
                    infinite.add(min_index)

    # Use a mask to remove the "infinite" coordinates
    mask = np.ones(len(coordinates), dtype=bool)
    mask[list(infinite)] = False
    answer = areas[mask].max()
    print(f"\nPart 1: {answer}")


def solve_part2(data):
    # Parse data into numpy array
    coordinates = np.array([list(map(int, x.split(", "))) for x in data])

    # Define grid edges
    x_min, y_min = coordinates.min(axis=0)
    x_max, y_max = coordinates.max(axis=0)

    # Count the number of points that have a total distance < 10,000
    safe_area = 0
    for x in range(x_min, x_max + 1):
        for y in range(y_min, y_max + 1):
            distance = np.abs(coordinates[:,0] - x) + np.abs(coordinates[:,1] - y)
            
            total_distance = distance.sum()
            if total_distance < 10_000:
                safe_area += 1

    answer = safe_area
    print(f"\nPart 2: {answer}")


def main():
    with open("./input.txt", "r") as f:
        data = [line.strip() for line in f]

    helpers.time_it(solve_part1, data)
    helpers.time_it(solve_part2, data)


if __name__ == "__main__":
    main()