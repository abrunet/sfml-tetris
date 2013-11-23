#ifndef GAME_STATE_HPP_
#define GAME_STATE_HPP_

class GameState {
public:
    GameState();
    virtual ~GameState();
    
    unsigned getLevel() const;
    unsigned getPoints() const;
    float getGravityInterval() const;
    bool isGameOver() const;
    bool isPaused() const;

    void incrementSoftDropBonus();
    void tetrominoLanded(int linesCleared);
    void setGameOver();
    void setPaused(bool paused);

private:
    unsigned linesCleared;
    unsigned points;
    bool gameOver;
    bool paused;

    static const unsigned POINTS_PER_LINE[5];
    static const unsigned GAMEBOY_LINES_PER_FRAME[21]; 
};

#endif // GAME_STATE_HPP_

