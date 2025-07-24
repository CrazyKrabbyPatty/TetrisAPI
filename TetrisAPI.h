#pragma once

#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

    // Экспорт функций модуля Python (если хочешь использовать их из C++)
    PyMODINIT_FUNC PyInit_TetrisAPI(void);

    // Также можно объявить вручную вызываемые из C++ функции,
    // если хочешь их тестировать не через Python, а напрямую.
    enum class TETROMINO {
        I, O, T, S, Z, J, L, COUNT
    };

    // Можно вынести сюда сигнатуры С++ функций для Google Test
    // (если будешь вызывать py_generate7bag напрямую)
    PyObject* py_generate7bag(PyObject*, PyObject*);
    PyObject* py_get_colors(PyObject*, PyObject*);

#ifdef __cplusplus
}
#endif
