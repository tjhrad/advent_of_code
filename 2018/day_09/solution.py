#!/usr/bin/env python3

from collections import deque
import helpers


def solve_part1(data):
    n_players = int(data[0].split()[0])
    last_marble = int(data[0].split()[6])

    answer = simulate_game(n_players, last_marble)
    print(f"\nPart 1: {answer}")


def solve_part2(data):
    n_players = int(data[0].split()[0])
    last_marble = int(data[0].split()[6])

    answer = simulate_game(n_players, last_marble * 100)
    print(f"\nPart 2: {answer}")


def simulate_game(n_players, last_marble):
    players = [0] * n_players
    circle = deque([0])
    current_marble = 1
    
    while current_marble <= last_marble:
        for elf in range(0, n_players):
            if current_marble > last_marble:
                break
            
            if current_marble % 23 == 0:
                players[elf] += current_marble
                circle.rotate(7) 
                players[elf] += circle.pop()
                circle.rotate(-1) # Adjust for current marble
            else:
                circle.rotate(-1)
                circle.append(current_marble)

            current_marble += 1

    return max(players)


def main():
    with open("./input.txt", "r") as f:
        data = [line.strip() for line in f]

    helpers.time_it(solve_part1, data)
    helpers.time_it(solve_part2, data)


if __name__ == "__main__":
    main()