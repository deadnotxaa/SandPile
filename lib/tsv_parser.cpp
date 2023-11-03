#include "tsv_parser.h"

std::ifstream OpenFile(std::string& file_name) {
    std::ifstream file(file_name, std::ios_base::binary);

    if (!file.good()) {
        std::cout << "err\n";
        exit(1);
    }

    return file;
}

Coordinates GetMinimalSquare() {

}
