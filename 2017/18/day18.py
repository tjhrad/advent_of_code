#!/usr/bin/env python3

import time
from collections import defaultdict
from collections import deque
import utils


def solve_part1(data):
    registers = defaultdict(int)

    answer = run(registers, data)
    print(f"\nPart 1: {answer}")


def solve_part2(data):
    registers_0 = defaultdict(int)
    registers_1 = defaultdict(int)

    registers_1["p"] = 1

    answer = run_duet(registers_0, registers_1, data)
    
    print(f"\nPart 2: {answer}")


def run(registers, instructions):
    last_sound = 0
    recovered_sound = 0
    current_instruction = 0
    while current_instruction < len(instructions):
        parts = instructions[current_instruction].split()
        op, reg = parts[0], parts[1]
        if op == "snd":
            last_sound = registers[reg]
        elif op == "set":
            if utils.is_integer(parts[2]):
                registers[reg] = int(parts[2])
            else:
                registers[reg] = registers[parts[2]]
        elif op == "add":
            if utils.is_integer(parts[2]):
                registers[reg] += int(parts[2])
            else:
                registers[reg] += registers[parts[2]]
        elif op == "mul":
            if utils.is_integer(parts[2]):
                registers[reg] *= int(parts[2])
            else:
                registers[reg] *= registers[parts[2]]
        elif op == "mod":
            if utils.is_integer(parts[2]):
                registers[reg] = registers[reg] % int(parts[2])
            else:
                registers[reg] = registers[reg] % registers[parts[2]]
        elif op == "rcv" and registers[reg] != 0:
            recovered_sound = last_sound
            break
        elif op == "jgz":
            if utils.is_integer(reg) and (int(reg) > 0):
                current_instruction += int(parts[2])
                continue
            elif registers[reg] > 0:
                current_instruction += int(parts[2])
                continue        
        current_instruction += 1

    return recovered_sound


def run_duet(registers_0, registers_1, instructions):
    count_sent_1 = 0

    sent_0 = deque()
    sent_1 = deque()

    running_program_0 = True
    running_program_1 = True

    waiting_program_0 = False
    waiting_program_1 = False

    current_instruction_0 = 0
    current_instruction_1 = 0

    while True:
        if current_instruction_0 < len(instructions):
            parts = instructions[current_instruction_0].split()
            op, reg = parts[0], parts[1]
            if op == "snd":
                if utils.is_integer(reg):
                    sent_0.append(int(reg))
                else:
                    sent_0.append(registers_0[reg])
                waiting_program_0 = False
                current_instruction_0 += 1
                
            elif op == "set":
                if utils.is_integer(parts[2]):
                    registers_0[reg] = int(parts[2])
                else:
                    registers_0[reg] = registers_0[parts[2]]
                waiting_program_0 = False
                current_instruction_0 += 1
            elif op == "add":
                if utils.is_integer(parts[2]):
                    registers_0[reg] += int(parts[2])
                else:
                    registers_0[reg] += registers_0[parts[2]]
                waiting_program_0 = False
                current_instruction_0 += 1
            elif op == "mul":
                if utils.is_integer(parts[2]):
                    registers_0[reg] *= int(parts[2])
                else:
                    registers_0[reg] *= registers_0[parts[2]]
                waiting_program_0 = False
                current_instruction_0 += 1
            elif op == "mod":
                if utils.is_integer(parts[2]):
                    registers_0[reg] = registers_0[reg] % int(parts[2])
                else:
                    registers_0[reg] = registers_0[reg] % registers_0[parts[2]]
                waiting_program_0 = False
                current_instruction_0 += 1
            elif op == "rcv":
                if sent_1:
                    registers_0[reg] = sent_1.popleft()
                    waiting_program_0 = False
                    current_instruction_0 += 1
                else:
                    waiting_program_0 = True
            elif op == "jgz":
                # evaluate X (first operand)
                if utils.is_integer(parts[1]):
                    x_val = int(parts[1])
                else:
                    x_val = registers_0[parts[1]]

                # evaluate Y (jump offset)
                if utils.is_integer(parts[2]):
                    y_val = int(parts[2])
                else:
                    y_val = registers_0[parts[2]]

                if x_val > 0:
                    current_instruction_0 += y_val
                else:
                    current_instruction_0 += 1

                waiting_program_0 = False
        else:
            running_program_0 = False

        if current_instruction_1 < len(instructions):
            parts = instructions[current_instruction_1].split()
            op, reg = parts[0], parts[1]
            if op == "snd":
                if utils.is_integer(reg):
                    sent_1.append(int(reg))
                else:
                    sent_1.append(registers_1[reg])
                current_instruction_1 += 1
                count_sent_1 += 1
            elif op == "set":
                if utils.is_integer(parts[2]):
                    registers_1[reg] = int(parts[2])
                else:
                    registers_1[reg] = registers_1[parts[2]]
                current_instruction_1 += 1
            elif op == "add":
                if utils.is_integer(parts[2]):
                    registers_1[reg] += int(parts[2])
                else:
                    registers_1[reg] += registers_1[parts[2]]
                current_instruction_1 += 1
            elif op == "mul":
                if utils.is_integer(parts[2]):
                    registers_1[reg] *= int(parts[2])
                else:
                    registers_1[reg] *= registers_1[parts[2]]
                current_instruction_1 += 1
            elif op == "mod":
                if utils.is_integer(parts[2]):
                    registers_1[reg] = registers_1[reg] % int(parts[2])
                else:
                    registers_1[reg] = registers_1[reg] % registers_1[parts[2]]
                current_instruction_1 += 1
            elif op == "rcv":
                if sent_0:
                    registers_1[reg] = sent_0.popleft()
                    waiting_program_1 = False
                    current_instruction_1 += 1
                else:
                    waiting_program_1 = True
            elif op == "jgz":
                # evaluate X (first operand)
                if utils.is_integer(parts[1]):
                    x_val = int(parts[1])
                else:
                    x_val = registers_1[parts[1]]

                # evaluate Y (jump offset)
                if utils.is_integer(parts[2]):
                    y_val = int(parts[2])
                else:
                    y_val = registers_1[parts[2]]

                if x_val > 0:
                    current_instruction_1 += y_val
                else:
                    current_instruction_1 += 1

                waiting_program_1 = False
        else:
            running_program_1 = False



        if (waiting_program_0 and (waiting_program_1 or not running_program_1)) or \
            (waiting_program_1 and (waiting_program_0 or not running_program_0)):
            break
    # Return the number of times that program 1 sent a value
    return count_sent_1


def main():
    with open("./data/input.txt", "r") as f:
        data = [line.strip() for line in f]

    start_time = time.time()
    solve_part1(data)
    print(utils.format_time(time.time() - start_time))

    start_time = time.time()
    solve_part2(data)
    print(utils.format_time(time.time() - start_time))


if __name__ == "__main__":
    main()
