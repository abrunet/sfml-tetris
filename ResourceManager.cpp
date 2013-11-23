#include "ResourceManager.hpp"

ResourceManager::ResourceManager() {
    cubeImage.LoadFromFile("tetromino.png");
    // Cyan for I
    colors.push_back(sf::Color(0, 255, 255, 255));
    // Yellow for O
    colors.push_back(sf::Color(255, 255, 0, 255));
    // Purple for T
    colors.push_back(sf::Color(128, 0, 128, 255));
    // Green for S
    colors.push_back(sf::Color(0, 255, 0, 255));
    // Red for Z
    colors.push_back(sf::Color(255, 0, 0, 255));
    // Blue for J
    colors.push_back(sf::Color(0, 0, 255, 255));
    // Orange for L
    colors.push_back(sf::Color(255, 128, 0, 255));
}

const sf::Color& ResourceManager::getColor(TetrominoShape::Shape shape) const {
    return colors[shape];
}

const sf::Image& ResourceManager::getTetrominoImage() const {
    return cubeImage;
}

