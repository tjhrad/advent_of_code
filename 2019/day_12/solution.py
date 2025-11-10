#!/usr/bin/env python3

import helpers
import math


def part1(data):
    moon_positions = []
    moon_velocities = []

    for line in data:
        moon_positions.append([int(n) for n in line.replace("<x=", "").replace("y=", "").replace("z=", "").replace(">", "").split(", ")])
        moon_velocities.append([0, 0, 0])

    for _ in range(1000):
        step(moon_positions, moon_velocities)
        
    answer = 0
    for i, moon1 in enumerate(moon_positions):
         answer += sum([abs(x) for x in moon_positions[i]]) * sum([abs(x) for x in moon_velocities[i]])

    print(f"\nPart 1: {answer}")


def part2(data):
    moon_positions = []
    moon_velocities = []

    for line in data:
        moon_positions.append([int(n) for n in line.replace("<x=", "").replace("y=", "").replace("z=", "").replace(">", "").split(", ")])
        moon_velocities.append([0, 0, 0])

    xseen, yseen, zseen = set(), set(), set()
    xcycle = ycycle = zcycle = None

    xseen.add(tuple((moon_positions[i][0], moon_velocities[i][0]) for i in range(len(moon_positions))))
    yseen.add(tuple((moon_positions[i][1], moon_velocities[i][1]) for i in range(len(moon_positions))))
    zseen.add(tuple((moon_positions[i][2], moon_velocities[i][2]) for i in range(len(moon_positions))))

    n_steps = 0
    while True:
        n_steps += 1
        step(moon_positions, moon_velocities)
        
        xkey = tuple((moon_positions[i][0], moon_velocities[i][0]) for i in range(len(moon_positions)))
        ykey = tuple((moon_positions[i][1], moon_velocities[i][1]) for i in range(len(moon_positions)))
        zkey = tuple((moon_positions[i][2], moon_velocities[i][2]) for i in range(len(moon_positions)))


        if xcycle is None:
            if xkey in xseen:
                xcycle = n_steps
            xseen.add(xkey)

        if ycycle is None:
            if ykey in yseen:
                ycycle = n_steps
            yseen.add(ykey)

        if zcycle is None:
            if zkey in zseen:
                zcycle = n_steps
            zseen.add(zkey)
           
        if xcycle and ycycle and zcycle:
            break

    answer = math.lcm(xcycle, ycycle, zcycle)

    print(f"\nPart 2: {answer}")


def step(moon_positions, moon_velocities):
    for i, pos1 in enumerate(moon_positions):
        for i2, pos2 in enumerate(moon_positions):
            if i == i2:
                continue

            if pos1[0] > pos2[0]:
                moon_velocities[i][0] -= 1
            elif pos1[0] < pos2[0]:
                moon_velocities[i][0] += 1

            if pos1[1] > pos2[1]:
                moon_velocities[i][1] -= 1
            elif pos1[1] < pos2[1]:
                moon_velocities[i][1] += 1

            if pos1[2] > pos2[2]:
                moon_velocities[i][2] -= 1
            elif pos1[2] < pos2[2]:
                moon_velocities[i][2] += 1

    for i in range(len(moon_positions)):
        moon_positions[i][0] += moon_velocities[i][0]
        moon_positions[i][1] += moon_velocities[i][1]
        moon_positions[i][2] += moon_velocities[i][2]


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]


helpers.time_it(part1, data)
helpers.time_it(part2, data)
