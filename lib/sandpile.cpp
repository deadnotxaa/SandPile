#include "sandpile.h"


void PrintModel(SandPile* pile) {
    for (int i = 0; i < pile->height; ++i) {
        for (int j = 0; j < pile->width; ++j) {
            std::cout << pile->pile_model_board[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void Destruction(SandPile* model) {

}
