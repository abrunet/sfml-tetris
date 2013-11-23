#include "TetrominoShape.hpp"

int const TetrominoShape::I_TETROMINO[4][4][4] = {
{{0,0,0,0},
 {1,1,1,1},
 {0,0,0,0},
 {0,0,0,0}},
{{0,0,1,0},
 {0,0,1,0},
 {0,0,1,0},
 {0,0,1,0}},
{{0,0,0,0},
 {0,0,0,0},
 {1,1,1,1},
 {0,0,0,0}},
{{0,1,0,0},
 {0,1,0,0},
 {0,1,0,0},
 {0,1,0,0}}
};

int const TetrominoShape::O_TETROMINO[4][2][2] = {
{{1,1},
 {1,1}},
{{1,1},
 {1,1}},
{{1,1},
 {1,1}},
{{1,1},
 {1,1}}
};

int const TetrominoShape::T_TETROMINO[4][3][3] = {
{{0,1,0},
 {1,1,1},
 {0,0,0}},
{{0,1,0},
 {0,1,1},
 {0,1,0}},
{{0,0,0},
 {1,1,1},
 {0,1,0}},
{{0,1,0},
 {1,1,0},
 {0,1,0}}
};

int const TetrominoShape::S_TETROMINO[4][3][3] = {
{{0,1,1},
 {1,1,0},
 {0,0,0}},
{{0,1,0},
 {0,1,1},
 {0,0,1}},
{{0,0,0},
 {0,1,1},
 {1,1,0}},
{{1,0,0},
 {1,1,0},
 {0,1,0}}
};

int const TetrominoShape::Z_TETROMINO[4][3][3] = {
{{1,1,0},
 {0,1,1},
 {0,0,0}},
{{0,0,1},
 {0,1,1},
 {0,1,0}},
{{0,0,0},
 {1,1,0},
 {0,1,1}},
{{0,1,0},
 {1,1,0},
 {1,0,0}}
};

int const TetrominoShape::J_TETROMINO[4][3][3] = {
{{1,0,0},
 {1,1,1},
 {0,0,0}},
{{0,1,1},
 {0,1,0},
 {0,1,0}},
{{0,0,0},
 {1,1,1},
 {0,0,1}},
{{0,1,0},
 {0,1,0},
 {1,1,0}}
};

int const TetrominoShape::L_TETROMINO[4][3][3] = {
{{0,0,1},
 {1,1,1},
 {0,0,0}},
{{0,1,0},
 {0,1,0},
 {0,1,1}},
{{0,0,0},
 {1,1,1},
 {1,0,0}},
{{1,1,0},
 {0,1,0},
 {0,1,0}}
};

int const TetrominoShape::SHAPE_SIZE[7] = { 4, 2, 3, 3, 3, 3, 3 };


TetrominoShape::TetrominoShape(TetrominoShape::Shape shape, int rotation) : 
        shape(shape), rotation(rotation)
{
}

TetrominoShape::~TetrominoShape() {}

int TetrominoShape::size() const {
    return SHAPE_SIZE[shape];
}

TetrominoShape::Shape TetrominoShape::getShape() const {
    return shape;
}

int TetrominoShape::get(int row, int col) const {
    if (row >= size() || col >= size()) return 0;

    switch(shape) {
    case I:
        return I_TETROMINO[rotation][row][col];
    case O:
        return O_TETROMINO[rotation][row][col];
    case T:
        return T_TETROMINO[rotation][row][col];
    case S:
        return S_TETROMINO[rotation][row][col];
    case Z:
        return Z_TETROMINO[rotation][row][col];
    case J:
        return J_TETROMINO[rotation][row][col];
    case L:
        return L_TETROMINO[rotation][row][col];
    }
    return 0;
}

TetrominoShape TetrominoShape::rotateCw() const {
    return TetrominoShape(shape, (rotation + 1) % 4);
}

TetrominoShape TetrominoShape::rotateCcw() const {
    return TetrominoShape(shape, (rotation -1 < 0 ? 3 : rotation -1));
}

