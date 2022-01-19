#include "ball.hpp"
#include "constants.hpp"
#include <cmath>
#include "utils.hpp"

Ball::Ball() :
    ballShape(BALL_RADIUS, 30),
    velocity(getRandVelocity()),
    pointWinner(NONE),
    texture(getRandomTexture()) {
    ballShape.setOrigin(BALL_RADIUS, BALL_RADIUS);
    ballShape.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    ballShape.setTexture(&texture);
}

void Ball::newPoint() {
    ballShape.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    velocity = getRandVelocity();
    pointWinner = NONE;
}

void Ball::getNewTexture() {
    texture = getRandomTexture();
    ballShape.setTextureRect({0, 0, static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y)});
}

void Ball::updateBallSpeed(BallSpeed newBallSpeed) {
    ballSpeed = newBallSpeed;
}

Side Ball::getPointWinner() const {
    return pointWinner;
}

void Ball::move(float secondsElapsed, const Paddle& playerPaddle, const Paddle& computerPaddle) {
    Trajectory curTraj = {ballShape.getPosition(), velocity, secondsElapsed};
    while (curTraj.secElapsed > 0) { // secondsElapsed == 0 means trajectory is complete
        Trajectory newTrajBoundary = getBoundaryCollision(curTraj);
        Trajectory newTrajPaddle = (curTraj.vel.x > 0) ?
            getPaddleCollision(curTraj, playerPaddle) : getPaddleCollision(curTraj, computerPaddle);
        // update curTraj to trajectory that yields most seconds still remaining
        curTraj = (newTrajBoundary.secElapsed > newTrajPaddle.secElapsed) ?
            newTrajBoundary : newTrajPaddle;
    }
    // update member variables to reflect new position of ball
    ballShape.setPosition(curTraj.pos);
    velocity = curTraj.vel;
    
    // determine winner
    if (curTraj.pos.x > playerPaddle.getFrontX()) {
        pointWinner = LEFT;
    } else if (curTraj.pos.x < computerPaddle.getFrontX()) {
        pointWinner = RIGHT;
    }
}

float Ball::getNewYVel(float yCollision, const Paddle& paddle, float xVel) {
    float minYCollision = paddle.getTopY() - BALL_RADIUS;
    float maxYCollision = paddle.getBottomY() + BALL_RADIUS;
    float collisionFrac = (yCollision - minYCollision) / (maxYCollision - minYCollision);
    float minYVel = -BALL_VEL_MAX_Y_X_RATIO * xVel;
    float maxYVel = BALL_VEL_MAX_Y_X_RATIO * xVel;
    float newYVel = (maxYVel - minYVel) * collisionFrac + minYVel;
    return newYVel;
}

Ball::Trajectory Ball::getPaddleCollision(const Trajectory& traj, const Paddle& paddle) {
    sf::Vector2f posNewNoCollision = {
        traj.pos.x + traj.vel.x * traj.secElapsed,
        traj.pos.y + traj.vel.y * traj.secElapsed
    };
    Trajectory newTraj = {posNewNoCollision, traj.vel, 0};
    float xNew = (paddle.getSide() == RIGHT) ?
        (paddle.getFrontX() - BALL_RADIUS) : (paddle.getFrontX() + BALL_RADIUS);
    float secToCollision = (xNew - traj.pos.x) / (posNewNoCollision.x - traj.pos.x) * traj.secElapsed;
    float yNew = traj.pos.y + traj.vel.y * secToCollision;
    if (secToCollision >= 0 && secToCollision < traj.secElapsed &&
            yNew + BALL_RADIUS >= paddle.getTopY() && yNew - BALL_RADIUS <= paddle.getBottomY()) {
        // collision
        newTraj.pos = {xNew, yNew};
        float yVelNew = getNewYVel(yNew, paddle, traj.vel.x);
        //yVelNew = yVelNew / std::abs(yVelNew) * std::max(std::abs(yVelNew), BALL_VEL_MAX_Y_X_RATIO);
        newTraj.vel = normalizeSpeed({-traj.vel.x, yVelNew}, ballSpeed);
        newTraj.secElapsed = traj.secElapsed - secToCollision;
    }
    return newTraj;
}

Ball::Trajectory Ball::getBoundaryCollision(const Trajectory& traj) {
    sf::Vector2f posNewNoCollision = {
        traj.pos.x + traj.vel.x * traj.secElapsed,
        traj.pos.y + traj.vel.y * traj.secElapsed
    };
    Trajectory newTraj = {posNewNoCollision, traj.vel, 0};
    float amountAbove = MARGIN_HEIGHT - (posNewNoCollision.y - BALL_RADIUS);
    float amountBelow = (posNewNoCollision.y + BALL_RADIUS) - (WINDOW_HEIGHT - MARGIN_HEIGHT);
    if (amountAbove > 0 || amountBelow > 0) { // collision either with top or bottom
        // collision position depends on whether it was with top or bottom region
        float yNew = (traj.vel.y < 0) ?
            MARGIN_HEIGHT + BALL_RADIUS : WINDOW_HEIGHT - MARGIN_HEIGHT - BALL_RADIUS;
        float secToCollision = (yNew - traj.pos.y) / (posNewNoCollision.y - traj.pos.y) * traj.secElapsed;
        float xNew = traj.pos.x + traj.vel.x * secToCollision;
        newTraj = {{xNew, yNew}, {traj.vel.x, -traj.vel.y}, traj.secElapsed - secToCollision};
    }
    return newTraj;
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(ballShape, states);
}

sf::Vector2f Ball::getRandVelocity() const {
    float x = 1;
    float y = getRandUniform(-BALL_VEL_MAX_Y_X_RATIO, BALL_VEL_MAX_Y_X_RATIO);
    return normalizeSpeed({x, y}, ballSpeed * INIT_SPEED_SLOWDOWN_FACTOR);
}

sf::Vector2f Ball::normalizeSpeed(const sf::Vector2f &vec, float newSpeed) {
    float norm = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    return {vec.x * newSpeed / norm, vec.y * newSpeed / norm};
}

sf::Vector2f Ball::getPosition() const {
    return ballShape.getPosition();
}
