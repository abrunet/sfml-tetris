#include "KeyboardHelper.hpp"
#include <iostream>

const float KeyboardHelper::DISTANCE_THRESHOLD = 20.0;
const float KeyboardHelper::ACCELERATION = 1.7;
const float KeyboardHelper::INITIAL_SPEED = 60.0;

KeyboardHelper::KeyboardHelper(Board& board) : board(board),
    leftKeyIsDown(false), rightKeyIsDown(false), upKeyIsDown(false),
    downKeyIsDown(false), zKeyIsDown(false), xKeyIsDown(false),
    pauseKeyWasDown(false), frameTime(0.0), speed(INITIAL_SPEED),
    distance(0.0) {
}

KeyboardHelper::~KeyboardHelper() {}

void KeyboardHelper::processInput(const sf::Input& input, float frameTime) {
    this->frameTime = frameTime;

    processKey(Board::RIGHT, input.IsKeyDown(sf::Key::Right), rightKeyIsDown);
    processKey(Board::LEFT, input.IsKeyDown(sf::Key::Left), leftKeyIsDown);
    processKey(Board::ROTATE_CW, input.IsKeyDown(sf::Key::Up), upKeyIsDown);
    
    processKey(Board::ROTATE_CCW, input.IsKeyDown(sf::Key::Z), zKeyIsDown);
    processKey(Board::ROTATE_CW, input.IsKeyDown(sf::Key::X), xKeyIsDown);
    
    softDrop(input.IsKeyDown(sf::Key::Down), downKeyIsDown);
    pause(input.IsKeyDown(sf::Key::P));
}

void KeyboardHelper::processKey(Board::Move move, const bool& keyIsDown, bool& keyWasDown) {
    if (keyIsDown) {
        distance += speed * frameTime;
        if (!keyWasDown) {
            keyWasDown = true;
            board.moveTetromino(move);
        }
        else {
            if (distance > DISTANCE_THRESHOLD) {
                board.moveTetromino(move);
                distance -= DISTANCE_THRESHOLD;
                speed *= 1.7;
            }
        }
    }
    else if (!keyIsDown && keyWasDown) {
        keyWasDown = false;
        distance = 0.0;
        speed = INITIAL_SPEED;
    }
}

void KeyboardHelper::softDrop(const bool& keyIsDown, bool& keyWasDown) {
    if (keyIsDown) {
        distance += 3*speed * frameTime;
        if (!keyWasDown) {
            keyWasDown = true;
            board.softDrop();
        }
        else {
            if (distance > DISTANCE_THRESHOLD) {
                board.softDrop();
                distance -= DISTANCE_THRESHOLD;
            }
        }
    }
    else if (!keyIsDown && keyWasDown) {
        keyWasDown = false;
        distance = 0.0;
        speed = INITIAL_SPEED;
    }
}

void KeyboardHelper::pause(const bool& keyIsDown) {
    if(keyIsDown && !pauseKeyWasDown) {
        pauseKeyWasDown = true;
        board.togglePaused();
    }
    else if(!keyIsDown && pauseKeyWasDown) {
        pauseKeyWasDown = false;
    }
}

