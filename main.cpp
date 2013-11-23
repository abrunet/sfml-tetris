#include "KeyboardHelper.hpp"
#include "Board.hpp"
#include "BoardSprite.hpp"
#include "TetrominoSprite.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Create the main rendering window
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Tile-matching Puzzle");

    float seconds = 0.0f;
    Board board;
    BoardSprite boardSprite(600, 800, board);
    KeyboardHelper kbHelper(board);

    // Start game loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();
        }

        // Get elapsed time
        float elapsedTime = App.GetFrameTime();
        
        kbHelper.processInput(App.GetInput(), elapsedTime);
        
        float gravityInterval = board.getGameState().getGravityInterval();
        seconds += elapsedTime;
        if (seconds > gravityInterval) {
            seconds -= gravityInterval;
            board.applyGravity();
        }
        
        // Clear screen
        App.Clear();
        
        App.Draw(boardSprite);

        // Display window contents on screen
        App.Display();
    }

    return EXIT_SUCCESS;
}

