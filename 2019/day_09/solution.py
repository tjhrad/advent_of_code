#!/usr/bin/env python3

import helpers
from collections import defaultdict
from typing import List, Dict


def part1(data):
    program = [int(n) for n in data[0].split(",")]

    comp = IntcodeComputer(program)
    comp.input_queue.append(1)
    answer = None
    while not comp.halted:
        output = comp.run_until_output()
        if output is not None:
            answer = output

    print(f"\nPart 1: {answer}")


def part2(data):
    program = [int(n) for n in data[0].split(",")]

    comp = IntcodeComputer(program)
    comp.input_queue.append(2)
    answer = None
    while not comp.halted:
        output = comp.run_until_output()
        if output is not None:
            answer = output

    print(f"\nPart 2: {answer}")


class IntcodeComputer:
    def __init__(self, program):
        self.program: Dict[int, int] = defaultdict(int)
        for i, v in enumerate(program):
            self.program[i] = v

        self.ip:int = 0
        self.relative_base:int = 0
        self.output: int | None = None
        self.halted: bool = False
        self.input_queue: list[int] = []

    def run_until_output(self):
        while True:
            mult_instruct = str(self.program[self.ip]).zfill(5)
            op = int(mult_instruct[-2:])
            modes = [int(mult_instruct[-3]), int(mult_instruct[-4]), int(mult_instruct[-5])]

            def get_param(offset):
                val = self.program[self.ip + offset]
                if modes[offset - 1] == 0:   # position mode
                    return self.program[val]
                elif modes[offset - 1] == 1: # immediate mode
                    return val
                elif modes[offset - 1] == 2: # relative mode
                    return self.program[self.relative_base + val]

                raise ValueError(f"Unknown parameter mode")

            def get_write_addr(offset):
                val = self.program[self.ip + offset]
                return val if modes[offset - 1] == 0 else self.relative_base + val

            if op == 99:
                self.halted = True
                return None

            elif op == 1:  # add
                self.program[get_write_addr(3)] = get_param(1) + get_param(2)
                self.ip += 4

            elif op == 2:  # multiply
                self.program[get_write_addr(3)] = get_param(1) * get_param(2)
                self.ip += 4

            elif op == 3:  # input
                self.program[get_write_addr(1)] = self.input_queue.pop(0)
                self.ip += 2

            elif op == 4:  # output
                self.output = get_param(1)
                self.ip += 2
                return self.output

            elif op == 5:  # jump-if-true
                self.ip = get_param(2) if get_param(1) != 0 else self.ip + 3

            elif op == 6:  # jump-if-false
                self.ip = get_param(2) if get_param(1) == 0 else self.ip + 3

            elif op == 7:  # less than
                self.program[get_write_addr(3)] = 1 if get_param(1) < get_param(2) else 0
                self.ip += 4

            elif op == 8:  # equals
                self.program[get_write_addr(3)] = 1 if get_param(1) == get_param(2) else 0
                self.ip += 4

            elif op == 9:  # adjust relative base
                self.relative_base += get_param(1)
                self.ip += 2

            else:
                raise ValueError(f"Unknown opcode {op} at position {self.ip}")


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]


helpers.time_it(part1, data)
helpers.time_it(part2, data)
