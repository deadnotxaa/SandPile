#include "parser.h"

Arguments Parse(int argc, char** argv) {
    Arguments args;

    for (int i = 1; i < argc; ++i) {
        if (!std::strcmp("--help", argv[i]) || !std::strcmp("-h", argv[i])) {
            HelpMessage();
        }

        if (!std::strcmp("-i", argv[i - 1])) {
            args.file_name = argv[i];
        } else if (!std::strcmp("-o", argv[i - 1])) {
            args.image_directory_path = argv[i];
        } else if (!std::strcmp("-m", argv[i - 1])) {
            args.max_model_iterations = FromChar(argv[i]);
        } else if (!std::strcmp("-f", argv[i - 1])) {
            args.image_save_frequency = FromChar(argv[i]);

        } else if (!std::strncmp(argv[i], "--input=", std::strlen("--input="))) {
            args.file_name = argv[i] + std::strlen("--input=");
        } else if (!std::strncmp(argv[i], "--output=", std::strlen("--output="))) {
            args.image_directory_path = argv[i] + std::strlen("--output=");
        } else if (!std::strncmp(argv[i], "--max-iter=", std::strlen("--max-iter="))) {
            args.max_model_iterations = FromStr(std::string(argv[i]).substr(std::strlen("--max-iter=")));
        } else if (!std::strncmp(argv[i], "--freq=", std::strlen("--freq="))) {
            args.image_save_frequency = FromStr(std::string(argv[i]).substr(std::strlen("--freq=")));
        }
    }

    return args;
}

uint64_t FromChar(const char* argument) {
    while (argument) {
        if (*argument > '9' || *argument < '0') {
            ErrorHandler(kUnacceptableValue);
        }
        argument++;
    }

    return std::stoull(argument);
}

uint64_t FromStr(const std::string& argument) {
    if (!std::all_of(argument.begin(), argument.end(), ::isdigit)) {
        ErrorHandler(kUnacceptableValue);
    }

    return std::stoull(argument);
}

void AddAllGrains(const SandPile& sand_pile, const std::string& file_name) {
    std::ifstream file(file_name, std::ios_base::binary);

    int16_t x;
    int16_t y;
    uint64_t value;

    while (file >> x >> y >> value) {
        sand_pile.matrix[x + sand_pile.height_alignment][y + sand_pile.width_alignment] = value;
    }
}

RectangleBorders GetMinimalRectangle(const std::string& file_name) {
    std::ifstream file(file_name, std::ios_base::binary);

    if (!file.good()) {
        ErrorHandler(kWrongFilename);
    }

    RectangleBorders max_coordinates = RectangleBorders::GetMinCoordinates();
    RectangleBorders min_coordinates = RectangleBorders::GetMaxCoordinates();

    int16_t x;
    int16_t y;
    uint64_t value;

    while (file >> x >> y >> value) {
        max_coordinates.width = std::max(max_coordinates.width, x);
        min_coordinates.width = std::min(min_coordinates.width, x);
        max_coordinates.height = std::max(max_coordinates.height, y);
        min_coordinates.height = std::min(min_coordinates.height, y);
    }

    return RectangleBorders{
            static_cast<int16_t>(max_coordinates.width - min_coordinates.width + 1),
            static_cast<int16_t>(max_coordinates.height - min_coordinates.height + 1),
            static_cast<int16_t>(-min_coordinates.width),
            static_cast<int16_t>(-min_coordinates.height)
    };
}

void ErrorHandler(Error error) {
    switch (error) {
        case kWrongFilename:
            std::cerr << "Wrong filename!\n";
            break;
        case kUnacceptableValue:
            std::cerr << "Unacceptable argument value!\n";
            break;
        default:
            std::cerr << "Unhandled error!\n";
    }

    exit(EXIT_FAILURE);
}

void HelpMessage() {
    std::cout << "\n Usage:\tlabwork3-deadnotxaa.exe [Options] -i filename.tsv\n\n"
                 " Options:\n"
                 "\t-h, --help \t\t\tShows this message\n"
                 "\t-i, --input=filename.tsv\tPath to tsv-file with starting values (necessary argument)\n"
                 "\t-o, --output\t\t\tPath to directory for saving images (unnecessary argument, by default -- current directory)\n"
                 "\t-m, --max-iter=n\t\tMaximum number of model iterations (unnecessary argument, by default -- until full destruction)\n"
                 "\t-f, --frequency=n\t\tFrequency of saving images (unnecessary argument, by default -- after full destruction)\n"
                 "\n Example:\n"
                 "\tlabwork3-deadnotxaa.exe -i test.txt -o ../img -m 1000 -f 50\n\n";

    exit(0);
}
