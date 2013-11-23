#ifndef KEYBOARD_HELPER_HPP_
#define KEYBOARD_HELPER_HPP_

#include "Board.hpp"
#include <SFML/Window/Input.hpp>

class KeyboardHelper {
public:
    KeyboardHelper(Board& board);
    virtual ~KeyboardHelper();

    void processInput(const sf::Input& input, float frameTime);

private:
    Board& board;

    bool leftKeyIsDown;
    bool rightKeyIsDown;
    bool upKeyIsDown;
    bool downKeyIsDown; 
    bool zKeyIsDown;
    bool xKeyIsDown;
    bool pauseKeyWasDown;

    float frameTime;
    float speed;
    float distance;

    void processKey(Board::Move move, const bool& keyIsDown, bool& keyWasDown);    
    void softDrop(const bool& keyIsDown, bool& keyWasDown);
    void pause(const bool& keyIsDown);

    static const float DISTANCE_THRESHOLD;
    static const float ACCELERATION;
    static const float INITIAL_SPEED;
};

#endif // KEYBOARD_HELPER_HPP_

