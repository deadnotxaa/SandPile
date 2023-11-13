#pragma once

#include "sandpile.h"
#include <string_view>
#include <cinttypes>
#include <cstring>
#include <iostream>
#include <limits>
#include <fstream>


struct Arguments {
    std::string file_name;
    std::string image_directory_path = "./";
    uint64_t max_model_iterations = std::numeric_limits<uint64_t>::max();
    uint64_t image_save_frequency = 0;
};

struct Coordinates {
    int16_t x = 0;
    int16_t y = 0;

    int16_t width_alignment = 0;
    int16_t height_alignment = 0;

    static Coordinates GetMaxCoordinates() {
        return Coordinates{
                std::numeric_limits<int16_t>::max(),
                std::numeric_limits<int16_t>::max()
        };
    }

    static Coordinates GetMinCoordinates() {
        return Coordinates{
                std::numeric_limits<int16_t>::min(),
                std::numeric_limits<int16_t>::min()
        };
    }

};

enum Error {
    kWrongFilename
};

Arguments Parse(int, char **);

uint64_t FromChar(char *);

uint64_t FromChar(const std::string &);

Coordinates GetMinimalSquare(std::string &);

void AddAllGrains(SandPile *, std::string &);

void ErrorHandler(Error);

void HelpMessage();
