#include "BoardSprite.hpp"
#include "TetrominoSprite.hpp"
#include "ResourceManager.hpp"

#include <boost/lexical_cast.hpp>

TetrominoShape::Shape const BoardSprite::TETROMINO_SHAPES[7] = {
    TetrominoShape::I,
    TetrominoShape::O,
    TetrominoShape::T,
    TetrominoShape::S,
    TetrominoShape::Z,
    TetrominoShape::J,
    TetrominoShape::L 
};

BoardSprite::BoardSprite(int windowHeight, int windowWidth, const Board& boardModel) : 
        boardModel(boardModel), windowHeight(windowHeight), windowWidth(windowWidth),
        gameOver("Game Over", sf::Font::GetDefaultFont(), 60) {
    int boardWidth = 10*TetrominoSprite::TETROMINO_HEIGHT;
    int boardHeight = 22*TetrominoSprite::TETROMINO_HEIGHT;

    backgroundImage = sf::Image(boardWidth, boardHeight, sf::Color(127,127,127));
    backgroundSprite = sf::Sprite(backgroundImage);
    
    boardTop = (windowHeight-boardHeight)/2;
    boardLeft = (windowWidth-boardWidth)/2;

    backgroundSprite.SetPosition(boardLeft, boardTop);

    previewRect.Left = boardLeft + boardWidth + 10;
    previewRect.Top = boardTop + 10;
    previewRect.Right = previewRect.Left + 100;
    previewRect.Bottom = previewRect.Top + 100;

    sf::FloatRect rect(gameOver.GetRect());
    gameOver.SetPosition(windowWidth /2 - rect.GetWidth() /2,
            windowHeight /2 - rect.GetHeight() /2); 
}

BoardSprite::~BoardSprite() {}

void BoardSprite::Render(sf::RenderTarget& target) const {
    TetrominoSprite tetromino(boardModel.getTetromino(), boardTop, boardLeft);
    target.Draw(backgroundSprite);

    if(!boardModel.isPaused()) {
        for(int row=0; row<boardModel.getHeight(); ++row) {
            for(int col=0; col<boardModel.getWidth(); ++col) {
                if(boardModel.get(row, col) != 0) {
                    sf::Sprite sprite( ResourceManager::getInstance().getTetrominoImage() );
                    sprite.SetColor( ResourceManager::getInstance().getColor(
                        TETROMINO_SHAPES[boardModel.get(row, col)-1] ));
                    sprite.SetPosition( 
                        boardLeft + (col*TetrominoSprite::TETROMINO_HEIGHT),
                        boardTop + (row*TetrominoSprite::TETROMINO_HEIGHT));

                    target.Draw( sprite );
               }
            }
        }
    
        target.Draw(tetromino);

        // Draw the GUI elements
        drawNextTetromino(target);
    }
    else if(!boardModel.getGameState().isGameOver()) {
        drawMessage("Pause", target);
    }
    drawStrings(target);
}

void BoardSprite::drawNextTetromino(sf::RenderTarget& target) const {
    TetrominoShape next(boardModel.previewNextTetromino(), 0);
    int top = previewRect.Top + (previewRect.GetHeight() /2 - TetrominoSprite::height(next) /2);
    int left = previewRect.Left + (previewRect.GetWidth() /2 - TetrominoSprite::width(next) /2);
    
    TetrominoSprite::draw(next, top, left, target);
}

void BoardSprite::drawStrings(sf::RenderTarget& target) const {
    // draw the points
    const GameState& gameState = boardModel.getGameState();
    sf::String points(
            boost::lexical_cast<std::string>(gameState.getPoints()),
            sf::Font::GetDefaultFont(), 24);
    sf::FloatRect pointsStringRect(points.GetRect());
    points.SetPosition(previewRect.Left + 50,
        boardTop + (22*TetrominoSprite::TETROMINO_HEIGHT) - pointsStringRect.GetHeight());
    target.Draw(points);

    sf::String level(boost::lexical_cast<std::string>(gameState.getLevel()),
            sf::Font::GetDefaultFont(), 24);
    level.SetPosition(points.GetPosition().x,
            points.GetPosition().y - level.GetRect().GetHeight() - 40);
    target.Draw(level);

    // draw game over message
    if (gameState.isGameOver()) {
        drawMessage("Game Over", target);
    }
}

void BoardSprite::drawMessage(const std::string& msg, sf::RenderTarget& target) const {
    sf::String message(msg, sf::Font::GetDefaultFont(), 60);

    sf::FloatRect stringRect(message.GetRect());
    message.SetPosition(windowWidth /2 - stringRect.GetWidth() /2,
            windowHeight /2 - stringRect.GetHeight() /2); 

    sf::String shadow(message);
    shadow.SetColor(sf::Color(0,0,0));
    shadow.SetPosition( message.GetPosition() + sf::Vector2f(2.0, 2.0) );

    target.Draw( shadow );
    target.Draw( message );
}

