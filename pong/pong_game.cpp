#include "pong_game.hpp"
#include "constants.hpp"

PongGame::PongGame() :
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "gameWindow"),
    playerPaddle(),
    computerPaddle(),
    ball(),
    scoreboard(),
    background(),
    gameState(START_GAME),
    ballClock(),
    waitClock(),
    playerPaddleClock() {
}

const std::vector<sf::Keyboard::Key> PongGame::difficultyKeys = {
    sf::Keyboard::E, sf::Keyboard::M, sf::Keyboard::H, sf::Keyboard::I};

void PongGame::play() {
    while (window.isOpen()) {
        handleEvents();
        if (gameState == PLAY_POINT || gameState == END_POINT) {
            playOrEndPoint();
        }
        updateDisplay();
    }
}

void PongGame::updateDisplay() {
    // clear and redraw pixels each time; this is how computer graphics is typically done
    window.clear();
    // draw objects (from back to front)
    window.draw(background);
    window.draw(playerPaddle);
    window.draw(computerPaddle);
    window.draw(ball);
    window.draw(scoreboard);
    window.display();
}

bool PongGame::isDifficultyKey(sf::Keyboard::Key key) {
    return std::find(difficultyKeys.begin(), difficultyKeys.end(), key) != difficultyKeys.end();
}

void PongGame::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        // if key is pressed, start first point, resetting clock
        if ((gameState == START_GAME || gameState == END_GAME) && event.type == sf::Event::KeyPressed
                && isDifficultyKey(event.key.code)) {
            ComputerSkill difficulty;
            BallSpeed ballSpeed;
            switch(event.key.code) {
                case sf::Keyboard::E:
                    difficulty = EASY;
                    ballSpeed = SLOW;
                    break;
                case sf::Keyboard::M:
                    difficulty = MEDIUM;
                    ballSpeed = MODERATE;
                    break;
                case sf::Keyboard::H:
                    difficulty = HARD;
                    ballSpeed = FAST;
                    break;
                case sf::Keyboard::I:
                    difficulty = IMPOSSIBLE;
                    ballSpeed = LIGHTNING;
                default:
                    break;
            }
            computerPaddle.updateReactSpeed(difficulty, ballSpeed);
            ball.updateBallSpeed(ballSpeed);
            ball.newPoint();
            gameState = PLAY_POINT;
            ballClock.restart();
            scoreboard.startGame();
        }
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        // player can move their paddle always
        if (event.type == sf::Event::MouseMoved) {
            float ts = playerPaddleClock.getElapsedTime().asSeconds();
            playerPaddle.move(ts, event.mouseMove.y);
        }
    }
}

void PongGame::playOrEndPoint() {
    // move ball
    float secElapsed = ballClock.restart().asSeconds();
    computerPaddle.move(ball, secElapsed);
    ball.move(secElapsed, playerPaddle, computerPaddle);
    // check if there is point winner if still playing point
    if (gameState == PLAY_POINT) {
        Side pointWinner = ball.getPointWinner();
        if (pointWinner != NONE) {
            scoreboard.incrementScore(pointWinner);
            gameState = END_POINT;
            waitClock.restart();
        }
    } else if (waitClock.getElapsedTime().asSeconds() >= SECONDS_BTWN_POINTS) {
        if (scoreboard.getWinner() != NONE) { // end game if game over
            gameState = END_GAME;
            scoreboard.endGame();
        } else {
            gameState = PLAY_POINT;
            ball.newPoint();
        }
    }
}
