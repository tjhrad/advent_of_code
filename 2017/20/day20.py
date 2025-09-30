#!/usr/bin/env python3

import time
from collections import defaultdict
import utils


def solve_part1(data):
    particles = get_particles(data)
    TIME = 1000

    for p in particles:
        p.jump_to(TIME)

    closest_particle = 100_000_000_000
    closest_distance = 100_000_000_000

    for p in particles:
        dist = p.distance_from_origin()
        if dist < closest_distance:
            closest_distance = dist
            closest_particle = p.id

    answer = closest_particle
    print(f"\nPart 1: {answer}")


def solve_part2(data):
    particles = get_particles(data)
    TIME = 100

    for _ in range(TIME):
        positions = defaultdict(list)
        for p in particles:
            p.step()
            positions[p.pos].append(p)
        
        # Remove particles that have 'collided'
        particles = [p for p in particles if len(positions[p.pos]) == 1]


    answer = len(particles)
    print(f"\nPart 2: {answer}")


def get_particles(data):
    particles = []

    id = 0
    for line in data:
        p_str, v_str, a_str = line.split(", ")
        p_str = p_str.replace("p=<","").replace(">","")
        v_str = v_str.replace("v=<","").replace(">","")
        a_str = a_str.replace("a=<","").replace(">","")

        pos = tuple([int(a) for a in p_str.split(",")])
        vel = tuple([int(a) for a in v_str.split(",")])
        acc = tuple([int(a) for a in a_str.split(",")])

        p = Particle(id, pos, vel, acc)
        particles.append(p)
        id += 1
    return particles


class Particle:
    def __init__(self, pid, pos, vel, acc):
        self.id = pid
        self.pos = pos
        self.vel = vel
        self.acc = acc

    def step(self):
        self.vel = tuple(v + a for v, a in zip(self.vel, self.acc))
        self.pos = tuple(p + v for p, v in zip(self.pos, self.vel))

    # Jump particle by a set time (t). Use to avoid simulating each step.
    def jump(self, t):
        self.pos = tuple(
            p0 + v0 * t + (a * t * (t + 1)) // 2
            for p0, v0, a in zip(self.pos, self.vel, self.acc)
        )

    # Manhattan distance
    def distance_from_origin(self):
        return sum(abs(a - b) for a, b in zip((0,0,0), self.pos))

    def __repr__(self):
        return f"Particle(ID={self.id}, pos={self.pos}, vel={self.vel}, acc={self.acc})"


def main():
    with open("./data/input.txt", "r") as f:
        data = [line.strip('\n') for line in f]

    start_time = time.time()
    solve_part1(data)
    print(utils.format_time(time.time() - start_time))

    start_time = time.time()
    solve_part2(data)
    print(utils.format_time(time.time() - start_time))


if __name__ == "__main__":
    main()
