#ifndef TETROMINO_SHAPE_HPP__
#define TETROMINO_SHAPE_HPP__

class TetrominoShape {
public:
    enum Shape { I, O, T, S, Z, J, L };
    TetrominoShape(Shape shape, int rotation);
    virtual ~TetrominoShape();

    int get(int row, int col) const;
    int size() const;
    Shape getShape() const;

    TetrominoShape rotateCw() const;
    TetrominoShape rotateCcw() const;

private:
    Shape shape;
    int rotation;

    static const int SHAPE_SIZE[7];

    static const int I_TETROMINO[4][4][4];
    static const int O_TETROMINO[4][2][2];
    static const int T_TETROMINO[4][3][3];
    static const int S_TETROMINO[4][3][3];
    static const int Z_TETROMINO[4][3][3];
    static const int J_TETROMINO[4][3][3];
    static const int L_TETROMINO[4][3][3];
};

#endif // TETROMINO_SHAPE_HPP__

