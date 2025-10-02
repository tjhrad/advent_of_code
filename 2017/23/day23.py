#!/usr/bin/env python3

import numpy as np
from collections import defaultdict
from math import sqrt
import utils


def solve_part1(data):
    registers = defaultdict(int)
    answer, reg_h = run(registers, data)
    print(f"\nPart 1: {answer}")


def solve_part2(data):
    h = 0
    start = 107900
    end = 124900
    step = 17
    for b in range(start, end+1, step):
        if not is_prime(b):
            h += 1
    answer = h
    print(f"\nPart 2: {answer}")


def is_prime(n):
    if n <= 1:
        return False
    for i in range(2, int(sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True


def run(registers, data):
    mul_count = 0
    instruct = 0
    while True:
        op, X, Y = data[instruct].split()
        if op == "set":
            if utils.is_integer(Y):
                registers[X] = int(Y)
            else:
                registers[X] = registers[Y]
            instruct += 1
        elif op == "sub":
            if utils.is_integer(Y):
                registers[X] -= int(Y)
            else:
                registers[X] -= registers[Y]
            instruct += 1
        elif op == "mul":
            if utils.is_integer(Y):
                registers[X] = registers[X] * int(Y)
            else:
                registers[X] = registers[X] * registers[Y]
            instruct += 1
            mul_count += 1
        elif op == "jnz":
            if utils.is_integer(X):
                if int(X) != 0:
                    if utils.is_integer(Y):
                        instruct += int(Y)
                    else:
                        instruct += registers[Y]
                else:
                    instruct += 1
            else:
                if registers[X] != 0:
                    if utils.is_integer(Y):
                        instruct += int(Y)
                    else:
                        instruct += registers[Y]
                else:
                    instruct += 1
        if instruct < 0 or instruct >= len(data):
            break
    return mul_count, registers['h']


def main():
    with open("./data/input.txt", "r") as f:
        data = [line.strip() for line in f]

    utils.time_it(solve_part1, data)
    utils.time_it(solve_part2, data)


if __name__ == "__main__":
    main()
