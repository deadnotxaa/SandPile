#include "lib/parser.h"
#include "lib/sandpile.h"
#include "lib/bmp.h"

int main(int argc, char **argv) {
    Arguments args;
    args = Parse(argc, argv);

    // Finds minimal rectangle to store Sand Pile
    Coordinates min_rectangle = GetMinimalSquare(args.file_name);

    auto *model = new SandPile(
            min_rectangle.y,
            min_rectangle.x,
            min_rectangle.width_alignment,
            min_rectangle.height_alignment
    );

    // Reads .tsv and place all grains
    AddAllGrains(model, args.file_name);

    // Imitates destruction of Sand Pile and creates .bmp
    uint64_t iteration_number = 0;

    uint16_t file_number = 0;
    while (!Destruction(*model, args.max_model_iterations, args.image_save_frequency, iteration_number)) {
        BMP *image = new BMP(*model);
        image->WriteFile(*model, file_number++, args.image_directory_path);
        if (iteration_number >= args.max_model_iterations) {
            break;
        }
    }

    return 0;
}
