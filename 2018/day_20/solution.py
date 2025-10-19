#!/usr/bin/env python3

import helpers
from collections import deque, defaultdict

def part_1(data):
    graph = build_graph(data[0])
    answer, _ = find_distance(graph)
    print(f"\nPart 1: {answer}")


def part_2(data):
    graph = build_graph(data[0])
    _, answer = find_distance(graph)
    print(f"\nPart 2: {answer}")


def build_graph(regex):
    DIRECTIONS = {"N": (0, -1), "E": (1, 0), "S": (0, 1), "W": (-1, 0)}

    if regex.startswith("^"): regex = regex[1:]
    if regex.endswith("$"): regex = regex[:-1]

    graph = defaultdict(set)
    current_positions = {(0, 0)}
    stack = []

    for c in regex:
        if c in "NESW":
            next_positions = set()
            dx, dy = DIRECTIONS[c]
            for (x, y) in current_positions:
                next_pos = (x + dx, y + dy)
                graph[(x, y)].add(next_pos)
                graph[next_pos].add((x, y))
                next_positions.add(next_pos)
            current_positions = next_positions
        elif c == "(":
            stack.append((set(current_positions), []))
        elif c == "|":
            positions_before, alternatives = stack[-1]
            alternatives.append(set(current_positions))
            current_positions = set(positions_before)
        elif c == ")":
            positions_before, alternatives = stack.pop()
            alternatives.append(set(current_positions))
            new_positions = set().union(*alternatives)
            current_positions = new_positions
        else:
            pass

    return graph


def find_distance(graph, start=(0, 0)):
    # BFS
    queue = deque([start])
    distances = {start:0}
    while queue:
        current = queue.popleft()
        for edge in graph[current]:
            if edge not in distances:
                distances[edge] = distances[current] + 1
                queue.append(edge)
    return max(distances.values()), sum([1 for d in distances.values() if d >= 1000])


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]

helpers.time_it(part_1, data)
helpers.time_it(part_2, data)
