from setuptools import setup, Extension

tetris_module = Extension(
    'tetrisapi',
    sources=['TetrisAPI.cpp'],
    extra_compile_args=['-std=c++17'],
    language='c++'
)

setup(
    name='tetrisapi',
    version='1.0',
    description='Tetris API Python C Extension',
    ext_modules=[tetris_module],
)
