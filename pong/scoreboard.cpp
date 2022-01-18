#include "scoreboard.hpp"
#include "constants.hpp"
#include <string>
#include <iostream>
#include <cmath>

Scoreboard::Scoreboard() :
    scores{0, 0},
    scoreboardState(START),
    winner(NONE) {
    if (!font.loadFromFile(FONT_PATH)) {
        return EXIT_FAILURE;
    }
    for (Side side : {LEFT, RIGHT}) {
        scoreText[side] = initText(std::to_string(scores[side]), NUMBER_SIZE);
        updateScoreText(side); // set correct x-coordinate
    }
    startText = initText("Press e (easy), m (medium), h (hard), or i (impossible) to begin.", WORD_SIZE);
    centerText(startText);
}

void Scoreboard::incrementScore(Side side) {
    scores[side]++;
    updateScoreText(side);
    if (scores[side] == WIN_SCORE) {
        winner = side;
    }
    std::string endTextString = ((winner == RIGHT) ? "You win!" : "You lose.");
    endTextString += " Press e (easy), m (medium), h (hard), or i (impossible) to play again.";
    endText = initText(endTextString, WORD_SIZE);
    centerText(endText);
}

std::array<int, 2> Scoreboard::getScores() const {
    return scores;
}

Side Scoreboard::getWinner() const {
    for (Side side : {LEFT, RIGHT}) {
        if (scores[side] == WIN_SCORE) {
            return side;
        }
    }
    return NONE;
}

void Scoreboard::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (scoreboardState == START) {
        target.draw(startText, states);
    } else if (scoreboardState == GAMEPLAY) {
        for (Side side : {LEFT, RIGHT}) {
            target.draw(scoreText[side], states);
        }
    } else if (scoreboardState == END) {
        target.draw(endText, states);
    }
}

void Scoreboard::startGame() {
    scoreboardState = GAMEPLAY;
    winner = NONE;
    for (Side side : {LEFT, RIGHT}) {
        scores[side] = 0;
        updateScoreText(side);
    }
}

void Scoreboard::endGame() {
    scoreboardState = END;
}

// inits text except for x-coordinate
sf::Text Scoreboard::initText(const std::string& string, int fontSize) const {
    sf::Text text(string, font);
    text.setPosition(0, MARGIN_HEIGHT + SCORE_DIST_FROM_TOP); // set correct x-coordinate later
    text.setFillColor(SCORE_COLOR);
    text.setCharacterSize(fontSize);
    return text;
}

void Scoreboard::updateScoreText(Side side) {
    sf::Text& text = scoreText[side];
    text.setString(std::to_string(scores[side]));
    sf::FloatRect textRect = text.getLocalBounds();
    // reset x position
    float x_new = WINDOW_WIDTH / 2 + ((side == RIGHT) ? SCORE_DIST_FROM_CENTER :
                                      (- SCORE_DIST_FROM_CENTER - textRect.width));
    text.setPosition(x_new, text.getPosition().y);
}

void Scoreboard::centerText(sf::Text& text) {
    sf::FloatRect rect = text.getLocalBounds();
    text.setPosition(WINDOW_WIDTH / 2 - rect.width / 2, text.getPosition().y);
}
