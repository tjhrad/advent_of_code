#!/usr/bin/env python3

import time
import aoc_tools

input_file_path = "./2/data/input.txt"

# Read file line by line
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
    is_done = False
    for n in numbers:
      if (is_done):
        break
      for n2 in numbers:
        if (n == n2):
          continue
        if (n2 % n == 0):
          answer += int(n2/n)
          is_done = True
          break
        if (n % n2 == 0):
          answer += int(n/n2)
          is_done = True
          break
  print("\nPart 2: " + str(answer))

start_time = time.time()
part1()
print(aoc_tools.format_time(time.time() - start_time))

start_time = time.time()
part2()
print(aoc_tools.format_time(time.time() - start_time))