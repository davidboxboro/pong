#include "computer_paddle.hpp"
#include "iostream"

ComputerPaddle::ComputerPaddle() :
    Paddle(Side::LEFT) {
}

void ComputerPaddle::move(const Ball& ball, float secElapsed) {
    // update position
    float yNew = paddleShape.getPosition().y + velocity * secElapsed;
    yNew = std::max(yNew, static_cast<float>(MARGIN_HEIGHT));
    yNew = std::min(yNew, static_cast<float>(WINDOW_HEIGHT - MARGIN_HEIGHT - PADDLE_HEIGHT));
    paddleShape.setPosition(paddleShape.getPosition().x, yNew);
    
    // update velocity
    float yPaddleCtr = getTopY() + PADDLE_HEIGHT / 2;
    float ySignedDistFromBall = ball.getPosition().y - yPaddleCtr;
    velocity = skill * (ballSpeed / SLOW) * ySignedDistFromBall;
}

void ComputerPaddle::updateReactSpeed(ComputerSkill newSkill, BallSpeed newBallSpeed) {
    skill = newSkill;
    ballSpeed = newBallSpeed;
}
