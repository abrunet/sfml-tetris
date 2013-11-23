#ifndef BOARD_HPP_
#define BOARD_HPP_

#include "Tetromino.hpp"
#include "RandomTetrominoGenerator.hpp"
#include "GameState.hpp"
#include <vector>

typedef std::vector<std::vector<int> > grid;

class Board {
public:
    enum Move {LEFT, RIGHT, DOWN, ROTATE_CW, ROTATE_CCW};
    Board(int height = 22, int width = 10);
    virtual ~Board();

    TetrominoShape::Shape previewNextTetromino() const;
    boost::shared_ptr<Tetromino> getTetromino() const;
    const GameState& getGameState() const;
    void moveTetromino(Board::Move move);
    void applyGravity();
    void softDrop();
    void togglePaused();

    int getHeight() const;
    int getWidth() const;
    int get(int row, int col) const;
    bool isPaused() const;

private:
    grid landed;

    int boardHeight;
    int boardWidth;
    bool paused;

    RandomTetrominoGenerator tetrominoGen;
    boost::shared_ptr<Tetromino> tetromino;
    GameState gameState;

    bool canMove(const TetrominoShape& shape, int top, int left);
    int doWallKick(const TetrominoShape& shape, int top, int left) const;
    void land(TetrominoPtr tetromino);
    void clearLines();
    int getInitialColumn(const TetrominoShape& shape) const;
    bool isGameOver();
};

#endif // BOARD_HPP_

