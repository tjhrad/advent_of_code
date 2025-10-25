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
    max_x = max(list(pos)[0] for _, pos in nanobots)
    min_x = min(list(pos)[0] for _, pos in nanobots)

    max_y = max(list(pos)[1] for _, pos in nanobots)
    min_y = min(list(pos)[1] for _, pos in nanobots)
    
    max_z = max(list(pos)[2] for _, pos in nanobots)
    min_z = min(list(pos)[2] for _, pos in nanobots)

    # cube = (x, y, z, size)
    cube_size = 1
    while cube_size < max(max_x - min_x, max_y - min_y, max_z - min_z):
        cube_size *= 2

    cube_center = ((max_x + min_x)//2, (max_y + min_y)//2, (max_z + min_z)//2)
    starting_cube = (*cube_center, cube_size)
    queue = []

    # Create a heapq with subdivisions of the larger cube
    # Sorts the heap by max value (number of bots in range)
    # Use a negative value as the priority value (because we actually want a max-heap)
    distance_to_origin = sum(abs(a-b) for a, b in zip((0, 0, 0), cube_center))
    heapq.heappush(queue, ((-len(nanobots), starting_cube[3], distance_to_origin), starting_cube))

    answer = 0
    while queue:
        # TODO: Fix the heapq pop based on the new tuple
        _, cube = heapq.heappop(queue)

        if cube[3] <= 1: # Done
            print((cube[0], cube[1], cube[2]))
            answer = sum(abs(a-b) for a, b in zip((cube[0], cube[1], cube[2]), (0,0,0)))
            break

        # Subdivide the cube into 8 equal sub-cubes
        for subcube in subdivide_cube(*cube):
            # Find how many robots are in the current subcube
            
            n_collisions = 0
            for bot in nanobots:
                # Check if bot is in range of the subcube
                if collision((subcube[0], subcube[1], subcube[2]), subcube[3], list(bot[1]), bot[0]):
                    n_collisions += 1
            
            if n_collisions > 0:
                distance_to_origin = sum(abs(a-b) for a, b in zip((0, 0, 0), (subcube[0], subcube[1], subcube[2])))
                heapq.heappush(queue, ((-n_collisions, subcube[3], distance_to_origin), subcube))
    
    print(f"\nPart 2: {answer}")


def collision(cube_center, cube_size, bot_pos, bot_range):
    half = cube_size / 2
    xmin, xmax = cube_center[0] - half, cube_center[0] + half
    ymin, ymax = cube_center[1] - half, cube_center[1] + half
    zmin, zmax = cube_center[2] - half, cube_center[2] + half
    
    dx = 0 if xmin <= bot_pos[0] <= xmax else min(abs(bot_pos[0] - xmin), abs(bot_pos[0] - xmax))
    dy = 0 if ymin <= bot_pos[1] <= ymax else min(abs(bot_pos[1] - ymin), abs(bot_pos[1] - ymax))
    dz = 0 if zmin <= bot_pos[2] <= zmax else min(abs(bot_pos[2] - zmin), abs(bot_pos[2] - zmax))

    return (dx + dy + dz) <= bot_range



def subdivide_cube(x, y, z, size):
    half = size // 2

    if half == 0:
        return # Cannot subdivide anymore

    quarter = half // 2
    for dx in (-quarter, quarter):
        for dy in (-quarter, quarter):
            for dz in (-quarter, quarter):
                yield (x + dx, y + dy, z + dz, half)


def get_bots(data):
    nanobots = []
    for line in data:
        coord_str, r_str = line.replace("pos=<", "").replace(">", "").replace("r=", "").split(", ")
        (x, y, z) = [int(p) for p in coord_str.split(",")]
        rng = int(r_str)
        nanobots.append([rng, (x, y, z)])

    return nanobots


with open("./test.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]

helpers.time_it(part_1, data)
helpers.time_it(part_2, data)
