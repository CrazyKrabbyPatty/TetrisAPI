#include <gtest/gtest.h>
#include "../TetrisAPI.h"
#include <set>

// Утилита: проверка валидности TETROMINO
bool is_valid_tetromino(TETROMINO t) {
    return t >= TETROMINO::I && t <= TETROMINO::L;
}

TEST(TetrisTest, Generate7BagSequence_SizeCorrect) {
    constexpr int size = 14;
    TETROMINO sequence[size];

    Generate7BagSequence(sequence, size);

    EXPECT_EQ(size, 14);
    for (int i = 0; i < size; ++i) {
        EXPECT_TRUE(is_valid_tetromino(sequence[i]));
    }
}

TEST(TetrisTest, Generate7BagSequence_UniquenessPerBag) {
    constexpr int size = 14;
    TETROMINO sequence[size];

    Generate7BagSequence(sequence, size);

    for (int bag = 0; bag < size; bag += 7) {
        std::set<TETROMINO> bag_set;
        for (int i = bag; i < bag + 7; ++i) {
            bag_set.insert(sequence[i]);
        }
        EXPECT_EQ(bag_set.size(), 7); // все 7 штук разные
    }
}

TEST(TetrisTest, GetColors_ValidOutput) {
    unsigned char r, g, b;
    for (int i = 0; i < static_cast<int>(TETROMINO::COUNT); ++i) {
        GetColors(static_cast<TETROMINO>(i), &r, &g, &b);
        EXPECT_GE(r, 0);
        EXPECT_LE(r, 255);
        EXPECT_GE(g, 0);
        EXPECT_LE(g, 255);
        EXPECT_GE(b, 0);
        EXPECT_LE(b, 255);
    }
}

TEST(TetrisTest, GetColors_InvalidTetromino) {
    unsigned char r = 123, g = 123, b = 123;
    GetColors(static_cast<TETROMINO>(999), &r, &g, &b);
    EXPECT_EQ(r, 0);
    EXPECT_EQ(g, 0);
    EXPECT_EQ(b, 0);
}
