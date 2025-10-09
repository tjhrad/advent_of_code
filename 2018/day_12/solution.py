#!/usr/bin/env python3

from collections import deque, defaultdict
import helpers


def solve_part1(data):
    starting_state = set([i for i, p in enumerate(data[0].replace("initial state: ", "")) if p == "#"])
    rules = get_rules(data)
    answer = simulate_plants(starting_state, rules)
    print(f"\nPart 1: {answer}")    


def solve_part2(data):
    starting_state = set([i for i, p in enumerate(data[0].replace("initial state: ", "")) if p == "#"])
    rules = get_rules(data)
    answer = simulate_plants(starting_state, rules, 50_000_000_000)
    print(f"\nPart 2: {answer}")


def get_rules(data):
    rules = [False] * 32
    for line in data:
        if "=>" in line:
            key, val = line.split(" => ")
            if val == "#":
                integer = 0
                if key[0] == "#":
                    integer += (16)
                if key[1] == "#":
                    integer += (8)
                if key[2] == "#":
                    integer += (4)
                if key[3] == "#":
                    integer += (2)
                if key[4] == "#":
                    integer += (1)
                rules[integer] = True
    return rules

def simulate_plants(current_state, rules, n_generations=20):
    last_normalized_state = current_state
    stable_generations_count = 0
    for g in range(n_generations):
        next_state = set()
        for i in range(min(current_state) - 2, max(current_state) + 3):
            integer = 0
            if i - 2 in current_state:
                integer += (16)
            if i - 1 in current_state:
                integer += (8)
            if i in current_state:
                integer += (4)
            if i + 1 in current_state:
                integer += (2)
            if i + 2 in current_state:
                integer += (1)
            
            if rules[integer]:
                next_state.add(i)

        min_index = min(next_state)
        normalized_state = set([p - min_index for p in next_state])

        if normalized_state == last_normalized_state and stable_generations_count > 5:
            delta_sum = sum(next_state) - sum(current_state)
            return sum(next_state) + ((n_generations - (g + 1)) * delta_sum)
        elif normalized_state == last_normalized_state:
            stable_generations_count += 1
        else:
            stable_generations_count = 0
        
        last_normalized_state = normalized_state
        
        current_state = next_state
        
    return sum(current_state)


def main():
    with open("./input.txt", "r") as f:
        data = [line.strip() for line in f]

    helpers.time_it(solve_part1, data)
    helpers.time_it(solve_part2, data)


if __name__ == "__main__":
    main()