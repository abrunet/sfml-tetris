#include "GameState.hpp"
#include <iostream>

const unsigned GameState::POINTS_PER_LINE[5] = {0, 40, 100, 300, 1200};
const unsigned GameState::GAMEBOY_LINES_PER_FRAME[] = {
    53, 49, 45, 41, 37, 33, 28, 22, 17, 11, 10, 9, 8, 7, 6, 6, 5, 5, 4, 4, 3};

GameState::GameState() : linesCleared(0), points(0), gameOver(false) {}

GameState::~GameState() {}

unsigned GameState::getLevel() const {
    return linesCleared / 10;
}

unsigned GameState::getPoints() const {
    return points;
}

float GameState::getGravityInterval() const {
    return GAMEBOY_LINES_PER_FRAME[getLevel()] / 59.73;
}

bool GameState::isGameOver() const {
    return gameOver;
}

void GameState::setGameOver() {
    gameOver = true;
}

void GameState::incrementSoftDropBonus() {
    points++;
}

bool GameState::isPaused() const {
    return paused;
}

void GameState::setPaused(bool paused) {
    this->paused = paused;
}

void GameState::tetrominoLanded(int linesCleared) {
    points += (1+getLevel()) * POINTS_PER_LINE[linesCleared];
    this->linesCleared += linesCleared;
}

