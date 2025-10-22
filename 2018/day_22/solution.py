#!/usr/bin/env python3

import helpers
from collections import defaultdict


# 5620 too

def part_1(data):
    depth = int(data[0].split(": ")[1])
    tx, ty = [int(c) for c in data[1].split(": ")[1].split(",")]

    regions = defaultdict(list)

    for y in range(ty + 1):
        for x in range(tx + 1):
            geologic_index = None
            erosion_level = None

            if (x == 0 and y == 0) or (x == tx and y == ty):
                geologic_index = 0
            elif y == 0:
                geologic_index = x * 16807
            elif x == 0:
                geologic_index = y * 48271
            else:
                geologic_index = regions[(x - 1, y)][1] * regions[(x, y - 1)][1]

            erosion_level = (geologic_index + depth) % 20183
            region_type = erosion_level % 3

            regions[(x, y)] = [geologic_index, erosion_level, region_type]

    # Visualize
    #print_map(regions, tx, ty) # Debugging

    answer = sum([r[2] for r in regions.values()])
    print(f"\nPart 1: {answer}")


def part_2(data):
    """
    You start at 0,0 (the mouth of the cave) with the torch 
    equipped and must reach the target coordinates as 
    quickly as possible.
    """


    answer = 0
    print(f"\nPart 2: {answer}")


class Node():
    def __init__(self, parent=None, position=None, tool=None):
        self.parent = parent
        self.position = position

        self.g = 0
        self.h = 0
        self.f = 0
        self.time = 0
        self.tool = tool

    def __eq__(self, other):
        return self.postion == other.position and self.tool == other.tool


def astar(map, start_pos, end_pos):

    # Create the start and end nodes
    start_node = Node(None, start_pos, "torch")
    end_node = Node(None, end_pos, "torch")

    open_list = []
    closed_list = []

    open_list.append(start_node)

    while len(open_list) > 0:

        # Get the first item in open_list
        current_node = open_list[0]
        current_index = 0

        # Find the node in the list with the lowest cost (f)
        for i, node in enumerate(open_list):
            if node.f < current_node.f:
                current_node = node
                current_index = i
        
        # Remove the current node from open_list and add it to the closed list
        open_list.pop(current_index)
        closed_list.append(current_node)

        # Return the path if current = end
        # TODO: Will need to change this to adding up the time taken for each node
        if current_node.position == end_node.position:
            path = []
            current = current_node
            while current is not None:
                path.append(current.position)
                current = current.parent
            return path[::-1]

        # Get children nodes
        children = []
        for dx, dy in [(1,0), (-1, 0), (0, 1), (0, -1)]:

            child_x, child_y = (current_node.position[0] + dx, current_node.position[1] + dy)
            if child_x < 0 or child_y < 0 or child_x >= len(map[0]) or child_y >= len(map):
                continue

            child_node = Node(current_node, (child_x, child_y))
            children.append(child_node)

        for child in children:
            # TODO: verify that this works. I'm not sure what this will actually do
            if child in closed_list:
                continue
            
            # TODO: init g,h,f,time, and tool
            child.g = current_node.g + 1
            child.h = sum(abs(a-b) for a, b in zip(child.position, current_node.position))
            """
            In rocky regions, you can use the climbing gear or the torch. 
            You cannot use neither (you'll likely slip and fall).
            In wet regions, you can use the climbing gear or neither tool. 
            You cannot use the torch (if it gets wet, you won't have a light source).
            In narrow regions, you can use the torch or neither tool. You cannot use the climbing gear (it's too bulky to fit).
            """
            if map[child.position] == 0: # Rocky
                if current_node.tool == "gear" or current_node.tool == "torch":
                    child.tool = current_node.tool
            elif map[child.position] == 1: # Wet

            elif map[child.position] == 2: # Narow
            child.f 






def print_map(regions, tx, ty):
    for y in range(ty + 1):
        row = ""
        for x in range(tx + 1):
            if regions[(x, y)][2] == 0:
                row += '.'
            elif regions[(x, y)][2] == 1:
                row += '='
            elif regions[(x, y)][2] == 2:
                row += '|'
        print(row)


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]

helpers.time_it(part_1, data)
helpers.time_it(part_2, data)
