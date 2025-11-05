#!/usr/bin/env python3

import helpers
import numpy as np


def part1(data):
    arr_1d = np.array([int(c) for c in data[0]])
    layers = arr_1d.reshape(-1, 6, 25)
    zero_counts = np.sum(layers == 0, axis=(1,2))
    target_layer = layers[np.argmin(zero_counts)]
    answer = np.sum(target_layer == 1) * np.sum(target_layer == 2)
    print(f"\nPart 1: {answer}")


def part2(data):
    arr_1d = np.array([int(c) for c in data[0]])
    layers = arr_1d.reshape(-1, 6, 25)
    output = layers[0].copy()

    for layer in layers[1:]:
        mask = output == 2
        output[mask] = layer[mask]

    print(output)
    answer = 0
    print(f"\nPart 2: {answer}")


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]


helpers.time_it(part1, data)
helpers.time_it(part2, data)
