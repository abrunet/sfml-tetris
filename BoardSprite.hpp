#ifndef BOARD_SPRITE_HPP__
#define BOARD_SPRITE_HPP__

#include "Board.hpp"

#include <SFML/Graphics.hpp>

class BoardSprite : public sf::Drawable {
public:
    BoardSprite(int windowHeight, int windowWidth, const Board& boardModel);
    virtual ~BoardSprite();

private:
    sf::Image backgroundImage;
    sf::Sprite backgroundSprite;
    sf::IntRect previewRect;
    sf::IntRect pointsStringRect;
    sf::IntRect levelStringRect;
    sf::String gameOver;

    const Board& boardModel;

    int boardTop;
    int boardLeft;

    const int windowHeight;
    const int windowWidth;

    virtual void Render(sf::RenderTarget& target) const;

    void drawNextTetromino(sf::RenderTarget& target) const; 
    void drawStrings(sf::RenderTarget& target) const;
    void drawMessage(const std::string& message, sf::RenderTarget& target) const;

    static const TetrominoShape::Shape TETROMINO_SHAPES[7];
};

#endif // BOARD_SPRITE_HPP__

