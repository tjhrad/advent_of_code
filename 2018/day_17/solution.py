#!/usr/bin/env python3

from collections import defaultdict
import helpers
import os, time


def part_1(data):
    min_coord, max_coord, clay = parse_data(data)
    moving, resting = simulate_water(min_coord, max_coord, clay)

    min_y, max_y = min_coord[1], max_coord[1]
    moving = {m for m in moving if min_y <= m[1] <= max_y}
    resting = {r for r in resting if min_y <= r[1] <= max_y}

    answer = len(resting) + len(moving)
    print(f"\nPart 1: {answer}")   


def part_2(data):
    min_coord, max_coord, clay = parse_data(data)
    moving, resting = simulate_water(min_coord, max_coord, clay)

    min_y, max_y = min_coord[1], max_coord[1]
    resting = {r for r in resting if min_y <= r[1] <= max_y}

    answer = len(resting)
    print(f"\nPart 2: {answer}")


def parse_data(data): 
    clay = defaultdict(str) 
    smallest_y = smallest_x = float('inf') 
    largest_y = largest_x = float('-inf') 
    
    for line in data: 
        parts = line.split(", ") 
        if parts[0][0] == "x": 
            x = int(parts[0].replace("x=", "")) 
            y_min, y_max = [int(y) for y in parts[1].replace("y=", "").split("..")] 
        
            if x < smallest_x: 
                smallest_x = x 

            if x > largest_x: 
                largest_x = x 
            
            if y_min < smallest_y: 
                smallest_y = y_min 
            
            if y_max > largest_y: 
                largest_y = y_max 
                
            for y in range(y_min, y_max + 1): 
                clay[(x, y)] = "#" 
        else: 
            y = int(parts[0].replace("y=", "")) 
            x_min, x_max = [int(x) for x in parts[1].replace("x=", "").split("..")] 
            
            if x_min < smallest_x: 
                smallest_x = x_min 
                
            if x_max > largest_x: 
                largest_x = x_max 
                
            if y < smallest_y: 
                smallest_y = y 
                
            if y > largest_y: 
                largest_y = y 
            
            for x in range(x_min, x_max + 1): 
                clay[(x, y)] = "#" 
                
    return (smallest_x, smallest_y), (largest_x, largest_y), clay


def simulate_water(min_coord, max_coord, clay):
    min_x, min_y = min_coord
    max_x, max_y = max_coord
    stack = [(500, 0)]

    resting = set()
    moving = set()

    while stack:
        current = stack.pop()

        if current[1] > max_y:
            continue

        abyss = False
        while ((current[0], current[1] + 1) not in clay and 
                (current[0], current[1] + 1) not in resting):
            moving.add(current)
            current = (current[0], current[1] + 1)
                
            if current[1] > max_y: # Abyss
                abyss = True
                break
        
        if abyss:
            continue

        left_extended = []
        right_extended = []

        if ((current[0], current[1] + 1) in clay or 
            (current[0], current[1] + 1) in resting):

            # LEFT
            left = current
            while True:
                below = (left[0], left[1] + 1)
                if below not in clay and below not in resting:
                    if left not in moving:
                        stack.append(left)
                    break
                
                left_extended.append(left)
                left = (left[0] - 1, left[1])

                if left in clay:
                    break
                    
            # RIGHT
            right = current
            while True:
                below = (right[0], right[1] + 1)
                if below not in clay and below not in resting:
                    if right not in moving:
                        stack.append(right)
                    break
                
                right_extended.append(right)
                right = (right[0] + 1, right[1])

                if right in clay:
                    break
            
            if right in clay and left in clay: # Water 'contained'
                resting.update(left_extended + [current] + right_extended)
                moving.difference_update(left_extended + [current] + right_extended)
                stack.append((current[0], current[1] - 1))
            else:
                moving.update(left_extended + [current] + right_extended)

    moving.discard((500, 0))
    return moving, resting


def print_grid(min_coord, max_coord, clay, falling, resting, pause=0.1):
    os.system("clear")  # clear terminal for animation
    for y in range(min_coord[1] - 1, max_coord[1] + 2):
        row = []
        for x in range(min_coord[0] - 1, max_coord[0]+ 2):
            if (x, y) in clay:
                row.append("#")
            elif (x, y) in resting:
                row.append("~")
            elif (x, y) in falling:
                row.append("|")
            elif (x, y) == (500, 0):
                row.append("+")
            else:
                row.append(".")
        print("".join(row))
    time.sleep(pause)


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]

helpers.time_it(part_1, data)
helpers.time_it(part_2, data)