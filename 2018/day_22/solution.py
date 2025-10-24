#!/usr/bin/env python3

import helpers
from collections import defaultdict
import heapq


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

    answer = sum([r[2] for r in regions.values()])
    print(f"\nPart 1: {answer}")


def part_2(data):

    depth = int(data[0].split(": ")[1])
    tx, ty = [int(c) for c in data[1].split(": ")[1].split(",")]

    regions = defaultdict(list)

    for y in range(ty * 20):
        for x in range(tx * 20):
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

    answer = astar(regions, (0, 0), (tx, ty))
    print(f"\nPart 2: {answer}")


class Node:
    def __init__(self, parent=None, position=None, tool=None):
        self.parent = parent
        self.position = position
        self.tool = tool

        self.g = 0  # cost from start
        self.h = 0  # heuristic (Manhattan distance to target)
        self.f = 0  # total cost

    def __eq__(self, other):
        return self.position == other.position and self.tool == other.tool

    def __lt__(self, other):  # for heapq
        return self.f < other.f


# Allowed tools for each region type
def allowed_tools(region_type):
    if region_type == 0:  # Rocky
        return {"torch", "gear"}
    elif region_type == 1:  # Wet
        return {"gear", "neither"}
    elif region_type == 2:  # Narrow
        return {"torch", "neither"}


def astar(map_data, start_pos, end_pos):

    # compute bounds with margin (ensure we allow exploration past target)
    max_x = max(x for x, _ in map_data.keys())
    max_y = max(y for _, y in map_data.keys())

    # start node
    start_node = Node(None, start_pos, "torch")
    start_node.g = 0
    start_node.h = abs(start_pos[0] - end_pos[0]) + abs(start_pos[1] - end_pos[1])
    start_node.f = start_node.g + start_node.h

    open_heap = []
    heapq.heappush(open_heap, (start_node.f, start_node))

    # best g found so far for a (pos,tool)
    g_scores = {(start_pos, "torch"): 0}
    visited = set()

    while open_heap:
        _, current_node = heapq.heappop(open_heap)
        current_pos = current_node.position
        current_tool = current_node.tool

        # if we popped a stale node (worse g than recorded), skip
        if g_scores.get((current_pos, current_tool), float("inf")) < current_node.g:
            continue

        # mark visited for this (pos,tool)
        if (current_pos, current_tool) in visited:
            continue
        visited.add((current_pos, current_tool))

        # End condition: at target with torch
        if current_pos == end_pos and current_tool == "torch":
            return current_node.g

        # consider switching tools in-place
        cur_region = map_data.get(current_pos)
        if cur_region is not None:
            allowed_here = allowed_tools(cur_region[2])
            for new_tool in allowed_here:
                if new_tool == current_tool:
                    continue
                new_g = current_node.g + 7
                state = (current_pos, new_tool)
                if new_g < g_scores.get(state, float("inf")) and state not in visited:
                    new_node = Node(current_node, current_pos, new_tool)
                    new_node.g = new_g
                    new_node.h = abs(current_pos[0] - end_pos[0]) + abs(current_pos[1] - end_pos[1])
                    new_node.f = new_node.g + new_node.h
                    g_scores[state] = new_g
                    heapq.heappush(open_heap, (new_node.f, new_node))

        # movement to neighbors
        for dx, dy in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
            x, y = current_pos[0] + dx, current_pos[1] + dy
            if x < 0 or y < 0 or x > max_x or y > max_y:
                continue
            if (x, y) not in map_data:
                continue

            region_type = map_data[(x, y)][2]
            allowed_next = allowed_tools(region_type)

            # If current tool is allowed in next, we can move with cost 1
            if current_tool in allowed_next:
                new_g = current_node.g + 1
                state = ((x, y), current_tool)
                if new_g < g_scores.get(state, float("inf")) and state not in visited:
                    new_node = Node(current_node, (x, y), current_tool)
                    new_node.g = new_g
                    new_node.h = abs(x - end_pos[0]) + abs(y - end_pos[1])
                    new_node.f = new_node.g + new_node.h
                    g_scores[state] = new_g
                    heapq.heappush(open_heap, (new_node.f, new_node))
            else:
                # If current tool not allowed in next, we must switch before moving.
                # We can only switch to a tool that is allowed in BOTH current and next.
                cur_region_type = map_data[current_pos][2]
                allowed_here = allowed_tools(cur_region_type)
                common = allowed_here & allowed_next
                for new_tool in common:
                    # switching (7) + move (1)
                    new_g = current_node.g + 7 + 1
                    state = ((x, y), new_tool)
                    if new_g < g_scores.get(state, float("inf")) and state not in visited:
                        new_node = Node(current_node, (x, y), new_tool)
                        new_node.g = new_g
                        new_node.h = abs(x - end_pos[0]) + abs(y - end_pos[1])
                        new_node.f = new_node.g + new_node.h
                        g_scores[state] = new_g
                        heapq.heappush(open_heap, (new_node.f, new_node))

    return None  # no path found


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]

helpers.time_it(part_1, data)
helpers.time_it(part_2, data)
