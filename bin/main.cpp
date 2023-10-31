#include <lib/parser.h>
#include <lib/sandpile.h>
#include <iostream>

int main(int argc, char** argv) {
    Arguments args;
    args = Parser(argc, argv);

    std::cout << "filename: " << args.file_name << "\nsave directory: " << args.image_directory_path <<
    "\nmax iterations: " << args.max_model_iterations << "\nfrequency: " << args.image_save_frequency << '\n';

    return 0;
}