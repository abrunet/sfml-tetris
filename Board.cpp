#include "Board.hpp"

#include <iostream>

Board::Board(int height, int width) : boardHeight(height), boardWidth(width), 
        paused(false), tetromino(new Tetromino(tetrominoGen.pop()))
{
    for(int i=0; i<height; ++i) {
        landed.push_back( std::vector<int>(width, 0) );
    }
    tetromino->setTopLeft(0, getInitialColumn(tetromino->getShape()));
}

Board::~Board() {
}

TetrominoPtr Board::getTetromino() const {
    return tetromino;
}

void Board::applyGravity() {
    moveTetromino(DOWN);
}

void Board::softDrop() {
    if(paused) return;
    gameState.incrementSoftDropBonus();
    moveTetromino(DOWN);
}

int Board::getHeight() const {
    return boardHeight;
}

int Board::getWidth() const {
    return boardWidth;
}

void Board::togglePaused() {
    paused = !paused;
}

bool Board::isPaused() const {
    return paused;
}

int Board::get(int row, int col) const {
    return landed[row][col];
}

int Board::getInitialColumn(const TetrominoShape& shape) const {
    return (shape.getShape() == TetrominoShape::O ? 4 : 3);
}

void Board::moveTetromino(Move move) {
    if(paused) return;

    if(move == LEFT &&
        canMove(tetromino->getShape(), tetromino->getTop(), tetromino->getLeft() -1)) {
        tetromino->setTopLeft(tetromino->getTop(), tetromino->getLeft() -1);
    }

    if(move == RIGHT &&
        canMove(tetromino->getShape(), tetromino->getTop(), tetromino->getLeft() +1)) {
        tetromino->setTopLeft(tetromino->getTop(), tetromino->getLeft() +1);
    }
    
    if(move == DOWN) {
        if(canMove(tetromino->getShape(), tetromino->getTop() +1, tetromino->getLeft())) {
            tetromino->setTopLeft(tetromino->getTop() +1, tetromino->getLeft());
        }
        else if(!gameState.isGameOver()) {
            land(tetromino);
            tetromino = TetrominoPtr(new Tetromino(tetrominoGen.pop()));
            tetromino->setTopLeft(0, getInitialColumn(tetromino->getShape()));
            if(isGameOver()) {
                // notify game over 
                gameState.setGameOver();
            }
        }
    }

    if(move == ROTATE_CW) {
        TetrominoShape rotated = tetromino->getShape().rotateCw();
        int newLeft = doWallKick(rotated, tetromino->getTop(), tetromino->getLeft());
        if (canMove(rotated, tetromino->getTop(), newLeft)) {
            tetromino->rotateCw();
            tetromino->setTopLeft(tetromino->getTop(), newLeft);
        }
    }

    if(move == ROTATE_CCW) {
        TetrominoShape rotated = tetromino->getShape().rotateCcw();
        int newLeft = doWallKick(rotated, tetromino->getTop(), tetromino->getLeft());
        if (canMove(rotated, tetromino->getTop(), newLeft)) {
            tetromino->rotateCcw();
            tetromino->setTopLeft(tetromino->getTop(), newLeft);
        }
    }
}

bool Board::canMove(const TetrominoShape& shape, int top, int left) {
    for (int row=0; row<shape.size(); ++row) {
        for (int col=0; col<shape.size(); ++col) {
            if (shape.get(row, col) != 0) {
                if (top + row >= boardHeight) {
                    return false;
                }
                if (left + col >= boardWidth) {
                    return false;
                }
                if (landed[row + top][col + left] != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Board::land(TetrominoPtr tetromino) {
    TetrominoShape shape = tetromino->getShape();
    for (int row=0; row<shape.size(); ++row) {
        for (int col=0; col<shape.size(); ++col) {
            if (shape.get(row, col) != 0) {
                landed[row + tetromino->getTop()][col + tetromino->getLeft()] = 1+shape.getShape();
            }
        }
    }
    clearLines();
}

int Board::doWallKick(const TetrominoShape& shape, int top, int left) const {
     for (int row=0; row<shape.size(); ++row) {
        for (int col=0; col<shape.size(); ++col) {
            if (shape.get(row, col) != 0) {
                if (left + col < 0) {
                    left-=(left+col);
                }
                if (left + col >= boardWidth) {
                    left--;
                }
            }
        }
    }
    return left;
}

void Board::clearLines() {
    int linesCleared = 0;
    for (int row=0; row<boardHeight; ++row) {
        bool rowIsFull = true;
        for (int col=0; col<boardWidth; ++col) {
            if (landed[row][col] == 0) {
                rowIsFull = false;
                break;
            }
        }
        
        if (rowIsFull) {
            landed.erase( landed.begin() + row );
            landed.insert( landed.begin(), std::vector<int>(boardWidth, 0));
            linesCleared++;
        }
    }
    // update lines cleared
    gameState.tetrominoLanded( linesCleared );
}

bool Board::isGameOver() {
    return !canMove(tetromino->getShape(), tetromino->getTop(), tetromino->getLeft());
}

TetrominoShape::Shape Board::previewNextTetromino() const {
    return tetrominoGen.peek();
}

const GameState& Board::getGameState() const {
    return gameState;
}

