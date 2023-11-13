#include "parser.h"

Arguments Parse(int argc, char** argv) {
    Arguments args;
    std::string argument;

    for (int i = 1; i < argc; ++i) {
        argument = argv[i];

        if (std::strcmp("--help", argv[i]) == 0 || std::strcmp("-h", argv[i]) == 0) {
            HelpMessage();
        }

        if (std::strcmp("-i", argv[i - 1]) == 0) {
            args.file_name = argv[i];
        } else if (std::strcmp("-o", argv[i - 1]) == 0) {
            args.image_directory_path = argv[i];
        } else if (std::strcmp("-m", argv[i - 1]) == 0) {
            args.max_model_iterations = FromChar(argv[i]);
        } else if (std::strcmp("-f", argv[i - 1]) == 0) {
            args.image_save_frequency = FromChar(argv[i]);

        } else if (argument.substr(0, 7) == "--input") {
            args.file_name = argument.substr(8);
        } else if (argument.substr(0, 8) == "--output") {
            args.image_directory_path = argument.substr(9);
        } else if (argument.substr(0, 10) == "--max-iter") {
            args.max_model_iterations = FromChar(argument.substr(11));
        } else if (argument.substr(0, 6) == "--freq") {
            args.image_save_frequency = FromChar(argument.substr(7));
        }
    }

    return args;
}

uint64_t FromChar(char* argument) {
    char* p_end{};
    return std::strtol(argument, &p_end, 10);
}

uint64_t FromChar(const std::string& argument) {
    return std::stoll(argument);
}

void AddAllGrains(SandPile* sand_pile, std::string& file_name) {
    std::ifstream file(file_name, std::ios_base::binary);

    int16_t x;
    int16_t y;
    uint64_t value;

    while (file >> x >> y >> value) {
        sand_pile->matrix[x + sand_pile->height_alignment][y + sand_pile->width_alignment] = value;
    }

    file.close();
}

Coordinates GetMinimalSquare(std::string& file_name) {
    std::ifstream file(file_name, std::ios_base::binary);

    if (!file.good()) {
        ErrorHandler(kWrongFilename);
    }

    Coordinates max_coordinates = Coordinates::GetMinCoordinates();
    Coordinates min_coordinates = Coordinates::GetMaxCoordinates();

    int16_t x;
    int16_t y;
    uint64_t value;

    while (file >> x >> y >> value) {
        if (x > max_coordinates.x) {
            max_coordinates.x = x;
        }
        if (x < min_coordinates.x) {
            min_coordinates.x = x;
        }
        if (y > max_coordinates.y) {
            max_coordinates.y = y;
        }
        if (y < min_coordinates.y) {
            min_coordinates.y = y;
        }
    }

    file.close();

    return Coordinates{
            static_cast<int16_t>(max_coordinates.x - min_coordinates.x + 1),
            static_cast<int16_t>(max_coordinates.y - min_coordinates.y + 1),
            static_cast<int16_t>(-min_coordinates.x),
            static_cast<int16_t>(-min_coordinates.y)
    };
}

void ErrorHandler(Error error) {
    switch (error) {
        case kWrongFilename:
            std::cerr << "Wrong filename!\n";
            exit(0b01);
        default:
            std::cerr << "Unhandled error\n";
            exit(0b10);
    }
}

void HelpMessage() {
    std::cout << "h\n";
}
