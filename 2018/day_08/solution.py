#!/usr/bin/env python3

from collections import deque
import helpers


def solve_part1(data):
    nodes = get_nodes(data)
    
    def sum_metadata(node):
        return sum(node['metadata']) + sum(sum_metadata(c) for c in node['children'])

    answer = sum_metadata(nodes)
    print(f"\nPart 1: {answer}")


def solve_part2(data):
    nodes = get_nodes(data)

    def get_value(node):
        if not node["children"]:
            return sum(node["metadata"])
        value = 0
        for i in node["metadata"]:
            if 1 <= i <= len(node["children"]):
                value += get_value(node["children"][i - 1])
        return value

    answer = get_value(nodes)
    print(f"\nPart 2: {answer}")


def get_nodes(data):
    numbers = deque(map(int, data[0].split()))
    nodes = [] # store all parsed nodes
    stack = [] # keeps track of nodes being built

    # Each element on stack: [remaining_children, num_metadata, children, metadata]
    while numbers:
        # If starting a new node
        if not stack or stack[-1][0] > 0:
            n_children = numbers.popleft()
            n_metadata = numbers.popleft()
            stack.append([n_children, n_metadata, [], []])
        else:
            # Read metadata
            n_children, n_metadata, children, metadata = stack.pop()
            metadata = [numbers.popleft() for _ in range(n_metadata)]
            node = {"children": children, "metadata": metadata}
            nodes.append(node)
        
            if stack:
                stack[-1][0] -= 1
                stack[-1][2].append(node) # Add this child to the parent node
    
    return nodes[-1] # Only return the root node (which has all other nodes)


def main():
    with open("./input.txt", "r") as f:
        data = [line.strip() for line in f]

    helpers.time_it(solve_part1, data)
    helpers.time_it(solve_part2, data)


if __name__ == "__main__":
    main()