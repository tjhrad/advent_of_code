#!/usr/bin/env python3

import numpy as np
from collections import defaultdict
import utils


def solve_part1(data):
    bridges = find_bridges(data)
    answer = find_strongest(bridges)
    print(f"\nPart 1: {answer}")


def solve_part2(data):
    bridges = find_bridges(data)
    answer = find_strongest_longest(bridges)
    print(f"\nPart 2: {answer}")


def find_bridges(data):
    # Build graph
    components = []
    components_dict = defaultdict(list)
    for component in data:
        a, b = [int(x) for x in component.split("/")]
        components.append((a, b))
        components_dict[a].append((a, b))
        components_dict[b].append((a, b))

    bridges = []

    def dfs(open_port, used, current_bridge):
        bridges.append(current_bridge[:])

        for comp in components_dict[open_port]:
            if comp in used:
                continue
            a, b = comp
            next_port = b if a == open_port else a
            dfs(next_port, used | {comp}, current_bridge + [comp])

    dfs(0, set(), [])

    return bridges


def find_strongest(bridges):
    strongest = 0
    for bridge in bridges:
        strength = 0
        for c in bridge:
            strength += c[0] + c[1]
        if strength > strongest:
            strongest = strength
    return strongest


def find_strongest_longest(bridges):
    max_len = max([len(a) for a in bridges])
    strongest = 0
    for bridge in bridges:
        if len(bridge) != max_len:
            continue
        strength = 0
        for c in bridge:
            strength += c[0] + c[1]
        if strength > strongest:
            strongest = strength
    return strongest


def main():
    with open("./data/input.txt", "r") as f:
        data = [line.strip() for line in f]

    utils.time_it(solve_part1, data)
    utils.time_it(solve_part2, data)


if __name__ == "__main__":
    main()