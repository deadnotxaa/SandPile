#include "lib/parser.h"
#include "lib/sandpile.h"
#include "lib/bmp.h"

int main(int argc, char **argv) {
    Arguments args = Parse(argc, argv);

    // Finds minimal rectangle to store Sand Pile
    RectangleBorders min_rectangle = GetMinimalRectangle(args.file_name);

    // Creates minimal-sized Sand Pile
    SandPile model(
            min_rectangle.height,
            min_rectangle.width,
            min_rectangle.width_alignment,
            min_rectangle.height_alignment
    );

    // Reads .tsv and place all grains
    AddAllGrains(model, args.file_name);

    // Destruct Sand Pile and creates .bmp
    bool is_destructed;
    bool is_zero_freq = !args.image_save_frequency;
    uint16_t image_number = 0;

    for (int i = 0; i < args.max_model_iterations && !is_destructed; ++i) {
        is_destructed = Destruction(model);

        if (is_zero_freq) {
            continue;
        }
        if (i % args.image_save_frequency) {
            continue;
        }

        BMP image(model);
        image.WriteFile(model, image_number++, args.image_directory_path);
    }

    // Save the last state of Sand Pile
    BMP image(model);
    image.WriteFile(model, image_number, args.image_directory_path);

    return 0;
}
