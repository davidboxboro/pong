#ifndef constants_hpp
#define constants_hpp

#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 2500;
const int WINDOW_HEIGHT = 1500;

const int MARGIN_HEIGHT = 100;
//const sf::Color MARGIN_COLOR = sf::Color::White;

const int PADDLE_WIDTH = 20;
const int PADDLE_HEIGHT = 200;
const int PADDLE_DIST_FROM_SIDE = 40;
const sf::Color PADDLE_COLOR = sf::Color::White;
const float PADDLE_VELOCITY_TIME_RANGE = 0.05; // time range for calculating paddle velocity

enum ComputerSkill {
    EASY = 3,
    MEDIUM = 4,
    HARD = 5,
    IMPOSSIBLE = 7
}; // high means more difficult

enum BallSpeed {
    SLOW = 1200,
    MODERATE = 2000,
    FAST = 2500,
    LIGHTNING = 4000
};

const int BALL_RADIUS = 30;
//const sf::Color BALL_COLOR = sf::Color(200, 100, 0);
const float INIT_SPEED_SLOWDOWN_FACTOR = 0.5;
const float BALL_VEL_MAX_Y_X_RATIO = 1; // maximum vertical to horizontal velocity ratio

const int WIN_SCORE = 3;

const sf::Color SCORE_COLOR = sf::Color::White;
const int NUMBER_SIZE = 150;
const int WORD_SIZE = 50;
const int SCORE_DIST_FROM_TOP = 50;
const int SCORE_DIST_FROM_CENTER = 100;

const int SECONDS_BTWN_POINTS = 2;

const std::string RESOURCE_PATH = "/Users/davidlu/Projects/pong/pong/Resources/";
const std::string FONT_PATH = RESOURCE_PATH + "OpenSans-Regular.ttf";
const std::vector<std::string> IMAGE_NAMES = {
    "trump.png",
    "pizza.jpeg",
    "biden.jpg",
    "annoying_orange.jpeg",
    "dora.png",
    "broccoli.jpeg"
};
    
enum Side {
    LEFT,
    RIGHT,
    NONE
};

#endif /* constants_hpp */
