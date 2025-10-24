#!/usr/bin/env python3

import helpers
from collections import defaultdict


def part_1(data):
    nanobots = get_bots(data)
    max_range = max([r for r, _ in nanobots])

    answer = 0
    for r, pos in nanobots:
        if max_range != r:
            continue
        
        for r_2, pos_2 in nanobots:
            dist = sum(abs(a-b) for a, b in zip(pos, pos_2))
            if dist <= max_range:
                answer += 1
    
    print(f"\nPart 1: {answer}")


def part_2(data):
    # TODO: Brute force too slow
    # Learn how to implement octree/space subdivition approach

    nanobots = get_bots(data)

    counts = defaultdict(int)
    max_x = max(list(pos)[0] for _, pos in nanobots)
    max_y = max(list(pos)[1] for _, pos in nanobots)
    max_z = max(list(pos)[2] for _, pos in nanobots)

    for x in range(max_x + 1):
        for y in range(max_y + 1):
            for z in range(max_z + 1):
                coordinate = (x, y, z)

                for r, pos in nanobots:
                    dist = sum(abs(a-b) for a, b in zip(pos, coordinate))
                    if dist <= r:
                        counts[coordinate] += 1


    max_count = max([count for count in counts.values()])
    coordinates = [p for p, v in counts.items() if v == max_count]
    answer = min([sum(abs(a-b) for a, b in zip((0, 0, 0), p)) for p in coordinates])
    print(f"\nPart 2: {answer}")


def get_bots(data):
    nanobots = []
    for line in data:
        coord_str, r_str = line.replace("pos=<", "").replace(">", "").replace("r=", "").split(", ")
        (x, y, z) = [int(p) for p in coord_str.split(",")]
        rng = int(r_str)
        nanobots.append([rng, (x, y, z)])

    return nanobots


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]

helpers.time_it(part_1, data)
helpers.time_it(part_2, data)