#include "TetrominoSprite.hpp"
#include "ResourceManager.hpp"

#include <iostream>

const int TetrominoSprite::TETROMINO_HEIGHT = 20;

TetrominoSprite::TetrominoSprite(TetrominoPtr shape, int boardTop, int boardLeft) : 
    tetromino(shape), boardTop(boardTop), boardLeft(boardLeft) {
}

TetrominoSprite::~TetrominoSprite() {}

void TetrominoSprite::Render(sf::RenderTarget& target) const {
    draw(tetromino->getShape(),
         boardTop + (tetromino->getTop()*TETROMINO_HEIGHT),
         boardLeft + (tetromino->getLeft()*TETROMINO_HEIGHT),
         target); 
}

int TetrominoSprite::height(const TetrominoShape& shape) {
    int height = 0, maxHeight = 0;
    for(int col=0; col<shape.size(); ++col) {
        for(int row=0; row<shape.size(); ++row) {
            if(shape.get(row, col) == 1) {
                height++;
            }
        }
        maxHeight = std::max(maxHeight, height);
        height = 0;
    }
    return maxHeight;
}

int TetrominoSprite::width(const TetrominoShape& shape) {
    int width = 0, maxWidth = 0;
    for(int row=0; row<shape.size(); ++row) {
        for(int col=0; col<shape.size(); ++col) {
            if(shape.get(row, col) == 1) {
                width++;
            }
        }
        maxWidth = std::max(maxWidth, width);
        width = 0;
    }
    return maxWidth;
}

void TetrominoSprite::draw(const TetrominoShape& shape, int top, int left,
        sf::RenderTarget& target) {
     for(int row=0; row<shape.size(); ++row) {
        for(int col=0; col<shape.size(); ++col) {
            if( shape.get(row, col) == 1 ) {
                sf::Sprite sprite( ResourceManager::getInstance().getTetrominoImage() );
                sprite.SetColor( ResourceManager::getInstance().getColor(shape.getShape()) );
                sprite.SetPosition( 
                    left + (col*TETROMINO_HEIGHT),
                    top + (row*TETROMINO_HEIGHT));

                target.Draw( sprite );
            }
        }
    }    
} 

