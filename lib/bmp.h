#pragma once

#include "sandpile.h"
#include <fstream>
#include <cstring>

struct Color {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

struct BMP {
    static const uint8_t kHeaderSize = 14;
    static const uint8_t kInfoHeaderSize = 40;
    static const uint8_t kPaletteSize = 20;

    uint8_t file_header[kHeaderSize]{};
    uint8_t file_info_header[kInfoHeaderSize]{};
    uint8_t palette[kPaletteSize]{};

    const Color kWhite = {255, 255, 255};
    const Color kGreen = {10, 85, 70};
    const Color kYellow = {5, 170, 255};
    const Color kPurple = {160, 90,140};
    const Color kBlack = {0, 0,0};

    uint16_t width;
    uint16_t height;

    void CreatePalette();
    explicit BMP(const SandPile&);
    void WriteFile(const SandPile&, uint16_t, const std::string&);
    static std::string CreateFilename(uint16_t, const std::string&);
    static uint8_t GetColor(uint64_t, uint64_t);
};
