#!/usr/bin/env python3

import time
import aoc_tools


def solve_part1(data):
    answer = 0

    stream = data[0]

    in_garbage = False
    ignore_next = False
    num_group_score = 0
    for s in stream:
        if ignore_next:
            ignore_next = False
            continue

        if (s == "!"):
            ignore_next = True

        if in_garbage and (s == ">"):
            in_garbage = False
            continue
        elif in_garbage:
            continue
        
        if (s == "{"):
            num_group_score += 1
        elif (s == "}"):
            answer += num_group_score
            num_group_score -= 1
        elif (s == "<"):
            in_garbage = True
    
    print("\nPart 1: " + str(answer))


def solve_part2(data):
    answer = 0

    stream = data[0]
    in_garbage = False
    ignore_next = False
    for s in stream:
        if ignore_next:
            ignore_next = False
            continue

        if (s == "!"):
            ignore_next = True

        if in_garbage and (s == ">"):
            in_garbage = False
            continue
        elif in_garbage:
            if (s != "!"):
                answer += 1
            continue
        
        if (s == "<"):
            in_garbage = True

    print("\nPart 2: " + str(answer))


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
