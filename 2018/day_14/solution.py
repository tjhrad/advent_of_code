#!/usr/bin/env python3

import helpers


def solve_part1(data):
    elf1, elf2 = 0, 1
    recipes = [3, 7]
    n_recipes = 513401

    target = 10 + n_recipes

    while len(recipes) < target:
        s = recipes[elf1] + recipes[elf2]

        if s >= 10:
            recipes.append(s // 10)
        
        recipes.append(s % 10)

        elf1 = (elf1 + 1 + recipes[elf1]) % len(recipes)
        elf2 = (elf2 + 1 + recipes[elf2]) % len(recipes)

    answer = ""
    answer += "".join([str(r) for r in recipes[n_recipes:n_recipes + 10]])
    print(f"\nPart 1: {answer}")   


def solve_part2(data):
    elf1, elf2 = 0, 1
    recipes = [3, 7]
    target_sequence = "513401"
    target_len = len(target_sequence)
    target_ints = [int(c) for c in target_sequence]

    sequence_found = False
    while not sequence_found:
        s = recipes[elf1] + recipes[elf2]

        if s >= 10:
            recipes.append(s // 10)
            if target_ints == recipes[-target_len:]:
                sequence_found = True
                break
        
        recipes.append(s % 10)
        if target_ints == recipes[-target_len:]:
            sequence_found = True
            break

        elf1 = (elf1 + 1 + recipes[elf1]) % len(recipes)
        elf2 = (elf2 + 1 + recipes[elf2]) % len(recipes)

    answer = len(recipes) - target_len
    print(f"\nPart 2: {answer}")


def main():
    with open("./input.txt", "r") as f:
        data = [line.rstrip('\n') for line in f]

    helpers.time_it(solve_part1, data)
    helpers.time_it(solve_part2, data)


if __name__ == "__main__":
    main()