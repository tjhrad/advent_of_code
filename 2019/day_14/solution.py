#!/usr/bin/env python3

import helpers
from collections import defaultdict


def part1(data):
    reactions = parse_reactions(data)
    answer = ore_required('FUEL', 1, reactions, defaultdict(int))
    print(f"\nPart 1: {answer}")


def part2(data):
    answer = 0
    print(f"\nPart 2: {answer}")


def ore_required(target, amount, reactions, leftovers):
    if target == 'ORE':
        return amount


    for name, quantity in reactions:
        print(":)")
        
    return 0

def parse_reactions(data):
    reactions = {}
    for line in data:
        inputs, output = line.strip().split(" => ")
        output_qty, output_name = output.split()
        inputs = [(name, int(qty)) for qty, name in (x.split() for x in inputs.split(", "))]
        reactions[output_name] = (int(output_qty), inputs)
    return reactions

with open("./test.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]


helpers.time_it(part1, data)
helpers.time_it(part2, data)
