#!/usr/bin/env python3

import helpers
import os, time

def part_1(data):
    ip_reg, instructions = parse_data(data)
    registers = [0] * 6

    ip = 0
    while 0 <= ip < len(instructions):
        registers[ip_reg] = ip
        execute_instruction(instructions[ip], registers)
        ip = registers[ip_reg]
        ip += 1
    
    answer = registers[0]
    print(f"\nPart 1: {answer}")   


def part_2(data):
    # This will only work for my input. 
    # I watched the code run to discover what n should be set to
    factors = set()
    answer = 0
    n = 10551277
    for i in range(1, int(n**0.5) + 1):
        if (n % i) == 0:
            factors.add(i)
            factors.add(n/i)
    
    answer = int(sum(factors))
    print(f"\nPart 2: {answer}")


def parse_data(data):
    ip_reg = None
    instructions = []
    for line in data:
        parts = line.split()
        if "#" in line:
            ip_reg = int(parts[1])
        else:
            instruct = [parts[0]] + [int(n) for n in parts[1:]]
            instructions.append(instruct)
    return ip_reg, instructions


def execute_instruction(instruction, reg):
    op, a, b, c = instruction
    
    if op == 'addr':
        # addr (add register) stores into register C the result of adding register A and register B.
        reg[c] = reg[a] + reg[b]
    elif op == 'addi':
        # addi (add immediate) stores into register C the result of adding register A and value B.
        reg[c] = reg[a] + b
    elif op == 'mulr':
        # mulr (multiply register) stores into register C the result of multiplying register A and register B.
        reg[c] = reg[a] * reg[b]
    elif op == 'muli':
        # muli (multiply immediate) stores into register C the result of multiplying register A and value B.
        reg[c] = reg[a] * b
    elif op == 'banr':
        # banr (bitwise AND register) stores into register C the result of the bitwise AND of register A and register B.
        reg[c] = reg[a] & reg[b]
    elif op == 'bani':
        # bani (bitwise AND immediate) stores into register C the result of the bitwise AND of register A and value B.
        reg[c] = reg[a] & b
    elif op == 'borr':
        # borr (bitwise OR register) stores into register C the result of the bitwise OR of register A and register B.
        reg[c] = reg[a] | reg[b]
    elif op == 'bori':
        # bori (bitwise OR immediate) stores into register C the result of the bitwise OR of register A and value B.
        reg[c] = reg[a] | b
    elif op == 'setr':
        # setr (set register) copies the contents of register A into register C. (Input B is ignored.)
        reg[c] = reg[a]
    elif op == 'seti':
        # seti (set immediate) stores value A into register C. (Input B is ignored.)
        reg[c] = a
    elif op == 'gtir':
        #gtir (greater-than immediate/register) sets register C to 1 if value A is greater than register B. Otherwise, register C is set to 0.
        if a > reg[b]:
            reg[c] = 1
        else:
            reg[c] = 0
    elif op == 'gtri':
        #gtri (greater-than register/immediate) sets register C to 1 if register A is greater than value B. Otherwise, register C is set to 0.
        if reg[a] > b:
            reg[c] = 1
        else:
            reg[c] = 0
    elif op == 'gtrr':
        #gtrr (greater-than register/register) sets register C to 1 if register A is greater than register B. Otherwise, register C is set to 0.
        if reg[a] > reg[b]:
            reg[c] = 1
        else:
            reg[c] = 0
    elif op == 'eqir':
        #eqir (equal immediate/register) sets register C to 1 if value A is equal to register B. Otherwise, register C is set to 0.
        if a == reg[b]:
            reg[c] = 1
        else:
            reg[c] = 0
    elif op == 'eqri':
        #eqri (equal register/immediate) sets register C to 1 if register A is equal to value B. Otherwise, register C is set to 0.
        if reg[a] == b:
            reg[c] = 1
        else:
            reg[c] = 0
    elif op == 'eqrr':
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