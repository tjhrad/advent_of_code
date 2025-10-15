#!/usr/bin/env python3

from collections import defaultdict
import copy
import helpers


def part_1(data):
    answer = 0
    for i, line in enumerate(data):
        if "Before" in line:
            registers_start = [int(x) for x in data[i].replace("Before: [", "").replace("]", "").split(", ")]
            instruction = data[i + 1]
            registers_end = [int(x) for x in data[i + 2].replace("After:  [", "").replace("]", "").split(", ")]
            valid_opcodes = get_valid_opcodes(instruction, registers_start, registers_end)
            if len(valid_opcodes) >= 3:
                answer += 1

    print(f"\nPart 1: {answer}")   


def part_2(data):
    codes = defaultdict(set)
    for i, line in enumerate(data):
        if "Before" in line:
            registers_start = [int(x) for x in data[i].replace("Before: [", "").replace("]", "").split(", ")]
            instruction = data[i + 1]
            registers_end = [int(x) for x in data[i + 2].replace("After:  [", "").replace("]", "").split(", ")]
            valid_opcodes = get_valid_opcodes(instruction, registers_start, registers_end)
            op, _, _, _ = [int(s) for s in instruction.split()]
            codes[op].update(valid_opcodes)

    final_opcodes = defaultdict(str)
    while len(codes) > 0:
        keys_to_remove = []
        for key, val in codes.items():
            if len(val) == 1:
                final_opcodes[key] = list(val)[0]
                for key_2, val_2 in codes.items():
                    if key == key_2:
                        continue

                    if list(val)[0] in val_2:
                        codes[key_2].remove(list(val)[0])

                keys_to_remove.append(key)
                
        for key in keys_to_remove:
            codes.pop(key)

    registers = [0] * 4

    for i, line in enumerate(data):
        if i < 3238:
            continue

        registers = run(line, registers, final_opcodes)
        # Run instructions

    answer = registers[0]
    print(f"\nPart 2: {answer}")


def get_valid_opcodes(instruction, registers_start, registers_end):
    valid_opcodes = []
    op, a, b, c = [int(s) for s in instruction.split()]
    
    # addr (add register) stores into register C the result of adding register A and register B.
    reg = copy.deepcopy(registers_start)
    reg[c] = reg[a] + reg[b]
    if reg == registers_end:
        valid_opcodes.append("addr")

    # addi (add immediate) stores into register C the result of adding register A and value B.
    reg = copy.deepcopy(registers_start)
    reg[c] = reg[a] + b
    if reg == registers_end:
        valid_opcodes.append("addi")

    # mulr (multiply register) stores into register C the result of multiplying register A and register B.
    reg = copy.deepcopy(registers_start)
    reg[c] = reg[a] * reg[b]
    if reg == registers_end:
        valid_opcodes.append("mulr")

    # muli (multiply immediate) stores into register C the result of multiplying register A and value B.
    reg = copy.deepcopy(registers_start)
    reg[c] = reg[a] * b
    if reg == registers_end:
        valid_opcodes.append("muli")


    # banr (bitwise AND register) stores into register C the result of the bitwise AND of register A and register B.
    reg = copy.deepcopy(registers_start)
    reg[c] = reg[a] & reg[b]
    if reg == registers_end:
        valid_opcodes.append("banr")

    # bani (bitwise AND immediate) stores into register C the result of the bitwise AND of register A and value B.
    reg = copy.deepcopy(registers_start)
    reg[c] = reg[a] & b
    if reg == registers_end:
        valid_opcodes.append("bani")

    
    # borr (bitwise OR register) stores into register C the result of the bitwise OR of register A and register B.
    reg = copy.deepcopy(registers_start)
    reg[c] = reg[a] | reg[b]
    if reg == registers_end:
        valid_opcodes.append("borr")

    # bori (bitwise OR immediate) stores into register C the result of the bitwise OR of register A and value B.
    reg = copy.deepcopy(registers_start)
    reg[c] = reg[a] | b
    if reg == registers_end:
        valid_opcodes.append("bori")

    
    # setr (set register) copies the contents of register A into register C. (Input B is ignored.)
    reg = copy.deepcopy(registers_start)
    reg[c] = reg[a]
    if reg == registers_end:
        valid_opcodes.append("setr")

    # seti (set immediate) stores value A into register C. (Input B is ignored.)
    reg = copy.deepcopy(registers_start)
    reg[c] = a
    if reg == registers_end:
        valid_opcodes.append("seti")


    #gtir (greater-than immediate/register) sets register C to 1 if value A is greater than register B. Otherwise, register C is set to 0.
    reg = copy.deepcopy(registers_start)
    if a > reg[b]:
        reg[c] = 1
    else:
        reg[c] = 0
    if reg == registers_end:
        valid_opcodes.append("gtir")

    #gtri (greater-than register/immediate) sets register C to 1 if register A is greater than value B. Otherwise, register C is set to 0.
    reg = copy.deepcopy(registers_start)
    if reg[a] > b:
        reg[c] = 1
    else:
        reg[c] = 0
    if reg == registers_end:
        valid_opcodes.append("gtri")

    #gtrr (greater-than register/register) sets register C to 1 if register A is greater than register B. Otherwise, register C is set to 0.
    reg = copy.deepcopy(registers_start)
    if reg[a] > reg[b]:
        reg[c] = 1
    else:
        reg[c] = 0
    if reg == registers_end:
        valid_opcodes.append("gtrr")


    #eqir (equal immediate/register) sets register C to 1 if value A is equal to register B. Otherwise, register C is set to 0.
    reg = copy.deepcopy(registers_start)
    if a == reg[b]:
        reg[c] = 1
    else:
        reg[c] = 0
    if reg == registers_end:
        valid_opcodes.append("eqir")

    #eqri (equal register/immediate) sets register C to 1 if register A is equal to value B. Otherwise, register C is set to 0.
    reg = copy.deepcopy(registers_start)
    if reg[a] == b:
        reg[c] = 1
    else:
        reg[c] = 0
    if reg == registers_end:
        valid_opcodes.append("eqri")

    #eqrr (equal register/register) sets register C to 1 if register A is equal to register B. Otherwise, register C is set to 0.
    reg = copy.deepcopy(registers_start)
    if reg[a] == reg[b]:
        reg[c] = 1
    else:
        reg[c] = 0
    if reg == registers_end:
        valid_opcodes.append("eqrr")
    
    return valid_opcodes


