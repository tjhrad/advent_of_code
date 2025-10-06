#!/usr/bin/env python3

import time
from collections import defaultdict, deque


def time_it(func, *args, **kwargs):
    """Run a function with timing and print the elapsed time."""
    start = time.time()
    result = func(*args, **kwargs)
    elapsed = time.time() - start
    print(format_time(elapsed))
    return result


def format_time(seconds: float) -> str:
    if seconds >= 1:
        return f"{seconds:.3f} s"
    elif seconds >= 1e-3:
        return f"{seconds * 1e3:.3f} ms"
    elif seconds >= 1e-6:
        return f"{seconds * 1e6:.3f} µs"
    else:
        return f"{seconds * 1e9:.3f} ns"


def is_integer(s):
    """
    Checks if a string is an integer
    This will ignore '+' and '-'
    """
    if s[0] in ["+", "-"]:
        if s[1:].isdigit():
            return True
        return False
      
    if s.isdigit():
        return True
    return False


def manhattan_distance(point_1, point_2):
    return sum(abs(a-b) for a, b in zip(point_1, point_2))


def topological_sort(graph):
    """
    Khan's algorithm
    graph: dict where keys are nodes, values are lists of nodes they point to
    Returns: a list of nodes in topologically sorted order
    """
    # Compute indegree of each node
    indegree = {node: 0 for node in graph}
    for node in graph:
        for neighbor in graph[node]:
            indegree[neighbor] += 1

    # Initialize queue with nodes that have indegree 0
    queue = deque([node for node in graph if indegree[node] == 0])
    result = []

    # Process nodes
    while queue:
        node = queue.popleft()
        result.append(node)
        for neighbor in graph[node]:
            indegree[neighbor] -= 1
            if indegree[neighbor] == 0:
                queue.append(neighbor)

    # Check for cycles
    if len(result) != len(graph):
        raise ValueError("Graph has a cycle! Topological sort impossible.")

    return result