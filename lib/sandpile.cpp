#include "sandpile.h"

void PrintModel(const SandPile& pile) {
    for (int i = 0; i < pile.height; ++i) {
        for (int j = 0; j < pile.width; ++j) {
            std::cout << pile.pile_model_board[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "hxw: " << pile.height << 'x' << pile.width << '\n';
}

void Destruction(SandPile& model, uint64_t iterations) {
    SandPile model_duplicate = model;

    model_duplicate.pile_model_board = new uint64_t *[model.height];
    for (int i = 0; i < model.height; ++i) {
        model_duplicate.pile_model_board[i] = new uint64_t[model.width];
    }

    for (int i = 0; i < model.height; ++i) {
        for (int j = 0; j < model.width; ++j) {
            model_duplicate.pile_model_board[i][j] = model.pile_model_board[i][j];
        }
    }

    bool is_full_destructed = false;
    bool is_all_grains_done;

    for (int i = 0; i < iterations && !is_full_destructed; ++i) {
        if (i % 10000 == 0) {
            std::cout << i << '\n';
        }
        is_all_grains_done = true;
        for (int j = 0; j < model.height; ++j) {
            for (int k = 0; k < model.width; ++k) {
                if (model.pile_model_board[j][k] >= 4) {
                    is_all_grains_done = false;

                    if (j + 1 >= model.height) {
                        Resize(model, model_duplicate, kDown);
                        model_duplicate.pile_model_board[j + 1][k]++;
                    } else {
                        model_duplicate.pile_model_board[j + 1][k]++;
                    }

                    if (j - 1 < 0) {
                        Resize(model, model_duplicate, kUp);
                        j++;
                        model_duplicate.pile_model_board[j - 1][k]++;
                    } else {
                        model_duplicate.pile_model_board[j - 1][k]++;
                    }

                    if (k + 1 >= model.width) {
                        Resize(model, model_duplicate, kRight);
                        model_duplicate.pile_model_board[j][k + 1]++;
                    } else {
                        model_duplicate.pile_model_board[j][k + 1]++;
                    }


                    if (k - 1 < 0) {
                        Resize(model, model_duplicate, kLeft);
                        k++;
                        model_duplicate.pile_model_board[j][k - 1]++;
                    } else {
                        model_duplicate.pile_model_board[j][k - 1]++;
                    }

                    model_duplicate.pile_model_board[j][k] -= 4;
                    model.pile_model_board[j][k] -= 4;
                }
            }
        }

        if (is_all_grains_done) {
            is_full_destructed = true;
        }

        for (int j = 0; j < model.height; ++j) {
            for (int k = 0; k < model.width; ++k) {
                model.pile_model_board[j][k] = model_duplicate.pile_model_board[j][k];
            }
        }
    }
}

void Resize(SandPile& original_model, SandPile& model_duplicate, Direction direction) {
    // creating duplicate matrix for main model
    auto **new_original_model = new uint64_t*[original_model.height]{};
    for (int i = 0; i < original_model.height; ++i) {
        new_original_model[i] = new uint64_t[original_model.width]{};
    }

    // creating duplicate matrix for extra model
    auto **new_model_duplicate = new uint64_t*[model_duplicate.height]{};
    for (int i = 0; i < model_duplicate.height; ++i) {
        new_model_duplicate[i] = new uint64_t[model_duplicate.width]{};
    }

    for (int i = 0; i < original_model.height; ++i) {
        for (int j = 0; j < original_model.width; ++j) {
            new_original_model[i][j] = original_model.pile_model_board[i][j];
            new_model_duplicate[i][j] = model_duplicate.pile_model_board[i][j];
        }
    }

    for (int i = 0; i < original_model.height; ++i) {
        free(original_model.pile_model_board[i]);
        free(model_duplicate.pile_model_board[i]);
    }
    free(original_model.pile_model_board);
    free(model_duplicate.pile_model_board);

    if (direction == kUp) {
        original_model.height++;
        original_model.pile_model_board = new uint64_t * [original_model.height]{};
        for (int i = 0; i < original_model.height; ++i) {
            original_model.pile_model_board[i] = new uint64_t [original_model.width]{};
        }

        model_duplicate.height++;
        model_duplicate.pile_model_board = new uint64_t * [model_duplicate.height]{};
        for (int i = 0; i < model_duplicate.height; ++i) {
            model_duplicate.pile_model_board[i] = new uint64_t [model_duplicate.width]{};
        }

        for (int i = 0; i < original_model.height - 1; ++i) {
            for (int j = 0; j < original_model.width; ++j) {
                original_model.pile_model_board[i + 1][j] = new_original_model[i][j];
                model_duplicate.pile_model_board[i + 1][j] = new_model_duplicate[i][j];
            }
        }
    } else if (direction == kDown) {
        original_model.height++;
        original_model.pile_model_board = new uint64_t * [original_model.height]{};
        for (int i = 0; i < original_model.height; ++i) {
            original_model.pile_model_board[i] = new uint64_t [original_model.width]{};
        }

        model_duplicate.height++;
        model_duplicate.pile_model_board = new uint64_t * [model_duplicate.height]{};
        for (int i = 0; i < model_duplicate.height; ++i) {
            model_duplicate.pile_model_board[i] = new uint64_t [model_duplicate.width]{};
        }

        for (int i = 0; i < original_model.height - 1; ++i) {
            for (int j = 0; j < original_model.width; ++j) {
                original_model.pile_model_board[i][j] = new_original_model[i][j];
                model_duplicate.pile_model_board[i][j] = new_model_duplicate[i][j];
            }
        }

    } else if (direction == kLeft) {
        original_model.width++;
        original_model.pile_model_board = new uint64_t * [original_model.height]{};
        for (int i = 0; i < original_model.height; ++i) {
            original_model.pile_model_board[i] = new uint64_t [original_model.width]{};
        }

        model_duplicate.width++;
        model_duplicate.pile_model_board = new uint64_t * [model_duplicate.height]{};
        for (int i = 0; i < model_duplicate.height; ++i) {
            model_duplicate.pile_model_board[i] = new uint64_t [model_duplicate.width]{};
        }

        for (int i = 0; i < original_model.height; ++i) {
            for (int j = 0; j < original_model.width - 1; ++j) {
                original_model.pile_model_board[i][j + 1] = new_original_model[i][j];
                model_duplicate.pile_model_board[i][j + 1] = new_model_duplicate[i][j];
            }
        }

    } else if (direction == kRight) {
        original_model.width++;
        original_model.pile_model_board = new uint64_t * [original_model.height]{};
        for (int i = 0; i < original_model.height; ++i) {
            original_model.pile_model_board[i] = new uint64_t [original_model.width]{};
        }

        model_duplicate.width++;
        model_duplicate.pile_model_board = new uint64_t * [model_duplicate.height]{};
        for (int i = 0; i < model_duplicate.height; ++i) {
            model_duplicate.pile_model_board[i] = new uint64_t [model_duplicate.width]{};
        }

        for (int i = 0; i < original_model.height; ++i) {
            for (int j = 0; j < original_model.width - 1; ++j) {
                original_model.pile_model_board[i][j] = new_original_model[i][j];
                model_duplicate.pile_model_board[i][j] = new_model_duplicate[i][j];
            }
        }
    }

    for (int i = 0; i < original_model.height - 1; ++i) {
        free(new_original_model[i]);
    }

    for (int i = 0; i < model_duplicate.height - 1; ++i) {
        free(new_model_duplicate[i]);
    }

    free(new_original_model);
    free(new_model_duplicate);
}

