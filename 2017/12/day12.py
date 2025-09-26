#!/usr/bin/env python3

import time
from collections import defaultdict
import aoc_tools


def solve_part1(data):
    answer = 0

    programs = defaultdict(set)

    for line in data:
        parent_str, children_str = line.split(" <-> ")
        for x in children_str.split(", "):
            programs[int(parent_str)].add(int(x))
            programs[int(x)].add(int(parent_str))
    
    for parent in programs.keys():
        if (0 in find_all_connections(parent, programs)):
            answer += 1

    print("\nPart 1: " + str(answer))


def solve_part2(data):
    answer = 0

    programs = defaultdict(set)

    for line in data:
        parent_str, children_str = line.split(" <-> ")
        for x in children_str.split(", "):
            programs[int(parent_str)].add(int(x))
            programs[int(x)].add(int(parent_str))
    
    answer = count_groups(programs)
    print("\nPart 2: " + str(answer))


def find_all_connections(parent, programs):
    seen = set()
    stack = [parent]
    connections = set()

    # Find all connected 'pipes' using DFS
    while stack:
        node = stack.pop()
        for child in programs.get(node, []):
            if child not in seen:
                seen.add(child)
                connections.add(child)
                stack.append(child)

    return connections


def count_groups(programs):
    seen = set()
    groups = []

    for parent in programs:
        if parent not in seen:
            group = find_all_connections(parent, programs)
            group.add(parent)
            seen.update(group)
            groups.append(group)

    return len(groups)



def main():
    with open("./data/input.txt", "r") as f:
        data = [line.strip() for line in f]

    start_time = time.time()
    solve_part1(data)
    print(aoc_tools.format_time(time.time() - start_time))

    start_time = time.time()
    solve_part2(data)
    print(aoc_tools.format_time(time.time() - start_time))


if __name__ == "__main__":
    main()
