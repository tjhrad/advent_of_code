#!/usr/bin/env python3

import time
import numpy as np
from collections import defaultdict
import utils


def solve_part1(data):
    answer = 0
    print(f"\nPart 1: {answer}")


def solve_part2(data):
    answer = 0
    print(f"\nPart 2: {answer}")


def main():
    with open("./data/test.txt", "r") as f:
        data = [line.strip('\n') for line in f]

    start_time = time.time()
    solve_part1(data)
    print(utils.format_time(time.time() - start_time))

    start_time = time.time()
    solve_part2(data)
    print(utils.format_time(time.time() - start_time))


if __name__ == "__main__":
    main()
