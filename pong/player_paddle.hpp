#ifndef player_paddle_hpp
#define player_paddle_hpp

#include "paddle.hpp"
#include <deque>

class PlayerPaddle : public Paddle {
private:
    struct Timestep {
        float y, ts;
    };
    std::deque<Timestep> pastTimesteps;
public:
    PlayerPaddle();
    void move(float ts, float yCursor);
};

#endif /* player_paddle_hpp */
