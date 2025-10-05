#!/usr/bin/env python3

import helpers


def solve_part1(data):
    answer = len(react_polymer(data[0]))
    print(f"\nPart 1: {answer}")


def solve_part2(data):
    answer = None
    lowercase_letters = list(map(chr, range(97, 123)))
    for letter in lowercase_letters:
        polymer = data[0]
        polymer = polymer.replace(letter, "").replace(letter.upper(), "")
        polymer = react_polymer(polymer)
        if answer is None:
            answer = len(polymer)
        elif len(polymer) < answer:
            answer = len(polymer)

    print(f"\nPart 2: {answer}")


def react_polymer(polymer):
    stack = []
    for char in polymer:
        if not stack:
            stack.append(char)
            continue
        
        if stack[-1] != char and char.upper() == stack[-1].upper():
            stack.pop()
        else:
            stack.append(char)
    return ''.join(x for x in stack)


def main():
    with open("./input.txt", "r") as f:
        data = [line.strip() for line in f]

    helpers.time_it(solve_part1, data)
    helpers.time_it(solve_part2, data)


if __name__ == "__main__":
    main()