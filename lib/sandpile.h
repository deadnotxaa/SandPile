#pragma once

#include <cinttypes>
#include <limits>
#include <iostream>

struct SandPile {
    uint64_t **matrix{};

    int16_t height = 0;
    int16_t width = 0;

    int16_t width_alignment = 0;
    int16_t height_alignment = 0;

    SandPile(int16_t, int16_t, int16_t, int16_t);
    SandPile() = default;
};

enum Direction {
    kUp,
    kDown,
    kLeft,
    kRight
};

void PrintModel(const SandPile&);

bool Destruction(SandPile&, uint64_t, uint64_t);

void Resize(SandPile&, SandPile&, Direction);
