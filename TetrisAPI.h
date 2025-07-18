#pragma once

enum class TETROMINO{
    I,
    O,
    T,
    S,
    Z,
    J,
    L,
    COUNT
};

#if defined(_WIN32) || defined(_WIN64)
    #ifdef TetrisAPI_EXPORTS
        #define TetrisAPI __declspec(dllexport)
    #else
        #define TetrisAPI __declspec(dllimport)
    #endif
#else
    #define TetrisAPI __attribute((visibility("default")))
#endif

extern "C" {
    TetrisAPI void Generate7BagSequence(TETROMINO* sequence, int size);
    TetrisAPI void GetColors(TETROMINO type, unsigned char* r, unsigned char* g, unsigned char* b);
}