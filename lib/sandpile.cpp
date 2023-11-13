#include "sandpile.h"

SandPile::SandPile(int16_t model_height, int16_t model_width, int16_t width_al, int16_t height_al) {
    height = model_height;
    width = model_width;

    width_alignment = width_al;
    height_alignment = height_al;

    matrix = new uint64_t *[height]{};

    for (int i = 0; i < height; ++i) {
        matrix[i] = new uint64_t[width]{};
    }
}

bool Destruction(SandPile& model, uint64_t iterations, uint64_t save_frequency, uint64_t& iteration_number) {
    SandPile model_duplicate = model;

    model_duplicate.matrix = new uint64_t *[model.height];
    for (int i = 0; i < model.height; ++i) {
        model_duplicate.matrix[i] = new uint64_t[model.width];
    }

    for (int i = 0; i < model.height; ++i) {
        for (int j = 0; j < model.width; ++j) {
            model_duplicate.matrix[i][j] = model.matrix[i][j];
        }
    }

    bool is_full_destructed = false;
    bool is_all_grains_done;

    for (int i = 0; i < iterations && !is_full_destructed; ++i, ++iteration_number) {
        is_all_grains_done = true;
        for (int j = 0; j < model.height; ++j) {
            for (int k = 0; k < model.width; ++k) {
                if (model.matrix[j][k] >= 4) {
                    is_all_grains_done = false;

                    if (j + 1 >= model.height) {
                        Resize(model, model_duplicate, kDown);
                        model_duplicate.matrix[j + 1][k]++;
                    } else {
                        model_duplicate.matrix[j + 1][k]++;
                    }

                    if (j - 1 < 0) {
                        Resize(model, model_duplicate, kUp);
                        j++;
                        model_duplicate.matrix[j - 1][k]++;
                    } else {
                        model_duplicate.matrix[j - 1][k]++;
                    }

                    if (k + 1 >= model.width) {
                        Resize(model, model_duplicate, kRight);
                        model_duplicate.matrix[j][k + 1]++;
                    } else {
                        model_duplicate.matrix[j][k + 1]++;
                    }


                    if (k - 1 < 0) {
                        Resize(model, model_duplicate, kLeft);
                        k++;
                        model_duplicate.matrix[j][k - 1]++;
                    } else {
                        model_duplicate.matrix[j][k - 1]++;
                    }

                    model_duplicate.matrix[j][k] -= 4;
                    model.matrix[j][k] -= 4;
                }
            }
        }

        if (is_all_grains_done) {
            is_full_destructed = true;
        }

        for (int j = 0; j < model.height; ++j) {
            for (int k = 0; k < model.width; ++k) {
                model.matrix[j][k] = model_duplicate.matrix[j][k];
            }
        }

        if (i == save_frequency && save_frequency) {
            break;
        }
    }
    return is_full_destructed;
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
            new_original_model[i][j] = original_model.matrix[i][j];
            new_model_duplicate[i][j] = model_duplicate.matrix[i][j];
        }
    }

    for (int i = 0; i < original_model.height; ++i) {
        free(original_model.matrix[i]);
        free(model_duplicate.matrix[i]);
    }
    free(original_model.matrix);
    free(model_duplicate.matrix);

    if (direction == kUp) {
        original_model.height++;
        original_model.matrix = new uint64_t * [original_model.height]{};
        for (int i = 0; i < original_model.height; ++i) {
            original_model.matrix[i] = new uint64_t [original_model.width]{};
        }

        model_duplicate.height++;
        model_duplicate.matrix = new uint64_t * [model_duplicate.height]{};
        for (int i = 0; i < model_duplicate.height; ++i) {
            model_duplicate.matrix[i] = new uint64_t [model_duplicate.width]{};
        }

        for (int i = 0; i < original_model.height - 1; ++i) {
            for (int j = 0; j < original_model.width; ++j) {
                original_model.matrix[i + 1][j] = new_original_model[i][j];
                model_duplicate.matrix[i + 1][j] = new_model_duplicate[i][j];
            }
        }
    } else if (direction == kDown) {
        original_model.height++;
        original_model.matrix = new uint64_t * [original_model.height]{};
        for (int i = 0; i < original_model.height; ++i) {
            original_model.matrix[i] = new uint64_t [original_model.width]{};
        }

        model_duplicate.height++;
        model_duplicate.matrix = new uint64_t * [model_duplicate.height]{};
        for (int i = 0; i < model_duplicate.height; ++i) {
            model_duplicate.matrix[i] = new uint64_t [model_duplicate.width]{};
        }

        for (int i = 0; i < original_model.height - 1; ++i) {
            for (int j = 0; j < original_model.width; ++j) {
                original_model.matrix[i][j] = new_original_model[i][j];
                model_duplicate.matrix[i][j] = new_model_duplicate[i][j];
            }
        }

    } else if (direction == kLeft) {
        original_model.width++;
        original_model.matrix = new uint64_t * [original_model.height]{};
        for (int i = 0; i < original_model.height; ++i) {
            original_model.matrix[i] = new uint64_t [original_model.width]{};
        }

        model_duplicate.width++;
        model_duplicate.matrix = new uint64_t * [model_duplicate.height]{};
        for (int i = 0; i < model_duplicate.height; ++i) {
            model_duplicate.matrix[i] = new uint64_t [model_duplicate.width]{};
        }

        for (int i = 0; i < original_model.height; ++i) {
            for (int j = 0; j < original_model.width - 1; ++j) {
                original_model.matrix[i][j + 1] = new_original_model[i][j];
                model_duplicate.matrix[i][j + 1] = new_model_duplicate[i][j];
            }
        }

    } else if (direction == kRight) {
        original_model.width++;
        original_model.matrix = new uint64_t * [original_model.height]{};
        for (int i = 0; i < original_model.height; ++i) {
            original_model.matrix[i] = new uint64_t [original_model.width]{};
        }

        model_duplicate.width++;
        model_duplicate.matrix = new uint64_t * [model_duplicate.height]{};
        for (int i = 0; i < model_duplicate.height; ++i) {
            model_duplicate.matrix[i] = new uint64_t [model_duplicate.width]{};
        }

        for (int i = 0; i < original_model.height; ++i) {
            for (int j = 0; j < original_model.width - 1; ++j) {
                original_model.matrix[i][j] = new_original_model[i][j];
                model_duplicate.matrix[i][j] = new_model_duplicate[i][j];
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
