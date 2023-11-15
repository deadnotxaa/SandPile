#include "bmp.h"

BMP::BMP(const SandPile &model) {
    if (model.width % 4 == 0) {
        width = model.width;
    } else {
        width = model.width + (4 - model.width % 4);
    }
    height = model.height;

    // Creation of palette
    CreatePalette();

    uint64_t size = kHeaderSize + kInfoHeaderSize + kPaletteSize + (width / 2) * height;

    // Bitmap File Header
    // BMP signature
    file_header[0] = 'B';
    file_header[1] = 'M';

    // Full size of BMP in bytes
    file_header[2] = size & 0xFF;
    file_header[3] = (size >> 8) & 0xFF;
    file_header[4] = (size >> 16) & 0xFF;
    file_header[5] = (size >> 24) & 0xFF;

    // Reserved fields (6-9 bytes, not specified)

    // Data offset
    file_header[10] = kHeaderSize + kInfoHeaderSize + kPaletteSize;
    file_header[11] = 0;
    file_header[12] = 0;
    file_header[13] = 0;

    // Bitmap Information Header
    // Size of Header
    file_info_header[0] = kInfoHeaderSize;
    file_info_header[1] = 0;
    file_info_header[2] = 0;
    file_info_header[3] = 0;

    // Width of image in pixels
    file_info_header[4] = width & 0xFF;
    file_info_header[5] = (width >> 8) & 0xFF;
    file_info_header[6] = (width >> 16) & 0xFF;
    file_info_header[7] = (width >> 24) & 0xFF;

    // Height of image in pixels
    file_info_header[8] = height & 0xFF;
    file_info_header[9] = (height >> 8) & 0xFF;
    file_info_header[10] = (height >> 16) & 0xFF;
    file_info_header[11] = (height >> 24) & 0xFF;

    // Planes
    file_info_header[12] = 1;
    file_info_header[13] = 0;

    // Bits per pixel
    file_info_header[14] = 4;
    file_info_header[15] = 0;

    // Number of colors
    file_info_header[32] = 5;

    // Other is not specified
}

void BMP::WriteFile(const SandPile& model, uint16_t image_number, const std::string& path) {
    std::ofstream file(CreateFilename(image_number, path), std::fstream::out | std::fstream::binary);

    file.write(reinterpret_cast<char*>(file_header), kHeaderSize);
    file.write(reinterpret_cast<char*>(file_info_header), kInfoHeaderSize);
    file.write(reinterpret_cast<char*>(palette), kPaletteSize);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j += 2) {
            uint8_t color = 0;

            if (i < model.height && j + 1 < model.width) {
                color = GetColor(model.matrix[i][j], model.matrix[i][j]);
            }

            file << color;
        }
    }
}

void BMP::CreatePalette() {
    palette[0] = kWhite.blue;
    palette[1] = kWhite.green;
    palette[2] = kWhite.red;
    palette[3] = 0;

    palette[4] = kGreen.blue;
    palette[5] = kGreen.green;
    palette[6] = kGreen.red;
    palette[7] = 0;

    palette[8] = kYellow.blue;
    palette[9] = kYellow.green;
    palette[10] = kYellow.red;
    palette[11] = 0;

    palette[12] = kPurple.blue;
    palette[13] = kPurple.green;
    palette[14] = kPurple.red;
    palette[15] = 0;

    palette[16] = kBlack.blue;
    palette[17] = kBlack.green;
    palette[18] = kBlack.red;
    palette[19] = 0;
}

std::string BMP::CreateFilename(uint16_t image_number, const std::string& path) {
    return path + "image" + std::to_string(image_number) + ".bmp";
}

uint8_t BMP::GetColor(uint64_t first_value, uint64_t second_value) {
    uint8_t result;

    if (first_value > 3) {
        result = 4;
    } else {
        result = first_value;
    }

    result = (result << 4);

    if (second_value > 3) {
        result += 4;
    } else {
        result += second_value;
    }

    return result;
}
