#include "parser.h"

Arguments Parser(int argc, char** argv) {
    Arguments args;
    std::string_view argument;

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
    return 1;
}

uint64_t FromChar(std::string_view argument) {
    return 1;
}

void ErrorHandler(Error) {

}

void HelpMessage() {
    std::cout << "h\n";
}
