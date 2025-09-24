#!/usr/bin/env python3

import time
import aoc_tools

input_file_path = "./data/input.txt"

with open(input_file_path,"r") as f:
  data = [line.strip() for line in f]


def part1():
  answer = 0

  for passphrase in data:
    words = passphrase.split()
    if (all_unique(words)):
      answer += 1

  print("\nPart 1: " + str(answer))

def part2():
  answer = 0

  for passphrase in data:
    words = passphrase.split()
    if not (has_anagram(words)):
      answer += 1
  
  print("\nPart 2: " + str(answer))


def all_unique(list):
  return len(list) == len(set(list))


def has_anagram(words):
  seen = set()
  for word in words:
    # normalize the word by sorting its characters once
    key = ''.join(sorted(word))
    if key in seen:
      return True
    seen.add(key)
  return False



start_time = time.time()
part1()
print(aoc_tools.format_time(time.time() - start_time))

start_time = time.time()
part2()
print(aoc_tools.format_time(time.time() - start_time))