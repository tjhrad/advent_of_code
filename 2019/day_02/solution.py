#!/usr/bin/env python3

import helpers
import copy
import itertools

def part1(data):
    integers = [int(x) for x in data[0].split(",")]

    integers[1] = 12
    integers[2] = 2

    integers = run(integers)

    answer = integers[0]
    print(f"\nPart 1: {answer}")


def part2(data):
    starting_integers = [int(x) for x in data[0].split(",")]

    integers = copy.deepcopy(starting_integers)
    
    last_noun = last_verb = 0

    while True:
        for noun, verb in itertools.product(range(100), range(100)):
            integers[1] = last_noun = noun
            integers[2] = last_verb = verb

            integers = run(integers)

            if integers[0] == 19690720:
                break

            integers = copy.deepcopy(starting_integers)
        else:
            continue

        break
        
    answer = 100 * last_noun + last_verb
    print(f"\nPart 2: {answer}")


def run(integers):
    ip = 0

    while True:
        op, a, b, c = integers[ip], integers[ip + 1], integers[ip + 2], integers[ip + 3]

        if op == 1:
            integers[c] = integers[a] + integers[b]
        elif op == 2:
            integers[c] = integers[a] * integers[b]
        elif op == 99:
            break
        else:
            print("UNKNOWN OP CODE")
            break

        ip += 4

        if ip > len(integers):
            ip = 0

    return integers


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]

helpers.time_it(part1, data)
helpers.time_it(part2, data)
