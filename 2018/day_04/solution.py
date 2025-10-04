#!/usr/bin/env python3

from collections import defaultdict
from datetime import datetime
import re
import helpers


def solve_part1(data):
    # --- Sort logs ---
    sorted_logs = get_logs(data)

    # --- Parse logs ---
    guards = defaultdict(lambda: [0] * 60)
    current_guard = None
    sleep_start = None

    for log in sorted_logs:
        if "Guard" in log:
            current_guard = int(re.search(r"#(\d+)", log).group(1))
        elif "asleep" in log:
            sleep_start = int(log[15:17])
        elif "up" in log:
            sleep_end = int(log[15:17])
            for minute in range(sleep_start, sleep_end):
                guards[current_guard][minute] += 1

    # --- Find guard with max sleep time ---    
    guard_id, _ = max(guards.items(), key=lambda g: sum(g[1]))
    answer = guard_id * guards[guard_id].index(max(guards[guard_id]))
    print(f"\nPart 1: {answer}")


def solve_part2(data):
    # --- Sort logs ---
    sorted_logs = get_logs(data)

    # --- Parse logs ---
    guards = defaultdict(lambda: [0] * 60)
    current_guard = None
    sleep_start = None

    for log in sorted_logs:
        if "Guard" in log:
            current_guard = int(re.search(r"#(\d+)", log).group(1))
        elif "asleep" in log:
            sleep_start = int(log[15:17])
        elif "up" in log:
            sleep_end = int(log[15:17])
            for minute in range(sleep_start, sleep_end):
                guards[current_guard][minute] += 1
    
    # --- Find guard with most frequent sleep minute ---
    guard_id, _ = max(guards.items(), key=lambda g: max(g[1]))
    answer = guard_id * guards[guard_id].index(max(guards[guard_id]))
    print(f"\nPart 2: {answer}")


def get_logs(data):
    pattern = re.compile(r"\[(.*?)\]")
    sorted_logs = sorted(
        data,
        key=lambda line: datetime.strptime(pattern.search(line).group(1), "%Y-%m-%d %H:%M")
    )
    return sorted_logs

def main():
    with open("./input.txt", "r") as f:
        data = [line.strip() for line in f]

    helpers.time_it(solve_part1, data)
    helpers.time_it(solve_part2, data)


if __name__ == "__main__":
    main()