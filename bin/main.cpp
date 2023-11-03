#include "lib/parser.h"
#include "lib/sandpile.h"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    Arguments args;
    args = Parse(argc, argv);

    Coordinates min_square = GetMinimalSquare(args.file_name);

    auto *model = new SandPile(
            min_square.y,
            min_square.x,
            min_square.width_alignment,
            min_square.height_alignment
            );

    AddAllGrains(model, args.file_name);
    PrintModel(model);

    return 0;
}

/*std::cout << min_square.x << ' ' << min_square.y << '\n';

  std::cout << "filename: " << args.file_name << "\nsave directory: " << args.image_directory_path <<
  "\nmax iterations: " << args.max_model_iterations << "\nfrequency: " << args.image_save_frequency << '\n';*/
