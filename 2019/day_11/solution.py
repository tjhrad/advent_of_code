#!/usr/bin/env python3

import helpers
from collections import defaultdict
from typing import Dict

def part1(data):
    program = [int(n) for n in data[0].split(",")]
    robot = Robot(program)
    robot.input_queue.append(0)
    while not robot.halted:
        robot.step()
    answer = robot.paint_count
    print(f"\nPart 1: {answer}")


def part2(data):
    program = [int(n) for n in data[0].split(",")]
    robot = Robot(program)
    robot.input_queue.append(1)
    while not robot.halted:
        robot.step()
    print_message(robot.panels)
    answer = robot.paint_count
    print(f"\nPart 2: {answer}")


class Robot:
    def __init__(self, program):
        self.program: Dict[int, int] = defaultdict(int)
        for i, v in enumerate(program):
            self.program[i] = v

        self.ip:int = 0
        self.relative_base:int = 0
        self.output: int | None = None
        self.halted: bool = False
        self.input_queue: list[int] = []

        self.panels = defaultdict(int)
        self.seen = set()
        self.x = 0
        self.y = 0
        self.paint_count = 0
        self.current_direction = "U"
        self.DIRECTIONS = {"U":(0, -1), "D":(0, 1), "L":(-1, 0), "R":(1, 0)}
        self.TURN_RIGHT = {"U":"R", "D":"L", "L":"U", "R":"D"}
        self.TURN_LEFT = {"U":"L", "D":"R", "L":"D", "R":"U"}


    def step(self):
        self.run_until_output()
        if self.output == 0:
            self.panels[(self.x, self.y)] = 0
        elif self.output == 1:
            self.panels[(self.x, self.y)] = 1
        else:
            raise ValueError(f"Unknown output {self.output}")

        if (self.x, self.y) not in self.seen:
            self.paint_count += 1
            self.seen.add((self.x, self.y))

        self.run_until_output()

        if self.output == 0:
            self.current_direction = self.TURN_LEFT[self.current_direction]
        elif self.output == 1:
            self.current_direction = self.TURN_RIGHT[self.current_direction]
        else:
            raise ValueError(f"Unknown output {self.output}")

        self.x, self.y = (self.x + self.DIRECTIONS[self.current_direction][0], self.y + self.DIRECTIONS[self.current_direction][1])
        
        if (self.x, self.y) in self.panels:
            self.input_queue.append(self.panels[(self.x, self.y)])
        else:
            self.input_queue.append(0)


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


def print_message(panels):
    xmin = min([x for x, _ in panels.keys()])
    xmax = max([x for x, _ in panels.keys()])
    ymin = min([y for _, y in panels.keys()])
    ymax = max([y for _, y in panels.keys()])
    
    print("")
    for y in range(ymin, ymax + 1):
        row = ""
        for x in range(xmin, xmax + 1):
            if panels[(x, y)] == 1:
                row += "#"
            else:
                row += "."
        print(row)


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]


helpers.time_it(part1, data)
helpers.time_it(part2, data)
