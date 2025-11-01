#!/usr/bin/env python3

import helpers

def part1(data):
    program = [int(n) for n in data[0].split(",")]
    answer = run(program, 1)
    print(f"\nPart 1: {answer}")


def part2(data):
    program = [int(n) for n in data[0].split(",")]
    answer = run(program, 5)
    print(f"\nPart 2: {answer}")


def run(program, input):
    program = program[:]
    ip = 0
    output = None

    while True:
        mult_instruct = str(program[ip]).zfill(5)
        op = int(mult_instruct[-2:])
        modes = [int(mult_instruct[-3]), int(mult_instruct[-4]), int(mult_instruct[-5])]

        def get_param(offset):
            val = program[ip + offset]
            return val if modes[offset - 1] else program[val]

        if op == 99:
            break
        elif op == 1:
            a, b, c = program[ip+1:ip+4]
            program[c] = (program[a] if not modes[0] else a) + (program[b] if not modes[1] else b)
            ip += 4
        elif op == 2:
            a, b, c = program[ip+1:ip+4]
            program[c] = (program[a] if not modes[0] else a) * (program[b] if not modes[1] else b)
            ip += 4
        elif op == 3:
            a = program[ip+1]
            program[a] = input
            ip += 2
        elif op == 4:
            a = program[ip+1]
            output = (program[a] if not modes[0] else a)
            ip += 2
        elif op == 5:
            a = get_param(1)
            b = get_param(2)
            ip = b if a != 0 else ip + 3
        elif op == 6:
            a = get_param(1)
            b = get_param(2)
            ip = b if a == 0 else ip + 3
        elif op == 7:
            a, b, c = program[ip+1:ip+4]
            program[c] = 1 if (program[a] if not modes[0] else a) < (program[b] if not modes[1] else b) else 0
            ip += 4
        elif op == 8:
            a, b, c = program[ip+1:ip+4]
            program[c] = 1 if (program[a] if not modes[0] else a) == (program[b] if not modes[1] else b) else 0
            ip += 4
        else:
            raise ValueError(f"Unknown opcode {op} at position {ip}")
            print("UNKNOWN OP CODE")
            break

    return output


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]

helpers.time_it(part1, data)
helpers.time_it(part2, data)
