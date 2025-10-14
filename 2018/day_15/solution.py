#!/usr/bin/env python3

from collections import deque
import copy
import helpers


def part_1(data):
    units, grid = parse_units_and_grid(data)
    answer, _, _ = simulate_battle(grid, copy.deepcopy(units))
    print(f"\nPart 1: {answer}")   


def part_2(data):
    units, grid = parse_units_and_grid(data)
    attack_power = 3

    while True:
        answer, winner, elf_died = simulate_battle(grid, copy.deepcopy(units), elf_attack=attack_power)
        if winner == "E" and not elf_died:
            break
        attack_power += 1

    print(f"\nPart 2: {answer}")


def simulate_battle(grid, units, elf_attack=3):
    n_rounds = 0
    battle_over = False
    initial_elfs = sum(1 for u in units if u[2] == "E")

    while not battle_over:
        units.sort(key=lambda u: (u[1], u[0]))  

        for i, current_unit in enumerate(units):
            # Skip unit if dead
            if current_unit[3] <= 0:
                continue

            DIRECTIONS = [(0, -1), (-1, 0), (1, 0), (0, 1)]

            # --- ATTACK PHASE FIRST ---
            adjacent_cells = [(current_unit[0] + dx, current_unit[1] + dy) for dx, dy in DIRECTIONS]
            in_range_units = [
                idx for idx, u in enumerate(units)
                if (u[0], u[1]) in adjacent_cells and u[3] > 0 and u[2] != current_unit[2]
            ]

            if in_range_units:
                # choose lowest HP, then reading order
                least_health = min(units[idx][3] for idx in in_range_units)
                candidates = [idx for idx in in_range_units if units[idx][3] == least_health]
                candidates.sort(key=lambda idx: (units[idx][1], units[idx][0]))
                target_idx = candidates[0]
                if current_unit[2] == "E":
                    units[target_idx][3] -= elf_attack
                else:
                    units[target_idx][3] -= 3
                # If battle ended mid-round
                if len(set(u[2] for u in units if u[3] > 0)) == 1:
                    battle_over = True
                    break
                continue  # attack complete, proceed to next unit


            # --- MOVE PHASE ---
            def in_bounds(x, y):
                return 0 <= y < len(grid) and 0 <= x < len(grid[0])

            target_squares = set()
            for tx, ty, ttype, thp in units:
                if thp <= 0 or ttype == current_unit[2]:
                    continue
                for dx, dy in DIRECTIONS:
                    nx, ny = tx + dx, ty + dy
                    if in_bounds(nx, ny) and grid[ny][nx] == "." and (nx, ny) not in {(u[0], u[1]) for u in units if u[3] > 0}:
                        target_squares.add((nx, ny))

            
            paths = []
            for tpos in target_squares:
                path = find_path_bfs(grid, units, (current_unit[0], current_unit[1]), tpos)
                if path:
                    paths.append(path)
            
            if paths:
                def reading_order(pos):
                    return (pos[1], pos[0])

                min_path = min(len(p) for p in paths)
                paths = [p for p in paths if len(p) == min_path and p is not None]
                paths.sort(key=lambda p: (p[-1][1], p[-1][0], p[0][1], p[0][0]))
                next_pos = paths[0][0]
                units[i][0], units[i][1] = next_pos


            # --- ATTACK PHASE ---
            adjacent_cells = [(units[i][0] + dx, units[i][1] + dy) for dx, dy in DIRECTIONS]
            in_range_units = [
                idx for idx, u in enumerate(units)
                if (u[0], u[1]) in adjacent_cells and u[3] > 0 and u[2] != current_unit[2]
            ]

            if in_range_units:
                # choose lowest HP, then reading order
                least_health = min(units[idx][3] for idx in in_range_units)
                candidates = [idx for idx in in_range_units if units[idx][3] == least_health]
                candidates.sort(key=lambda idx: (units[idx][1], units[idx][0]))
                target_idx = candidates[0]
                if current_unit[2] == "E":
                    units[target_idx][3] -= elf_attack
                else:
                    units[target_idx][3] -= 3
                # If battle ended mid-round
                if len(set(u[2] for u in units if u[3] > 0)) == 1:
                    battle_over = True
                    break
        
        # remove dead units
        units[:] = [u for u in units if u[3] > 0]

        if not battle_over:
            n_rounds += 1

    winner = next(u[2] for u in units if u[3] > 0)
    elf_died = sum(1 for u in units if u[2] == "E") < initial_elfs
    return sum([u[3] for u in units]) * n_rounds, winner, elf_died


def parse_units_and_grid(data):
    units = [] # [x, y, type, hp]
    grid = [list(line) for line in data]
    for y, row in enumerate(data):
        for x, c in enumerate(row):
            if c in "EG":
                grid[y][x] = "."
                units.append([x, y, c, 200])
    return units, grid


def find_path_bfs(grid, units, start_pos, end_pos):
    # Define directions Up, Left, Right, Down
    DIRECTIONS = [(0, -1), (-1, 0), (1, 0), (0, 1)]
    
    visited = {start_pos}
    queue = deque([(start_pos, [])])

    occupied = {(u[0], u[1]) for u in units if u[3] > 0 and (u[0], u[1]) not in (start_pos, end_pos)}

    while queue:
        pos, path = queue.popleft()

        if pos == end_pos:
            return path if path else None

        for dx, dy in DIRECTIONS:
            new_pos = (pos[0] + dx, pos[1] + dy)
            # Bounds check
            if not (0 <= new_pos[0] < len(grid[0]) and 0 <= new_pos[1] < len(grid)):
                continue
            
            # Skip walls and occupied squares
            if grid[new_pos[1]][new_pos[0]] != '.':
                continue

            if new_pos in occupied:
                continue
            
            if new_pos not in visited:
                visited.add(new_pos)
                queue.append((new_pos, path + [new_pos]))

    return None


def print_grid(grid, units):
    # For Debugging only

    # Add units
    for u in units:
        grid[u[1]][u[0]] = u[2]

    for row in grid:
        print("".join(list(row)))
    
    # Remove units
    for u in units:
        grid[u[1]][u[0]] = "."


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]

helpers.time_it(part_1, data)
helpers.time_it(part_2, data)