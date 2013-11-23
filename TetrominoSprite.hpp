#include <SFML/Graphics.hpp>
#include "Tetromino.hpp"

class TetrominoSprite : public sf::Drawable {

public:
    TetrominoSprite(TetrominoPtr shape, int boardTop, int boardLeft);
    virtual ~TetrominoSprite();

    static int height(const TetrominoShape& shape);
    static int width(const TetrominoShape& shape);
    static void draw(const TetrominoShape& shape, int top, int left, sf::RenderTarget& target);

    static const int TETROMINO_HEIGHT;

private:
    TetrominoPtr tetromino;
    int boardTop;
    int boardLeft;

    virtual void Render(sf::RenderTarget& target) const;
};

