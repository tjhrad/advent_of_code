#!/usr/bin/env python3

import helpers
from collections import defaultdict
import math


def part1(data):
    reactions = parse_reactions(data)
    answer = ore_required('FUEL', 1, reactions, defaultdict(int))
    print(f"\nPart 1: {answer}")


def part2(data):
    reactions = parse_reactions(data)
    target = 1000000000000
    high = 10_000_000
    low = 0

    while low <= high:
        mid = (low + high) // 2
        ore = ore_required('FUEL', mid, reactions, defaultdict(int))

        if ore <= target:
            best = mid
            low = mid + 1
        else:
            high = mid - 1

    answer = best
    print(f"\nPart 2: {answer}")


def ore_required(target, amount, reactions, leftovers):
    if target == 'ORE':
        return amount

    output_quantity, inputs = reactions[target]

    if leftovers[target] >= amount:
        leftovers[target] -= amount
        return 0

    amount -= leftovers[target]
    leftovers[target] = 0

    batches = math.ceil(amount/output_quantity)
    ore = 0

    for name, quantity in inputs:
        ore += ore_required(name, quantity * batches, reactions, leftovers)
        
    leftovers[target] += batches * output_quantity - amount

    return ore

def parse_reactions(data):
    reactions = {}
    for line in data:
        inputs, output = line.strip().split(" => ")
        output_qty, output_name = output.split()
        inputs = [(name, int(qty)) for qty, name in (x.split() for x in inputs.split(", "))]
        reactions[output_name] = (int(output_qty), inputs)
    return reactions

with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]


helpers.time_it(part1, data)
helpers.time_it(part2, data)
