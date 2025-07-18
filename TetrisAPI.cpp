#include "TetrisAPI.h"
#include <random>
#include <algorithm>
#include <array>

const std::array<std::array<unsigned char, 3>, static_cast<size_t>(TETROMINO::COUNT)> COLORS = {{
    {0, 255, 255}, // I - голубой
    {255, 255, 0}, // O - желтый
    {128, 0, 128}, // T - фиолетовый
    {0, 255, 0},   // S - зеленый
    {255, 0, 0},   // Z - красный
    {0, 0, 255},   // J - синий
    {255, 165, 0}  // L - оранжевый
}};

void Generate7BagSequence(TETROMINO* sequence, int size) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::vector<TETROMINO> bag;
    for (int i = 0; i < size; ) {
        if (bag.empty()) {

            bag = {TETROMINO::I, TETROMINO::O, TETROMINO::T,
                   TETROMINO::S, TETROMINO::Z, TETROMINO::J, TETROMINO::L};

            std::shuffle(bag.begin(), bag.end(), gen);
        }

        sequence[i++] = bag.back();
        bag.pop_back();
    }
}

void GetColors(TETROMINO type, unsigned char* r, unsigned char* g, unsigned char* b) {
    if (type >= TETROMINO::COUNT) {
        *r = *g = *b = 0;
        return;
    }

    const auto& color = COLORS[static_cast<size_t>(type)];
    *r = color[0];
    *g = color[1];
    *b = color[2];
}