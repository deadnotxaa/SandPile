#include <cinttypes>
#include <limits>

struct SandPile {
    uint64_t *pile_model_board;

    SandPile() {
        pile_model_board = new uint64_t[std::numeric_limits<uint16_t>::max()];
    }
};

void add_new_grain(const int16_t& x, const int16_t& y, const uint64_t& value);
