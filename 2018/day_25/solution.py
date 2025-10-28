#!/usr/bin/env python3

import helpers


def part_1(data):
    points = []
    for line in data:
        points.append(tuple([int(n) for n in line.split(",")]))

    constellations = []
    seen = set()

    for p in points:
        if p in seen:
            continue

        constellation = {p}
        queue = [p]
        seen.add(p)

        while queue:
            current = queue.pop()
            for other in points:
                if other in seen:
                    continue

                dist = sum(abs(a-b) for a, b in zip (current, other))
                
                if dist <= 3:
                    seen.add(other)
                    constellation.add(other)
                    queue.append(other)
       
        constellations.append(constellation)

    answer = len(constellations)
    print(f"\nPart 1: {answer}")


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]

helpers.time_it(part_1, data)
