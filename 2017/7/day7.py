#!/usr/bin/env python3

import time
import aoc_tools

input_file_path = "./data/input.txt"

with open(input_file_path, "r") as f:
    data = [line.strip() for line in f]


def part1():
    answer = get_root_node(data)

    print("\nPart 1: " + str(answer))


def part2():
    root_node = get_root_node(data)
    answer = balance_tower(root_node)

    print("\nPart 2: " + str(answer))


def get_root_node(input_data):
    children = set()
    parents = set()

    for line in input_data:
        parts = line.split()
        parent = parts[0]
        parents.add(parent)

        if "->" in line:
            # collect children
            child_nodes = line.split("->")[1].strip().split(", ")
            children.update(child_nodes)

    # root is the parent that’s never a child
    root = (parents - children).pop()
    return root


"""Global variables"""
node_weights_base = {}
node_weights_total = {}
node_children = {}
def balance_tower(root):

    for line in data:
        # Initialize the weights of each node
        line_split = line.split()
        line_weight = line_split[1]
        line_weight = line_weight.replace("(", "")
        line_weight = line_weight.replace(")", "")
        node_weights_base[line_split[0]] = int(line_weight)
        node_weights_total[line_split[0]] = int(line_weight)

        # Store the children for each node
        if "->" in line:
            line_split_2 = line.split(" -> ")
            line_split_children = line_split_2[1].split(", ")
            node_children[line_split[0]] = line_split_children
        else:
            node_children[line_split[0]] = []

    update_weights(root)

    balanced_weight = 0

    # Find the program that is causing the imbalance and return it's balanced weight
    current_node = root
    while True:
        weights = [node_weights_total[child] for child in node_children[current_node]]
        heaviest_weight = max(weights)
        lightest_weight = min(weights)
        unique_count = len(set(weights))

        # Stop looping if all of the programs are balanced
        if unique_count == 1:
            break

        for child in node_children[current_node]:
            if node_weights_total[child] == heaviest_weight:
                current_node = child
                balanced_weight = node_weights_base[current_node] - (
                    heaviest_weight - lightest_weight
                )
                break
    return balanced_weight


def update_weights(current_node):
    # Recursively update the total weight of each program
    if len(node_children[current_node]) == 0:
        return node_weights_total[current_node]

    for child in node_children[current_node]:
        node_weights_total[current_node] += update_weights(child)

    return node_weights_total[current_node]



def main():
    start_time = time.time()
    part1()
    print(aoc_tools.format_time(time.time() - start_time))

    start_time = time.time()
    part2()
    print(aoc_tools.format_time(time.time() - start_time))


if __name__ == "__main__":
    main()
