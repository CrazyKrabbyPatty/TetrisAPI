%module TetrisAPI

%{
#include "TetrisAPI.h"
%}

%include "windows.i" // Для Windows экспорта

// Определяем enum для Python
enum class TETROMINO {
        I,
        O,
        T,
        S,
        Z,
        J,
        L
};

%rename(get_colors) GetColors;
        extern void GetColors(TETROMINO type, unsigned char* r, unsigned char* g, unsigned char* b);

%rename(generate_7bag_sequence) Generate7BagSequence;
        extern void Generate7BagSequence(TETROMINO* sequence, int size);

// Добавляем typemaps для более удобной работы с Python
%typemap(in, numinputs=0) TETROMINO * (TETROMINO temp) {
$1 = &temp;
}

%typemap(argout) TETROMINO * {
$result = SWIG_Python_AppendOutput($result, SWIG_From_int(static_cast<int>(*$1)));
}

%typemap(in) TETROMINO* sequence {
        if (!PySequence_Check($input)) {
            PyErr_SetString(PyExc_TypeError, "Expected a sequence");
            SWIG_fail;
        }

        $1 = (TETROMINO*) malloc(PySequence_Length($input) * sizeof(TETROMINO));
        if (!$1) {
            PyErr_SetString(PyExc_MemoryError, "Failed to allocate memory");
            SWIG_fail;
        }
}

%typemap(freearg) TETROMINO* sequence {
        free($1);
}

%typemap(argout) (TETROMINO* sequence, int size) {
    PyObject* list = PyList_New($2);
    for (int i = 0; i < $2; ++i) {
        PyList_SetItem(list, i, PyLong_FromLong(static_cast<long>($1[i])));
    }
    $result = SWIG_Python_AppendOutput($result, list);
}