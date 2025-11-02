#!/usr/bin/env python3

import helpers
from collections import defaultdict


def part1(data):
    graph = defaultdict(list)

    for line in data:
        a, b = line.split(")")
        graph[b].append(a)

    answer = 0
    for g in graph.keys():
        queue = [g]
        seen = set()

        while queue:
            current = queue.pop()

            if current not in graph:
                continue

            for n in graph[current]:
                if n in seen:
                    continue

                seen.add(n)
                queue.append(n)
                answer += 1

    print(f"\nPart 1: {answer}")


def part2(data):
    graph = defaultdict(list)

    for line in data:
        a, b = line.split(")")
        graph[a].append(b)
        graph[b].append(a)

    queue = [["YOU", []]]
    seen = set()

    answer = None
    while queue:
        current, path = queue.pop()

        if current not in graph:
            continue

        if current == "SAN":
            answer = len(path) - 2
            break

        for n in graph[current]:
            if n in seen:
                continue

            seen.add(n)
            queue.append([n, path + [n]])

    print(f"\nPart 2: {answer}")


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]


helpers.time_it(part1, data)
helpers.time_it(part2, data)