def run(instruction, reg, opcode_dict):
    op, a, b, c = [int(s) for s in instruction.split()]
    
    if opcode_dict[op] == 'addr':
        # addr (add register) stores into register C the result of adding register A and register B.
        reg[c] = reg[a] + reg[b]
    elif opcode_dict[op] == 'addi':
        # addi (add immediate) stores into register C the result of adding register A and value B.
        reg[c] = reg[a] + b
    elif opcode_dict[op] == 'mulr':
        # mulr (multiply register) stores into register C the result of multiplying register A and register B.
        reg[c] = reg[a] * reg[b]
    elif opcode_dict[op] == 'muli':
        # muli (multiply immediate) stores into register C the result of multiplying register A and value B.
        reg[c] = reg[a] * b
    elif opcode_dict[op] == 'banr':
        # banr (bitwise AND register) stores into register C the result of the bitwise AND of register A and register B.
        reg[c] = reg[a] & reg[b]
    elif opcode_dict[op] == 'bani':
        # bani (bitwise AND immediate) stores into register C the result of the bitwise AND of register A and value B.
        reg[c] = reg[a] & b
    elif opcode_dict[op] == 'borr':
        # borr (bitwise OR register) stores into register C the result of the bitwise OR of register A and register B.
        reg[c] = reg[a] | reg[b]
    elif opcode_dict[op] == 'bori':
        # bori (bitwise OR immediate) stores into register C the result of the bitwise OR of register A and value B.
        reg[c] = reg[a] | b
    elif opcode_dict[op] == 'setr':
        # setr (set register) copies the contents of register A into register C. (Input B is ignored.)
        reg[c] = reg[a]
    elif opcode_dict[op] == 'seti':
        # seti (set immediate) stores value A into register C. (Input B is ignored.)
        reg[c] = a
    elif opcode_dict[op] == 'gtir':
        #gtir (greater-than immediate/register) sets register C to 1 if value A is greater than register B. Otherwise, register C is set to 0.
        if a > reg[b]:
            reg[c] = 1
        else:
            reg[c] = 0
    elif opcode_dict[op] == 'gtri':
        #gtri (greater-than register/immediate) sets register C to 1 if register A is greater than value B. Otherwise, register C is set to 0.
        if reg[a] > b:
            reg[c] = 1
        else:
            reg[c] = 0
    elif opcode_dict[op] == 'gtrr':
        #gtrr (greater-than register/register) sets register C to 1 if register A is greater than register B. Otherwise, register C is set to 0.
        if reg[a] > reg[b]:
            reg[c] = 1
        else:
            reg[c] = 0
    elif opcode_dict[op] == 'eqir':
        #eqir (equal immediate/register) sets register C to 1 if value A is equal to register B. Otherwise, register C is set to 0.
        if a == reg[b]:
            reg[c] = 1
        else:
            reg[c] = 0
    elif opcode_dict[op] == 'eqri':
        #eqri (equal register/immediate) sets register C to 1 if register A is equal to value B. Otherwise, register C is set to 0.
        if reg[a] == b:
            reg[c] = 1
        else:
            reg[c] = 0
    elif opcode_dict[op] == 'eqrr':
        #eqrr (equal register/register) sets register C to 1 if register A is equal to register B. Otherwise, register C is set to 0.
        if reg[a] == reg[b]:
            reg[c] = 1
        else:
            reg[c] = 0
    
    return reg


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]

helpers.time_it(part_1, data)
helpers.time_it(part_2, data)