#include "sandpile.h"

SandPile::SandPile(int16_t model_height, int16_t model_width, int16_t model_width_alignment, int16_t model_height_alignment) {
    height = model_height;
    width = model_width;
    height_alignment = model_height_alignment;
    width_alignment = model_width_alignment;
    matrix = new uint64_t* [height]{};
    for (int i = 0; i < height; ++i) {
        matrix[i] = new uint64_t[width]{};
    }
}

bool Destruction(SandPile& model) {
    SandPile model_duplicate = model;

    model_duplicate.matrix = new uint64_t* [model.height];
    for (int i = 0; i < model.height; ++i) {
        model_duplicate.matrix[i] = new uint64_t[model.width];
    }

    for (int i = 0; i < model.height; ++i) {
        for (int j = 0; j < model.width; ++j) {
            model_duplicate.matrix[i][j] = model.matrix[i][j];
        }
    }

    bool is_fully_destructed = true;
    for (int j = 0; j < model.height; ++j) {
        for (int k = 0; k < model.width; ++k) {
            if (model.matrix[j][k] < 4) {
                continue;
            }
            is_fully_destructed = false;

            if (j + 1 >= model.height) {
                Resize(model, model_duplicate, kDown);
            }
            if (j - 1 < 0) {
                Resize(model, model_duplicate, kUp);
                j++;
            }
            if (k + 1 >= model.width) {
                Resize(model, model_duplicate, kRight);
            }
            if (k - 1 < 0) {
                Resize(model, model_duplicate, kLeft);
                k++;
            }

            model_duplicate.matrix[j + 1][k]++;
            model_duplicate.matrix[j - 1][k]++;
            model_duplicate.matrix[j][k + 1]++;
            model_duplicate.matrix[j][k - 1]++;

            model_duplicate.matrix[j][k] -= 4;
            model.matrix[j][k] -= 4;
        }
    }

    for (int j = 0; j < model.height; ++j) {
        for (int k = 0; k < model.width; ++k) {
            model.matrix[j][k] = model_duplicate.matrix[j][k];
        }
    }

    for (int i = 0; i < model.height; ++i) {
        delete [] model_duplicate.matrix[i];
    }
    delete model_duplicate.matrix;

    return is_fully_destructed;
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
        delete [] original_model.matrix[i];
        delete [] model_duplicate.matrix[i];
    }
    delete original_model.matrix;
    delete model_duplicate.matrix;

    if (direction == kUp || direction == kDown) {
        original_model.height++;
        original_model.matrix = new uint64_t* [original_model.height]{};
        for (int i = 0; i < original_model.height; ++i) {
            original_model.matrix[i] = new uint64_t [original_model.width]{};
        }

        model_duplicate.height++;
        model_duplicate.matrix = new uint64_t* [model_duplicate.height]{};
        for (int i = 0; i < model_duplicate.height; ++i) {
            model_duplicate.matrix[i] = new uint64_t [model_duplicate.width]{};
        }
    } else if (direction == kLeft || direction == kRight) {
        original_model.width++;
        original_model.matrix = new uint64_t* [original_model.height]{};
        for (int i = 0; i < original_model.height; ++i) {
            original_model.matrix[i] = new uint64_t [original_model.width]{};
        }

        model_duplicate.width++;
        model_duplicate.matrix = new uint64_t* [model_duplicate.height]{};
        for (int i = 0; i < model_duplicate.height; ++i) {
            model_duplicate.matrix[i] = new uint64_t [model_duplicate.width]{};
        }
    }

    if (direction == kUp) {
        for (int i = 0; i < original_model.height - 1; ++i) {
            for (int j = 0; j < original_model.width; ++j) {
                original_model.matrix[i + 1][j] = new_original_model[i][j];
                model_duplicate.matrix[i + 1][j] = new_model_duplicate[i][j];
            }
        }
    } else if (direction == kDown) {
        for (int i = 0; i < original_model.height - 1; ++i) {
            for (int j = 0; j < original_model.width; ++j) {
                original_model.matrix[i][j] = new_original_model[i][j];
                model_duplicate.matrix[i][j] = new_model_duplicate[i][j];
            }
        }

    } else if (direction == kLeft) {
        for (int i = 0; i < original_model.height; ++i) {
            for (int j = 0; j < original_model.width - 1; ++j) {
                original_model.matrix[i][j + 1] = new_original_model[i][j];
                model_duplicate.matrix[i][j + 1] = new_model_duplicate[i][j];
            }
        }

    } else if (direction == kRight) {
        for (int i = 0; i < original_model.height; ++i) {
            for (int j = 0; j < original_model.width - 1; ++j) {
                original_model.matrix[i][j] = new_original_model[i][j];
                model_duplicate.matrix[i][j] = new_model_duplicate[i][j];
            }
        }
    }

    for (int i = 0; i < original_model.height - 1; ++i) {
        delete [] new_original_model[i];
    }

    for (int i = 0; i < model_duplicate.height - 1; ++i) {
        delete [] new_model_duplicate[i];
    }

    delete [] new_original_model;
    delete [] new_model_duplicate;
}
