#ifndef pong_game_hpp
#define pong_game_hpp

#include <SFML/Graphics.hpp>
#include "ball.hpp"
#include "player_paddle.hpp"
#include "computer_paddle.hpp"
#include "scoreboard.hpp"
#include "background.hpp"

class PongGame {
private:
    enum GameState {
        START_GAME,
        PLAY_POINT,
        END_POINT,
        END_GAME
    };
    
    sf::RenderWindow window;
    PlayerPaddle playerPaddle;
    ComputerPaddle computerPaddle;
    Ball ball;
    Scoreboard scoreboard;
    Background background;
    GameState gameState;
    sf::Clock ballClock;
    sf::Clock waitClock;
    sf::Clock playerPaddleClock;
    const static std::vector<sf::Keyboard::Key> difficultyKeys;
    
    void updateDisplay();
    void handleEvents();
    void playOrEndPoint();
    static bool isDifficultyKey(sf::Keyboard::Key key);
public:
    PongGame();
    void play();
};

#endif /* pong_game_hpp */
