#!/usr/bin/env python3

import helpers
from collections import defaultdict, deque
import copy


def part1(data):
    program = [int(x) for x in data[0].split(",")]
    paths, map = find_path_bfs(program)
    answer = min(len(p) for p in paths)
    print(f"\nPart 1: {answer}")


def part2(data):
    program = [int(x) for x in data[0].split(",")]
    paths, map = find_path_bfs(program)
    answer = time_to_fill(map)
    print(f"\nPart 2: {answer}")


def time_to_fill(map):
    DIRECTIONS = [
        (0, -1),
        (0, 1),
        (-1, 0),
        (1, 0)
    ]
    time = 0

    start = None
    for key, val in map.items():
        if val == "O":
            start = key

    queue = deque([start])
    seen = set()

    while queue:
        next_queue = []
        for current in queue:
            for d in DIRECTIONS:
                next_pos = (current[0] + d[0], current[1] + d[1])
                if next_pos in seen:
                    continue

                if next_pos in map and map[next_pos] == "#":
                    continue
                
                map[next_pos] = "O"
                seen.add(next_pos)
                next_queue.append(next_pos)
        queue.clear()
        [queue.append(n) for n in next_queue]
        if queue:
            time += 1

    return time


def find_path_bfs(program):
    graph = defaultdict(str)
    graph[(0, 0)] = "."

    bot1 = Bot(program)
    bot1.queue_next_move(1)
    bot2 = Bot(program)
    bot2.queue_next_move(2)
    bot3 = Bot(program)
    bot3.queue_next_move(3)
    bot4 = Bot(program)
    bot4.queue_next_move(4)

    seen = set((0, 0))
    paths = []
    queue = deque([bot1, bot2, bot3, bot4])

    while queue:
        current = queue.popleft()

        out = current.run_until_output()

        if out == 2:
            current.move()
            graph[current.get_current_position()] = "O"
            paths.append(current.get_path())
        elif out == 1:
            current.move()
            graph[current.get_current_position()] = "."
        elif out == 0:
            current.move()
            graph[current.get_current_position()] = "#"
            continue
        else:
            raise ValueError("Unknown value for out: {out}")

        for n in range(1, 5):
            neighbor_bot = copy.deepcopy(current)
            neighbor_bot.queue_next_move(n)
            if neighbor_bot.next_pos is not None and neighbor_bot.next_pos not in seen:
                queue.append(neighbor_bot)
                seen.add(neighbor_bot.next_pos)
                
    return paths, graph


def print_map(graph):
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


class Bot:
    def __init__(self, program):
        self.program: Dict[int, int] = defaultdict(int)
        for i, v in enumerate(program):
            self.program[i] = v

        self.ip:int = 0
        self.relative_base:int = 0
        self.output: int | None = None
        self.halted: bool = False
        self.input_queue: list[int] = []

        self.current_pos = (0, 0)
        self.next_pos = None
        self.path = []
        self.DIRECTIONS = [
        (0, -1),
        (0, 1),
        (-1, 0),
        (1, 0)
        ]


    def get_current_position(self):
        return self.current_pos

    def add_position(self, position):
        path.append(position)

    def get_path(self):
        return self.path

    def queue_next_move(self, d):
        self.input_queue.append(d)
        self.next_pos = (self.current_pos[0] + self.DIRECTIONS[d - 1][0], self.current_pos[1] + self.DIRECTIONS[d - 1][1])

    def move(self):
        self.current_pos = self.next_pos
        self.path.append(self.current_pos)
        self.next_pos = None

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
