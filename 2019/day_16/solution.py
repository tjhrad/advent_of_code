#!/usr/bin/env python3

import helpers


def part1(data):
    signal = [int(n) for n in data[0]]
    output_list = fft(signal, 100)
    answer = ''.join(str(n) for n in output_list[:8])
    print(f"\nPart 1: {answer}")


def part2(data):
    signal = [int(n) for n in data[0]]
    offset = int(''.join(str(x) for x in signal[:7]))

    assert offset > len(signal) * 10_000 // 2

    signal = (signal * 10_000)[offset:]

    for _ in range(100):
        for i in range(len(signal) - 2, -1, -1):
            signal[i] = (signal[i] + signal[i+1]) % 10

    answer = ''.join(str(n) for n in signal[:8])
    print(f"\nPart 2: {answer}")


def fft(signal, n_phases):
    base_pattern = [0, 1, 0, -1]
    next_signal = []
    
    for _ in range(n_phases):
        base_idx = 0
        base_count = 1
        next_signal = []
        for i, n in enumerate(signal):
            next_number = 0
            
            for n2 in signal:
                if base_count >= i:
                    base_count = 0
                    base_idx = (base_idx + 1) % 4
                else:
                    base_count += 1

                next_number += (n2 * base_pattern[base_idx])

            next_signal.append(abs(next_number) % 10)
            base_idx = 0
            base_count = 0

        signal = next_signal

    return signal


with open("./input.txt", "r") as f:
    data = [line.rstrip('\n') for line in f]


helpers.time_it(part1, data)
helpers.time_it(part2, data)
