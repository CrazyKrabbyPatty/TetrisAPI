#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <random>
#include <algorithm>
#include <array>

enum class TETROMINO {
    I,
    O,
    T,
    S,
    Z,
    J,
    L,
    COUNT
};

const std::array<std::array<unsigned char, 3>, static_cast<size_t>(TETROMINO::COUNT)> COLORS = {{
    {0, 255, 255}, // I
    {255, 255, 0}, // O
    {128, 0, 128}, // T
    {0, 255, 0},   // S
    {255, 0, 0},   // Z
    {0, 0, 255},   // J
    {255, 165, 0}  // L
}};

// generate_7bag_sequence(size)
static PyObject* generate_7bag_sequence(PyObject*, PyObject* args) {
    int size;
    if (!PyArg_ParseTuple(args, "i", &size)) {
        return nullptr;
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::vector<TETROMINO> bag;
    PyObject* list = PyList_New(size);
    if (!list) return nullptr;

    for (int i = 0; i < size; ) {
        if (bag.empty()) {
            bag = {TETROMINO::I, TETROMINO::O, TETROMINO::T,
                   TETROMINO::S, TETROMINO::Z, TETROMINO::J, TETROMINO::L};
            std::shuffle(bag.begin(), bag.end(), gen);
        }
        PyList_SET_ITEM(list, i, PyLong_FromLong(static_cast<long>(bag.back())));
        bag.pop_back();
        ++i;
    }

    return list;
}

// get_colors(tetromino)
static PyObject* get_colors(PyObject*, PyObject* args) {
    int type;
    if (!PyArg_ParseTuple(args, "i", &type)) {
        return nullptr;
    }

    if (type < 0 || type >= static_cast<int>(TETROMINO::COUNT)) {
        PyErr_SetString(PyExc_ValueError, "Invalid TETROMINO value.");
        return nullptr;
    }

    const auto& color = COLORS[static_cast<size_t>(type)];
    return Py_BuildValue("(BBB)", color[0], color[1], color[2]);
}

// Маппинг функций Python -> C++
static PyMethodDef TetrisMethods[] = {
    {"generate_7bag_sequence", generate_7bag_sequence, METH_VARARGS, "Generate a 7-bag Tetris sequence."},
    {"get_colors", get_colors, METH_VARARGS, "Get RGB color for a TETROMINO type."},
    {nullptr, nullptr, 0, nullptr}
};

// Описание модуля
static struct PyModuleDef tetrismodule = {
    PyModuleDef_HEAD_INIT,
    "tetrisapi",
    "Tetris API Module",
    -1,
    TetrisMethods
};

// Инициализация модуля
PyMODINIT_FUNC PyInit_tetrisapi(void) {
    return PyModule_Create(&tetrismodule);
}
