#!/usr/bin/env python3

import helpers
from collections import defaultdict
import heapq


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
    nanobots = get_bots(data)

    xmax = max(pos[0] for _, pos in nanobots)
    xmin = min(pos[0] for _, pos in nanobots)

    ymax = max(pos[1] for _, pos in nanobots)
    ymin = min(pos[1] for _, pos in nanobots)
    
    zmax = max(pos[2] for _, pos in nanobots)
    zmin = min(pos[2] for _, pos in nanobots)

    cube_size = 1
    while cube_size < max(xmax - xmin, ymax - ymin, zmax - zmin):
        cube_size *= 2

    starting_cube = (xmin, ymin, zmin, cube_size)

    initial_count = 0
    for r, pos in nanobots:
        if collision(starting_cube, pos, r):
            initial_count += 1
    
    queue = []
    priority = (-initial_count, starting_cube[3], dist_to_origin(starting_cube))
    heapq.heappush(queue, (priority, starting_cube))

    answer = 0
    best_dist = float("inf")
    while queue:
        _, cube = heapq.heappop(queue)

        # Check if we are done
        if cube[3] <= 1:
            dist = dist_to_origin(cube)
            answer = dist
            break

        for subcube in subdivide(*cube):
            n_collisions = sum(
                collision(subcube, bot[1], bot[0])
                for bot in nanobots
            )

            if n_collisions > 0:
                priority = (-n_collisions, subcube[3], dist_to_origin(subcube))
                heapq.heappush(queue, (priority, subcube))

    print(f"\nPart 2: {answer}")


def dist_to_origin(cube):
    xmin, ymin, zmin, s = cube
    xmax, ymax, zmax = xmin + s - 1, ymin + s - 1, zmin + s - 1

    dx = 0 if xmin <= 0 <= xmax else min(abs(xmin), abs(xmax))
    dy = 0 if ymin <= 0 <= ymax else min(abs(ymin), abs(ymax))
    dz = 0 if zmin <= 0 <= zmax else min(abs(zmin), abs(zmax))

    return dx + dy + dz


def collision(cube, bot_pos, bot_range):
    xmin, ymin, zmin, s = cube
    xmax, ymax, zmax = xmin + s - 1, ymin + s - 1, zmin + s - 1

    bx, by, bz = bot_pos
    dx = 0 if xmin <= bx <= xmax else min(abs(bx - xmin), abs(bx - xmax))
    dy = 0 if ymin <= by <= ymax else min(abs(by - ymin), abs(by - ymax))
    dz = 0 if zmin <= bz <= zmax else min(abs(bz - zmin), abs(bz - zmax))

    return (dx + dy + dz) <= bot_range


def subdivide(xmin, ymin, zmin, size):
    half = size // 2

    if half == 0:
        return  # cannot subdivide further

    # children are exactly aligned on integer grid; offsets are 0 or half
    for ox in (0, half):
        for oy in (0, half):
            for oz in (0, half):
                yield (xmin + ox, ymin + oy, zmin + oz, half)


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
