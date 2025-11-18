#!/usr/bin/env python3

import helpers
from collections import defaultdict, deque
import copy


def part1(data):
    program = [int(x) for x in data[0].split(",")]
    graph = get_graph(program)
    print_graph(graph)
    answer = 0
    print(f"\nPart 1: {answer}")


def part2(data):
    answer = 0
    print(f"\nPart 2: {answer}")

# TODO: 
# Create multiple bots that all are walking down separate paths.
# Use BFS and at each point copy.deepcopy(bot) the bot 4x for each direction and store each in the queue.
# Store the path in each bot
def find_path_bfs(program):
    start = (0, 0)
    bot = Computer(program)
    seen = set()
    queue = deque([bot])

def get_graph(program):
    DIRECTIONS = [(0, -1), (0, 1), (-1, 0), (1, 0)]
    graph = defaultdict(str)
    current_location = (0, 0)
    current_direction = 0
    remote_control = Computer(program)
    graph[current_location] = '.'

    while True:
        remote_control.input_queue.append(current_direction + 1)
        output = remote_control.run_until_output()
        if output == 2:
            next_location = (current_location[0] + DIRECTIONS[current_direction][0], current_location[1] + DIRECTIONS[current_direction][1])
            graph[next_location] = 'O'
            current_location = next_location
            break
        elif output == 1:
            next_location = (current_location[0] + DIRECTIONS[current_direction][0], current_location[1] + DIRECTIONS[current_direction][1])
            graph[next_location] = '.'
            current_location = next_location
        elif output == 0:
            next_location = (current_location[0] + DIRECTIONS[current_direction][0], current_location[1] + DIRECTIONS[current_direction][1])
            graph[next_location] = '#'
            current_direction = (current_direction + 1) % 4
        else:
            raise ValueError("UNKNOWN OUTPUT: {output}")

        print_graph(graph)
        input("Press enter")

    return graph


def print_graph(graph):
    xmin = min(x for x, y in graph.keys())
    ymin = min(y for x, y in graph.keys())
    xmax = max(x for x, y in graph.keys())
    ymax = max(y for x, y in graph.keys())

    for y in range(ymin, ymax + 1):
        row = ""
        for x in range(xmin, xmax + 1):
            if (x, y) in graph:
                row += graph[(x, y)]
            else:
                row += "?"
        print(row)


class Computer:
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
            self.output = None

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
                if len(self.input_queue) == 0:
                    return None
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
