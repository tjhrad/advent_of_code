#!/usr/bin/env python3

import time
import itertools
import aoc_tools

input_file_path = "./data/input.txt"

# Read file
with open(input_file_path,"r") as f:
  data = [line.strip() for line in f]

def part1():
  answer = 0
  for line in data:
    numbers = [int(x) for x in line.split()]
    numbers.sort()
    answer += numbers[-1] - numbers[0]

  print("\nPart 1: " + str(answer))

def part2():
  answer = 0
  for line in data:
    numbers = [int(x) for x in line.split()]
    for a, b in itertools.combinations(numbers, 2):
      if (a % b == 0):
        answer += int(a/b)
        break
      if (b % a == 0):
        answer += int(b/a)
        break
    
  print("\nPart 2: " + str(answer))


start_time = time.time()
part1()
print(aoc_tools.format_time(time.time() - start_time))

start_time = time.time()
part2()
print(aoc_tools.format_time(time.time() - start_time))