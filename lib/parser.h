#pragma once

#include "sandpile.h"
#include <string>
#include <cinttypes>
#include <cstring>
#include <iostream>
#include <limits>
#include <fstream>
#include <algorithm>

struct Arguments {
    std::string file_name;
    std::string image_directory_path = "./";
    uint64_t max_model_iterations = std::numeric_limits<uint64_t>::max();
    uint64_t image_save_frequency = 0;
};

struct RectangleBorders {
    int16_t width = 0;
    int16_t height = 0;

    int16_t width_alignment = 0;
    int16_t height_alignment = 0;

    static RectangleBorders GetMaxCoordinates() {
        return RectangleBorders{
                std::numeric_limits<int16_t>::max(),
                std::numeric_limits<int16_t>::max()
        };
    }

    static RectangleBorders GetMinCoordinates() {
        return RectangleBorders{
                std::numeric_limits<int16_t>::min(),
                std::numeric_limits<int16_t>::min()
        };
    }

};

enum Error {
    kWrongFilename,
    kUnacceptableValue
};

Arguments Parse(int, char**);

uint64_t FromChar(const char*);

uint64_t FromStr(const std::string&);

RectangleBorders GetMinimalRectangle(const std::string&);

void AddAllGrains(const SandPile&, const std::string&);

void ErrorHandler(Error);

void HelpMessage();
