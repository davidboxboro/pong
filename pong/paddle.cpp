#include "paddle.hpp"

Paddle::Paddle(Side side) :
    paddleShape({PADDLE_WIDTH, PADDLE_HEIGHT}),
    side(side),
    velocity(0) {
    paddleShape.setFillColor(PADDLE_COLOR);
    // set position depending on side
    float xInit = (side == RIGHT) ?
        WINDOW_WIDTH - PADDLE_WIDTH - PADDLE_DIST_FROM_SIDE : PADDLE_DIST_FROM_SIDE;
    float yInit = WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    paddleShape.setPosition(xInit, yInit);
}

void Paddle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(paddleShape, states);
}

Side Paddle::getSide() const {
    return side;
}

float Paddle::getFrontX() const {
    if (side == RIGHT) {
        return paddleShape.getPosition().x;
    }
    return paddleShape.getPosition().x + PADDLE_WIDTH;
}

float Paddle::getTopY() const {
    return paddleShape.getPosition().y;
}

float Paddle::getBottomY() const {
    return paddleShape.getPosition().y + PADDLE_HEIGHT;
}

float Paddle::getVelocity() const {
    return velocity;
}
