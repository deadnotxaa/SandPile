#pragma once

#include <string_view>
#include <cinttypes>
#include <cstring>
#include <iostream>
#include <limits>

struct Arguments {
    std::string_view file_name;
    std::string_view image_directory_path = "./";
    uint64_t max_model_iterations = std::numeric_limits<uint64_t>::max();
    uint64_t image_save_frequency = 0;
};

enum Error {
    kWrongDirectoryPath,
    kWrongFilename
};

Arguments Parser(int, char**);

uint64_t FromChar(char*);

uint64_t FromChar(std::string_view);

void ErrorHandler(Error);

void HelpMessage();
