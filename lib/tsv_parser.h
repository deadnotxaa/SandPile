#pragma once
#include <cinttypes>
#include <fstream>
#include <string_view>
#include <iostream>

struct Coordinates {
    int16_t x;
    int16_t y;
};

std::ifstream OpenFile(std::string&);

Coordinates GetMinimalSquare();
