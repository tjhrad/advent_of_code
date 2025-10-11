#!/usr/bin/env python3

import helpers


# Direction mappings
TURN_LEFT = {">":"^", "<":"v", "^":"<", "v":">"}
TURN_RIGHT = {">":"v", "<":"^", "^":">", "v":"<"}
DIRECTIONS = {">":(1, 0), "<":(-1, 0), "^":(0, -1), "v":(0, 1)}


def solve_part1(data):
    _, collision_locations = run_simulation(data, stop_after_first_collision=True)
    answer = f"{collision_locations[0][0]},{collision_locations[0][1]}"
    print(f"\nPart 1: {answer}")   


def solve_part2(data):
    pos_final_cart, collision_locations = run_simulation(data)
    answer = f"{pos_final_cart[0]},{pos_final_cart[1]}"
    print(f"\nPart 2: {answer}")


def run_simulation(data, stop_after_first_collision=False):
    carts, track = get_carts_and_track(data)
    collision_locations = []

    while len(carts) > 1:
        carts.sort(key=lambda tup: (tup[1], tup[0]))

        collisions = set()
        positions = {(c[0], c[1]):i for i, c in enumerate(carts)}
        new_carts = []
        for i, (x_pos, y_pos, direction, turn) in enumerate(carts):

            if (x_pos, y_pos) in collisions:
                continue
            
            positions.pop((x_pos, y_pos), None)

            # Move cart
            dx, dy = DIRECTIONS[direction]
            new_pos = (x_pos + dx, y_pos + dy)
            new_direction = direction
            new_turn = turn

            if new_pos not in track:
                raise Exception(f"Cart moved off track at {new_pos}: {n_loops}")

            if track[new_pos] == "+":
                if turn == 0:  # left
                    new_direction = TURN_LEFT[direction]
                elif turn == 2:  # right
                    new_direction = TURN_RIGHT[direction]
                new_turn = (new_turn + 1) % 3
            elif track[new_pos] == "\\":
                if direction in "^v":
                    new_direction = TURN_LEFT[direction]
                else:
                    new_direction = TURN_RIGHT[direction]
            elif track[new_pos] == "/":
                if direction in "^v":
                    new_direction = TURN_RIGHT[direction]
                else:
                    new_direction = TURN_LEFT[direction]

            # Check collision
            if new_pos in positions:
                collision_locations.append(new_pos)
                collisions.add(new_pos)
                collisions.add((x_pos, y_pos))
                positions.pop(new_pos, None)
                if stop_after_first_collision:
                    return new_pos, collision_locations
                continue
            else:
                positions[new_pos] = i
                new_carts.append([new_pos[0], new_pos[1], new_direction, new_turn])
            
        # After all carts moved, keep only non-collided ones
        carts = [c for c in new_carts if (c[0], c[1]) not in collisions]

    # If only one cart remains
    return carts[0][:2], collision_locations


def get_carts_and_track(data):
    track = {}
    carts = []

    for y, row in enumerate(data):
        for x, cell in enumerate(row):
            if cell in "><":
                # Add cart with next-turn counter = 0
                carts.append([x, y, cell, 0])
                # Preserve underlying horizontal track
                track[(x, y)] = "-"
            elif cell in "^v":
                carts.append([x, y, cell, 0])
                # Preserve underlying vertical track
                track[(x, y)] = "|"
            elif cell in "-|/\\+":
                # Keep curves and intersections as-is
                track[(x, y)] = cell
            # spaces are ignored
    return carts, track


def main():
    with open("./input.txt", "r") as f:
        data = [line.rstrip('\n') for line in f]

    helpers.time_it(solve_part1, data)
    helpers.time_it(solve_part2, data)


if __name__ == "__main__":
    main()