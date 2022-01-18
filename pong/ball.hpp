#ifndef ball_hpp
#define ball_hpp

#include <SFML/Graphics.hpp>
#include "player_paddle.hpp"
#include "background.hpp"

class Ball : public sf::Drawable {
private:
    sf::CircleShape ballShape;
    sf::Vector2f velocity;
    Side pointWinner;
    BallSpeed ballSpeed;
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    static float getNewYVel(float yCollision, const Paddle& paddle, float xVel);
    sf::Vector2f getRandVelocity() const;
    static sf::Vector2f normalizeSpeed(const sf::Vector2f& vec, float newSpeed);
    
    // intersection-related functions
    struct Trajectory {
        sf::Vector2f pos;
        sf::Vector2f vel;
        float secElapsed;
    };
    Trajectory getPaddleCollision(const Trajectory& traj, const Paddle& paddle);
    Trajectory getBoundaryCollision(const Trajectory& traj);
public:
    Ball();
    void move(float secondsElapsed, const Paddle& playerPaddle, const Paddle& computerPaddle);
    Side getPointWinner() const;
    sf::Vector2f getPosition() const;
    void newPoint();
    void updateBallSpeed(BallSpeed newBallSpeed);
};

#endif /* ball_hpp */
