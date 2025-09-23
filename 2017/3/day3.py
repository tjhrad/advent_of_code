#!/usr/bin/env python3

import time
import numpy as np
import aoc_tools

input_file_path = "./data/input.txt"

with open(input_file_path,"r") as f:
  data = [line.strip() for line in f]


def part1():
  answer = 0
  target = int(data[0])
  
  side_length = 1
  while (side_length * side_length) < target:
    side_length += 1
  
  position_from_end = (side_length * side_length) - target

  start_point = find_starting_index(side_length, position_from_end)
  end_point = get_access_port_index(side_length)

  answer = manhattan_distance(start_point, end_point)

  print("\nPart 1: " + str(answer))

def part2():
  answer = 0
  target = int(data[0])

  side_length = 1
  while (side_length * side_length) < target:
    side_length += 1

  end_point = get_access_port_index(side_length)

  arr = np.zeros((side_length, side_length), dtype=int)

  direction = "RIGHT"
  current_pos = list(end_point)
  arr[current_pos[1]][current_pos[0]] = 1

  #Fill in the array counterclockwise starting from the access port index.
  for x in range(2, (side_length * side_length) + 1):
    if (direction == "RIGHT"):
      current_pos[0] += 1
      val = sum_neighbors(arr, current_pos[1], current_pos[0])
      arr[current_pos[1]][current_pos[0]] = val
      if (arr[current_pos[1] - 1][current_pos[0]] == 0):
        direction = "UP"
    elif (direction == "UP"):
      current_pos[1] -= 1
      val = sum_neighbors(arr, current_pos[1], current_pos[0])
      if (arr[current_pos[1]][current_pos[0] - 1] == 0):
        direction = "LEFT"
    elif (direction == "LEFT"):
      current_pos[0] -= 1
      val = sum_neighbors(arr, current_pos[1], current_pos[0])
      if (arr[current_pos[1] + 1][current_pos[0]] == 0):
        direction = "DOWN"
    elif (direction == "DOWN"):
      current_pos[1] += 1
      val = sum_neighbors(arr, current_pos[1], current_pos[0])
      if (arr[current_pos[1]][current_pos[0 + 1]] == 0):
        direction = "RIGHT"

    arr[current_pos[1]][current_pos[0]] = val

    # Stop looping if a number larger than the target is found
    if (val > target):
      answer = val
      break


  print("\nPart 2: " + str(answer))


def find_starting_index(s_length, p_from_end):
  x = 0
  y = 0

  #If even, set the starting indices to the bottom right corner
  if not ((s_length * s_length) % 2):
    for i in range(p_from_end):
      if (x < s_length - 1):
        x += 1
      else:
        y += 1
  else:
    x = s_length - 1
    y = s_length - 1
    for i in range(p_from_end):
      if (x > 0):
        x -= 1
      else:
        y -= 1
  
  return (x,y)

def get_access_port_index(s_length):
  #Odd
  if ((s_length * s_length) % 2):
    x = int((s_length - 1)/2)
    y = int((s_length - 1)/2)
  #Even
  else: 
    x = int(s_length/2) - 1
    y = int(s_length/2)
  
  return (x,y)

def manhattan_distance(p1, p2):
  return sum(abs(a - b) for a, b in zip(p1, p2))

def sum_neighbors(arr, row, col):
    # Define the window boundaries
    r_start = max(0, row - 1)
    r_end   = min(arr.shape[0], row + 2)  # +2 because slice is exclusive
    c_start = max(0, col - 1)
    c_end   = min(arr.shape[1], col + 2)
    
    # Extract the subarray around the element
    sub = arr[r_start:r_end, c_start:c_end]
    
    # Sum everything except the element itself
    return sub.sum() - arr[row, col]


start_time = time.time()
part1()
print(aoc_tools.format_time(time.time() - start_time))

start_time = time.time()
part2()
print(aoc_tools.format_time(time.time() - start_time))