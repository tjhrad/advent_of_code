#!/usr/bin/env python3

import time
import aoc_tools

input_file_path = "./data/input.txt"

with open(input_file_path,"r") as f:
  data = [line.strip() for line in f]

def part1():
  answer = 0

  nums = [int(s) for s in data]
  
  i = 0
  while (i >= 0) and (i < len(nums)):
    answer += 1
    old_i = i
    i = i + nums[i]
    nums[old_i] += 1

  print("\nPart 1: " + str(answer))

def part2():
  answer = 0

  nums = [int(s) for s in data]

  i = 0
  while (i >= 0) and (i < len(nums)):
    answer += 1
    old_i = i
    i = i + nums[i]
    if (nums[old_i] >= 3):
      nums[old_i] -= 1
    else:
      nums[old_i] += 1

  print("\nPart 2: " + str(answer))


start_time = time.time()
part1()
print(aoc_tools.format_time(time.time() - start_time))

start_time = time.time()
part2()
print(aoc_tools.format_time(time.time() - start_time))