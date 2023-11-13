#include "bmp.h"

BMP::BMP(SandPile &model) {

    if (model.width % 4 == 0) {
        width = model.width;
    } else {
        width = model.width + (4 - model.width % 4);
    }

    if (model.height % 4 == 0) {
        height = model.height;
    } else {
        height = model.height + (4 - model.height % 4);
    }

    uint64_t size = kHeaderSize + kInfoHeaderSize + width * height * 3;

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
    file_header[10] = kHeaderSize + kInfoHeaderSize;
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
    file_info_header[14] = 24;
    file_info_header[15] = 0;

    // Other is not specified
}

void BMP::WriteFile(const SandPile& model, uint16_t number, std::string& path) {
    std::fstream file;

    std::string file_name = path + "image";
    file_name.append(std::to_string(number));
    file_name.append(".bmp");

    file.open(file_name, std::fstream::out | std::fstream::binary);

    file.write(reinterpret_cast<char*>(file_header), kHeaderSize);
    file.write(reinterpret_cast<char*>(file_info_header), kInfoHeaderSize);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            unsigned char color[] = {0xFF, 0xFF, 0xFF};

            if (i < model.height && j < model.width) {
                GetColor(model.matrix[i][j], color);
            }

            file.write(reinterpret_cast<char*>(color), 3);
        }
    }
    file.close();
}

void GetColor(uint64_t value, unsigned char* color) {
    switch (value) {
        case 0:
            color[0] = 0xFF;
            color[1] = 0xFF;
            color[2] = 0xFF;
            break;
        case 1:
            color[0] = 0x00;
            color[1] = 0xFF;
            color[2] = 0x00;
            break;
        case 2:
            color[0] = 0xFF;
            color[1] = 0x00;
            color[2] = 0xFF;
            break;
        case 3:
            color[0] = 0;
            color[1] = 0xFF;
            color[2] = 0xFF;
            break;
        default:
            color[0] = 0x00;
            color[1] = 0x00;
            color[2] = 0x00;
            break;
    }
}
