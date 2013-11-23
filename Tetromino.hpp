#ifndef TETROMINO_HPP__
#define TETROMINO_HPP__

#include "TetrominoShape.hpp"

#include <boost/shared_ptr.hpp>

class Tetromino {
public:
    Tetromino(TetrominoShape::Shape);
    virtual ~Tetromino();

    TetrominoShape getShape() const;
    int getTop() const;
    int getLeft() const;

    void setTopLeft(int top, int left);
    
    void rotateCw();
    void rotateCcw();

private:
    TetrominoShape shape;
    int top;
    int left;
};

typedef boost::shared_ptr<Tetromino> TetrominoPtr;

#endif // TETROMINO_HPP__

