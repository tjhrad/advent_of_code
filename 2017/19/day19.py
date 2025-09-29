#!/usr/bin/env python3

import time
import utils


def solve_part1(data):
    start = find_start(data)
    answer = walk_path(start, data)[0]
    print(f"\nPart 1: {answer}")


def solve_part2(data):
    start = find_start(data)
    answer = walk_path(start, data)[1]
    print(f"\nPart 2: {answer}")


def find_start(data):
    col = 0
    for c in data[0]:
        if c == '|':
            break
        col += 1
    return 0, col


def walk_path(start_node, data):
    letters = []
    pos = start_node
    direction = "DOWN"
    num_steps = 0

    DIRECTIONS = {
        "DOWN": (1, 0),
        "UP": (-1, 0),
        "RIGHT": (0, 1),
        "LEFT": (0, -1),
    }

    while True:
        row, col = pos
        char = data[row][col]
        num_steps += 1

        if char == "+":
            if direction in ("DOWN", "UP"):
                # check left/right
                right = (row + DIRECTIONS["RIGHT"][0], col + DIRECTIONS["RIGHT"][1])
                left = (row + DIRECTIONS["LEFT"][0], col + DIRECTIONS["LEFT"][1])

                if 0 <= right[0] < len(data) and 0 <= right[1] < len(data[0]) and data[right[0]][right[1]] != " ":
                    direction = "RIGHT"
                elif 0 <= left[0] < len(data) and 0 <= left[1] < len(data[0]) and data[left[0]][left[1]] != " ":
                    direction = "LEFT"

            else:
                # check up/down
                up = (row + DIRECTIONS["UP"][0], col + DIRECTIONS["UP"][1])
                down = (row + DIRECTIONS["DOWN"][0], col + DIRECTIONS["DOWN"][1])

                if 0 <= up[0] < len(data) and 0 <= up[1] < len(data[0]) and data[up[0]][up[1]] != " ":
                    direction = "UP"
                elif 0 <= down[0] < len(data) and 0 <= down[1] < len(data[0]) and data[down[0]][down[1]] != " ":
                    direction = "DOWN"

        elif char.isalpha():
            letters.append(char)

        # move to next position
        dr, dc = DIRECTIONS[direction]
        pos = (row + dr, col + dc)

        # stop if out of bounds or on a space
        if not (0 <= pos[0] < len(data) and 0 <= pos[1] < len(data[0])):
            break
        if data[pos[0]][pos[1]] == " ":
            break

    # Return tuple containing the letters seen as a string and the number of steps taken
    return "".join(letters), num_steps
        

def main():
    with open("./data/input.txt", "r") as f:
        data = [line.strip('\n') for line in f]

    start_time = time.time()
    solve_part1(data)
    print(utils.format_time(time.time() - start_time))

    start_time = time.time()
    solve_part2(data)
    print(utils.format_time(time.time() - start_time))


if __name__ == "__main__":
    main()
