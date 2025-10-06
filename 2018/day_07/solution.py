#!/usr/bin/env python3

from collections import defaultdict, deque
import helpers


def solve_part1(data):
    letters = set()
    rules = defaultdict(list)
    for line in data:
        letters.update([line[5], line[36]])
        rules[line[5]].append(line[36])
    
    answer = ''.join(sort_letters(rules, letters))
    print(f"\nPart 1: {answer}")


def solve_part2(data):
    letters = set()
    rules = defaultdict(list)
    for line in data:
        letters.update([line[5], line[36]])
        rules[line[5]].append(line[36])
    
    answer = time_to_sort_letters(rules, letters, n_workers=5, base_time=60)
    print(f"\nPart 2: {answer}")


def sort_letters(graph, elements):
    # Slightly modified Khan's topological sort algo
    
    # Compute starting indegree
    indegree = {e: 0 for e in elements}
    for bigger, smaller_list in graph.items():
        for smaller in smaller_list:
            indegree[smaller] += 1

    # Initialize the queue with zero indegree elements
    queue = deque(sorted([e for e in elements if indegree[e] == 0]))

    # Process the nodes and build the result
    result = []
    while queue:
        node = queue.popleft()
        result.append(node)
        for neighbor in graph[node]:
            indegree[neighbor] -= 1
            
            if indegree[neighbor] == 0:
                queue.append(neighbor)
        queue = deque(sorted(queue)) # Re-sort queue to preserve smallest first order
    
    return result


def time_to_sort_letters(graph, elements, n_workers=5, base_time=60):
    # Compute starting indegree
    indegree = {e: 0 for e in elements}
    for bigger, smaller_list in graph.items():
        for smaller in smaller_list:
            indegree[smaller] += 1

    # Initialize the queue with zero indegree elements
    queue = deque(sorted([e for e in elements if indegree[e] == 0]))

    # Process the nodes and workers
    time = 0
    workers = []
    while queue or workers:
        while queue and len(workers) < n_workers:
            node = queue.popleft()
            duration = base_time + ord(node) - ord('A') + 1
            workers.append([node, duration])

        # Find the shortest current step
        min_time = min([w[1] for w in workers])
        time += min_time

        finished_nodes = []
        for w in workers:
            w[1] -= min_time
            if w[1] == 0:
                finished_nodes.append(w[0])

        workers = [w for w in workers if w[1] > 0]
        
        # Update indegree
        for node in finished_nodes:
            for neighbor in graph[node]:
                indegree[neighbor] -= 1
                if indegree[neighbor] == 0:
                    queue.append(neighbor)
        queue = deque(sorted(queue)) # Re-sort queue to preserve smallest first order
    
    return time


def main():
    with open("./input.txt", "r") as f:
        data = [line.strip() for line in f]

    helpers.time_it(solve_part1, data)
    helpers.time_it(solve_part2, data)


if __name__ == "__main__":
    main()