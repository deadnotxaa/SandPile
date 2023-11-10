#pragma once

#include <cinttypes>
#include <limits>
#include <iostream>

struct SandPile {
    uint64_t **pile_model_board{};
    int16_t height = 0;
    int16_t width = 0;
    int16_t width_alignment = 0;
    int16_t height_alignment = 0;

    SandPile(int16_t model_height, int16_t model_width, int16_t width_al, int16_t height_al) {
        height = model_height;
        width = model_width;

        width_alignment = width_al;
        height_alignment = height_al;

        pile_model_board = new uint64_t *[height]{};

        for (int i = 0; i < height; ++i) {
            pile_model_board[i] = new uint64_t[width]{};
        }

        std::cout << "Created Sand Pile " << height << 'x' << width << '\n';
    }

    SandPile() = default;

};

enum Direction {
    kUp,
    kDown,
    kLeft,
    kRight
};

void PrintModel(const SandPile&);

void Destruction(SandPile&, uint64_t);

void Resize(SandPile&, SandPile&, Direction);
