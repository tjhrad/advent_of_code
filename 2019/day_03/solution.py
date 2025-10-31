#!/usr/bin/env python3

import helpers

def part1(data):
    wire1 = get_wire(data[0])
    wire2 = get_wire(data[1])

    intersections = set(wire1) & set(wire2)

    answer = min([abs(x) + abs(y) for x, y in intersections])
    print(f"\nPart 1: {answer}")


def part2(data):
    wire1 = get_wire(data[0])
    wire2 = get_wire(data[1])

    intersections = set(wire1) & set(wire2)

    answer = min([(wire1.index(i) + 1) + (wire2.index(i) + 1) for i in intersections])
    print(f"\nPart 2: {answer}")


def get_wire(string):
    wire_str = [x for x in string.split(",")]
    DIRECTIONS = {"U":(0, -1), "D":(0, 1), "L":(-1, 0), "R":(1, 0)}

    wire = []

    current_pos = (0, 0)
    for w in wire_str:
        for _ in range(int(w[1:])):
            current_pos = (current_pos[0] + DIRECTIONS[w[0]][0], current_pos[1] + DIRECTIONS[w[0]][1])
            wire.append(current_pos)
    
    return wire


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]

helpers.time_it(part1, data)
helpers.time_it(part2, data)
