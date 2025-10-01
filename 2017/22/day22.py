#!/usr/bin/env python3

import numpy as np
from collections import defaultdict
import utils


def solve_part1(data):
    NUM_BURSTS = 10000

    nodes = parse_data(data)

    r = int((len(data) - 1)/2)
    c = int((len(data[0]) - 1)/2)
    start_node = (r, c)
    
    virus = Virus(start_node)
  
    infection_count = 0
    for _ in range(NUM_BURSTS):
        if virus.current_node not in nodes:
            nodes[virus.current_node] = "."

        # Turn
        if (nodes[virus.current_node] == "#"):
            virus.turn_right()
        else:
            virus.turn_left()

        # Modify State
        if (nodes[virus.current_node] == "."):
            nodes[virus.current_node] = "#"
            infection_count += 1
        else:
            nodes[virus.current_node] = "."
        
        virus.move()

    answer = infection_count
    print(f"\nPart 1: {answer}")


def solve_part2(data):
    NUM_BURSTS = 10_000_000

    nodes = parse_data(data)

    r = int((len(data) - 1)/2)
    c = int((len(data[0]) - 1)/2)
    start_node = (r, c)
    
    virus = Virus(start_node)
  
    infection_count = 0
    for _ in range(NUM_BURSTS):
        if virus.current_node not in nodes:
            nodes[virus.current_node] = "."

        # Turn
        if (nodes[virus.current_node] == "#"):
            virus.turn_right()
        elif (nodes[virus.current_node] == "."):
            virus.turn_left()
        elif (nodes[virus.current_node] == "F"):
            virus.flip_direction()

        # Modify State
        if (nodes[virus.current_node] == "."):
            nodes[virus.current_node] = "W"
        elif (nodes[virus.current_node] == "W"):
            nodes[virus.current_node] = "#"
            infection_count += 1
        elif (nodes[virus.current_node] == "#"):
            nodes[virus.current_node] = "F"
        else:
            nodes[virus.current_node] = "."
        
        virus.move()

    answer = infection_count
    print(f"\nPart 2: {answer}")


def parse_data(data):
    nodes = defaultdict(str)
    for row in range(len(data)):
        for col in range(len(data[0])):
            n = (row, col)
            nodes[n] = data[row][col]
    return nodes


class Virus:
    DIRECTIONS = {
        "UP":    (-1, 0),
        "DOWN":  (1, 0),
        "LEFT":  (0, -1),
        "RIGHT": (0, 1)
    }

    FLIP = {
        "UP": "DOWN",
        "RIGHT": "LEFT",
        "DOWN": "UP",
        "LEFT": "RIGHT"
    }

    RIGHT_TURNS = {
        "UP": "RIGHT",
        "RIGHT": "DOWN",
        "DOWN": "LEFT",
        "LEFT": "UP"
    }

    LEFT_TURNS = {v: k for k, v in RIGHT_TURNS.items()}

    def __init__(self, start_node):
        self.current_node = start_node
        self.direction = "UP"

    def move(self):
        dr, dc = self.DIRECTIONS[self.direction]
        self.current_node = (self.current_node[0] + dr, self.current_node[1] + dc)

    def turn_right(self):
        self.direction = self.RIGHT_TURNS[self.direction]

    def turn_left(self):
        self.direction = self.LEFT_TURNS[self.direction]

    def flip_direction(self):
        self.direction = self.FLIP[self.direction]

    def __repr__(self):
        return f"Virus(Node={self.current_node}, direction={self.direction})"



def main():
    with open("./data/input.txt", "r") as f:
        data = [line.strip() for line in f]

    utils.time_it(solve_part1, data)
    utils.time_it(solve_part2, data)


if __name__ == "__main__":
    main()
