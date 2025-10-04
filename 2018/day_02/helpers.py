#!/usr/bin/env python3

import time


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

