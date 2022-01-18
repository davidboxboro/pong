#ifndef computer_paddle_hpp
#define computer_paddle_hpp

#include "paddle.hpp"
#include "ball.hpp"

class ComputerPaddle : public Paddle {
private:
    ComputerSkill skill;
    BallSpeed ballSpeed;
public:
    ComputerPaddle();
    void move(const Ball& ball, float secElapsed);
    void updateReactSpeed(ComputerSkill skill, BallSpeed ballSpeed);
};

#endif /* computer_paddle_hpp */
