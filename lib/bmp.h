#pragma once

#include "sandpile.h"
#include <fstream>
#include <array>

struct BMP {
    static const uint8_t kHeaderSize = 14;
    static const uint8_t kInfoHeaderSize = 56;
    unsigned char file_header[kHeaderSize]{};
    unsigned char file_info_header[kInfoHeaderSize]{};

    uint16_t width;
    uint16_t height;


    explicit BMP(SandPile&);
    void WriteFile(const SandPile&);
};

void GetColor(uint64_t, unsigned char*);
