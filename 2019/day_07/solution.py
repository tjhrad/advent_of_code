#!/usr/bin/env python3

import helpers
import itertools


def part1(data):
    program = [int(n) for n in data[0].split(",")]

    best_output = 0

    for phase_setting in itertools.permutations([0, 1, 2, 3, 4]):
        amplifiers = [IntcodeComputer(program) for _ in range(5)]
        input_signal = 0
        for i in range(5):
            amp = amplifiers[i]
            amp.input_queue = [phase_setting[i], input_signal]
            output = amp.run_until_output()
            input_signal = output

        if input_signal > best_output:
            best_output = amplifiers[-1].output

    answer = best_output
    print(f"\nPart 1: {answer}")


def part2(data):
    program = [int(n) for n in data[0].split(",")]

    best_output = 0

    for phase_setting in itertools.permutations([5, 6, 7, 8, 9]):
        amplifiers = [IntcodeComputer(program) for _ in range(5)]

        for i in range(5):
            amplifiers[i].input_queue.append(phase_setting[i])

        input_signal = 0
        last_output = 0

        while not amplifiers[-1].halted:
            for i in range(5):
                amp = amplifiers[i]
                amp.input_queue.append(input_signal)
                output = amp.run_until_output()

                if output is not None:
                    input_signal = output
                    last_output = output

        if input_signal > best_output:
            best_output = last_output

    answer = best_output
    print(f"\nPart 2: {answer}")


class IntcodeComputer():
    def __init__(self, program):
        self.program = program.copy()
        self.ip = 0
        self.output = None
        self.paused = False
        self.halted = False
        self.input_queue = []

    def run_until_output(self):
        while True:
            mult_instruct = str(self.program[self.ip]).zfill(5)
            op = int(mult_instruct[-2:])
            modes = [int(mult_instruct[-3]), int(mult_instruct[-4]), int(mult_instruct[-5])]

            def get_param(offset):
                val = self.program[self.ip + offset]
                return val if modes[offset - 1] else self.program[val]

            if op == 99:
                self.halted = True
                return None
            elif op == 1:
                a, b, c = self.program[self.ip+1:self.ip+4]
                self.program[c] = (self.program[a] if not modes[0] else a) + (self.program[b] if not modes[1] else b)
                self.ip += 4
            elif op == 2:
                a, b, c = self.program[self.ip+1:self.ip+4]
                self.program[c] = (self.program[a] if not modes[0] else a) * (self.program[b] if not modes[1] else b)
                self.ip += 4
            elif op == 3:
                a = self.program[self.ip+1]
                self.program[a] = self.input_queue.pop(0)
                self.ip += 2
            elif op == 4:
                a = self.program[self.ip+1]
                self.output = (self.program[a] if not modes[0] else a)
                self.ip += 2
                return self.output
            elif op == 5:
                a = get_param(1)
                b = get_param(2)
                self.ip = b if a != 0 else self.ip + 3
            elif op == 6:
                a = get_param(1)
                b = get_param(2)
                self.ip = b if a == 0 else self.ip + 3
            elif op == 7:
                a, b, c = self.program[self.ip+1:self.ip+4]
                self.program[c] = 1 if (self.program[a] if not modes[0] else a) < (self.program[b] if not modes[1] else b) else 0
                self.ip += 4
            elif op == 8:
                a, b, c = self.program[self.ip+1:self.ip+4]
                self.program[c] = 1 if (self.program[a] if not modes[0] else a) == (self.program[b] if not modes[1] else b) else 0
                self.ip += 4
            else:
                raise ValueError(f"Unknown opcode {op} at position {self.ip}")


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]


helpers.time_it(part1, data)
helpers.time_it(part2, data)
