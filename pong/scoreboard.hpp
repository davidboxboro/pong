#ifndef scoreboard_hpp
#define scoreboard_hpp

#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "array"

class Scoreboard : public sf::Drawable {
private:
    enum ScoreboardState {
        START,
        GAMEPLAY,
        END
    };
    
    std::array<int, 2> scores;
    std::array<sf::Text, 2> scoreText;
    sf::Text startText;
    sf::Text endText;
    Side winner;
    sf::Font font;
    ScoreboardState scoreboardState;
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    sf::Text initText(const std::string& string, int fontSize) const;
    void updateScoreText(Side side);
    static void centerText(sf::Text& text);
public:
    Scoreboard();
    void incrementScore(Side side);
    std::array<int, 2> getScores() const;
    Side getWinner() const;
    void startGame();
    void endGame();
};

#endif /* scoreboard_hpp */
