#ifndef paddle_hpp
#define paddle_hpp

#include <SFML/Graphics.hpp>
#include "constants.hpp"

class Paddle : public sf::Drawable {
protected:
    sf::RectangleShape paddleShape;
    const Side side;
    float velocity;
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    Paddle(Side side);
    Side getSide() const;
    float getFrontX() const;
    float getTopY() const;
    float getBottomY() const;
    float getVelocity() const;
};

#endif /* paddle_hpp */
