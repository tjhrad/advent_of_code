#!/usr/bin/env python3

import helpers
import re
import copy


def part_1(data):
    groups = parse_data(data)
    answer, _ = simulate_battle(groups)
    print(f"\nPart 1: {answer}")


def part_2(data):
    boost = 0
    while True:
        groups = parse_data(data, boost)
        answer, winner = simulate_battle(groups)
        if winner == 0:
            break
        else:
            boost += 1

    print(f"\nPart 2: {answer}")


def simulate_battle(groups):
    while True:
        # Remove dead groups and recompute effective power
        groups = [g for g in groups if g[2] > 0]

        # Reset each effective power.
        for g in groups:
            g[1] = g[2] * g[4]

        # End if only one type remains
        if len(set(g[0] for g in groups)) <= 1:
            break

        # TARGET SELECTION PHASE
        groups.sort(key=lambda x: (-x[1], -x[6]))  # by effective power, then initiative
        targeted = set()
        new_groups = []

        for g in groups:
            group_type, ep, n_units, hp, ap, at, initiative, weakness, immunity, target = g

            if n_units <= 0:
                new_groups.append([group_type, n_units * ap, n_units, hp, ap, at, initiative, weakness, immunity, None])
                continue

            max_damage = 0
            target_index = None

            for i, t in enumerate(groups):
                if g == t:
                    continue

                t_group_type, t_ep, t_n_units, t_hp, t_ap, t_at, t_initiative, t_weakness, t_immunity, t_next_target = t

                # Skip allies, dead, or already-targeted
                if t_n_units <= 0 or group_type == t_group_type or i in targeted:
                    continue

                # Compute damage (considering immunities/weaknesses)
                if at in t_immunity:
                    continue

                damage = n_units * ap
                if at in t_weakness:
                    damage *= 2

                if damage == 0:
                    continue

                # Tie-breaking rules
                if (damage > max_damage or
                    (damage == max_damage and t_ep > groups[target_index][1]) or
                    (damage == max_damage and t_ep == groups[target_index][1] and t_initiative > groups[target_index][6])):
                    max_damage = damage
                    target_index = i

            if target_index is not None:
                targeted.add(target_index)

            new_groups.append([group_type, n_units * ap, n_units, hp, ap, at, initiative, weakness, immunity, target_index])

        groups = copy.deepcopy(new_groups)

        # ATTACK PHASE
        attack_order = sorted(enumerate(groups), key=lambda x: -x[1][6])
        new_groups = copy.deepcopy(groups)
        total_units_killed = 0

        for i, g in attack_order:
            group_type, ep, n_units, hp, ap, at, initiative, weakness, immunity, target = g

            if n_units <= 0 or target is None:
                continue

            t_group_type, t_ep, t_n_units, t_hp, t_ap, t_at, t_initiative, t_weakness, t_immunity, t_next_target = new_groups[target]
            if t_n_units <= 0:
                continue

            # Compute damage
            # Use 'new_groups' because n_units can change mid-battle
            damage = new_groups[i][2] * new_groups[i][4] # n_units * ap
            if at in t_immunity:
                damage = 0
            elif at in t_weakness:
                damage *= 2

            # Units killed (cannot exceed remaining units)
            units_killed = min(damage // t_hp, t_n_units)
            total_units_killed += units_killed

            remaining_units = t_n_units - units_killed
            new_groups[target][2] = remaining_units
            new_groups[target][1] = remaining_units * new_groups[target][4]

        groups = new_groups

        # Stalemate check (no one died this round)
        if total_units_killed == 0:
            print("Stalemate detected.")
            break

    # Final count
    return sum(g[2] for g in groups if g[2] > 0), max(list(set([g[0] for g in groups if g[2] > 0])))


def parse_data(data, boost = None):
    groups = []
    group_type = 0  # 0 = Immune System, 1 = Infection

    for line in data:
        if "Infection" in line:
            group_type = 1
            continue

        if ":" in line or not line.strip():
            continue

        # Extract optional weaknesses/immunities
        m = re.search(r'\((.*?)\)', line)
        immunities_and_weaknesses = m.group(1) if m else ""
        if m:
            line = line.replace(f"({immunities_and_weaknesses})", "")

        parts = line.split()
        n_units = int(parts[0])
        hp = int(parts[4])
        attack_power = int(parts[-6])
        attack_type = parts[-5]
        initiative = int(parts[-1])

        weaknesses = []
        immunities = []

        if immunities_and_weaknesses:
            for item in immunities_and_weaknesses.split(";"):
                item = item.strip()
                if item.startswith("weak to"):
                    weaknesses.extend([w.strip() for w in item.replace("weak to ", "").split(",")])
                elif item.startswith("immune to"):
                    immunities.extend([i.strip() for i in item.replace("immune to ", "").split(",")])

        ep = n_units * attack_power
        # type, ep, n_units, hp, ap, at, initiative, weakness, immunity, target
        if group_type == 0 and boost is not None:
            groups.append([group_type, ep, n_units, hp, attack_power + boost, attack_type, initiative, weaknesses, immunities, None])
        else:
            groups.append([group_type, ep, n_units, hp, attack_power, attack_type, initiative, weaknesses, immunities, None])

    return groups


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]

helpers.time_it(part_1, data)
helpers.time_it(part_2, data)
