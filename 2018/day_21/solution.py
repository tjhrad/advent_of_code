#!/usr/bin/env python3

import helpers

def part_1(data):
    registers = [0] * 6

    while True:
        registers[2] = registers[3] | 0X10000
        registers[3] = 1505483
        while True:
            registers[4] = registers[2] & 0xFF
            registers[3] += registers[4]
            registers[3] &= 0xFFFFFF
            registers[3] *= 65899
            registers[3] &= 0xFFFFFF
            if 256 > registers[2]:
                break
            registers[2] = registers[2] // 256
        break

    answer = registers[3]
    print(f"\nPart 1: {answer}")


def part_2(data):
    registers = [0] * 6

    values = set()
    answer = 0
    while True:
        registers[2] = registers[3] | 0X10000
        registers[3] = 1505483
        while True:
            registers[4] = registers[2] & 0xFF
            registers[3] += registers[4]
            registers[3] &= 0xFFFFFF
            registers[3] *= 65899
            registers[3] &= 0xFFFFFF
            if 256 > registers[2]:
                if registers[3] not in values:
                    answer = registers[3]
                values.add(registers[3])
                break
            registers[2] = registers[2] // 256

        if len(values) == 10778:
            break

    print(f"\nPart 2: {answer}")


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]

helpers.time_it(part_1, data)
helpers.time_it(part_2, data)
