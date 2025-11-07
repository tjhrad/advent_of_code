#!/usr/bin/env python3

import helpers
from collections import defaultdict
import math 


def part1(data):
    asteroids = get_asteroids(data)

    for a in asteroids.keys():
        seen = set()
        for a2 in asteroids.keys():
            if a == a2:
                continue
            
            dx = (a2[0] - a[0])
            dy = (a2[1] - a[1])

            g = math.gcd(dx, dy)
            dx //= g
            dy //= g

            if (dx, dy) in seen:
                continue

            seen.add((dx, dy))
        asteroids[a] = len(seen)
    
    answer = max([n for n in asteroids.values()])
    print(f"\nPart 1: {answer}")


def part2(data):
    asteroids = get_asteroids(data)

    best = None
    visible_counts = {}

    for a in asteroids.keys():
        seen = set()
        for a2 in asteroids.keys():
            if a == a2:
                continue
            
            dx = (a2[0] - a[0])
            dy = (a2[1] - a[1])

            g = math.gcd(dx, dy)
            dx //= g
            dy //= g

            if (dx, dy) in seen:
                continue

            seen.add((dx, dy))
        visible_counts[a] = len(seen)
        if best is None or visible_counts[a] > visible_counts[best]:
            best = a
        
    station = best
    angles = {}

    for x2, y2 in asteroids:
        if (x2, y2) == station:
            continue

        dx = x2 - station[0]
        dy = y2 - station[1]

        # Angle: 0 = up, rotate clockwise
        angle = math.atan2(dx, -dy)

        # Normalize to [0, 2π)
        if angle < 0:
            angle += 2 * math.pi

        dist = math.hypot(dx, dy)

        if angle not in angles:
            angles[angle] = []

        angles[angle].append((dist, (x2, y2)))

    for angle in angles.keys():
        angles[angle].sort(key=lambda x: x[0])

    ordered_angles = sorted(angles.keys())

    count = 0
    result = None

    while True:
        for angle in ordered_angles:
            if angles[angle]:
                dist, asteroid = angles[angle].pop(0)
                count += 1

                if count == 200:
                    result = asteroid
                    break

        if result:
            break

    answer = (result[0] * 100) + result[1]
    print(f"\nPart 2: {answer}")


def get_asteroids(data):
    asteroids = defaultdict(int)

    for y, line in enumerate(data):
        for x, c in enumerate(line):
            if c == "#":
                asteroids[(x, y)] = 0

    return asteroids

    

with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]


helpers.time_it(part1, data)
helpers.time_it(part2, data)
