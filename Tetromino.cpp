#include "Tetromino.hpp"
#include <iostream>

Tetromino::Tetromino(TetrominoShape::Shape shape) : 
        shape(TetrominoShape(shape, 0)), top(0), left(0) {}

Tetromino::~Tetromino() {
}

TetrominoShape Tetromino::getShape() const {
    return shape;
}

int Tetromino::getTop() const {
    return top;
}

int Tetromino::getLeft() const {
    return left;
}

void Tetromino::setTopLeft(int top, int left) {
    this->top = top;
    this->left = left;
}

void Tetromino::rotateCw() {
    shape = shape.rotateCw();
}

void Tetromino::rotateCcw() {
    shape = shape.rotateCcw();
}

