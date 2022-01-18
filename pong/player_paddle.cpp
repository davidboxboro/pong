#include "player_paddle.hpp"
#include <algorithm>
#include <iostream>
#include <cmath>

PlayerPaddle::PlayerPaddle() : Paddle(RIGHT), pastTimesteps() {}

void PlayerPaddle::move(float ts, float yCursor) {
    // align center of paddle with y-coordinate of cursor
    float yNew = yCursor - paddleShape.getSize().y / 2;
    // paddle cannot go outside margin
    yNew = std::max(yNew, static_cast<float>(MARGIN_HEIGHT));
    yNew = std::min(yNew, static_cast<float>(WINDOW_HEIGHT - MARGIN_HEIGHT - PADDLE_HEIGHT));
    paddleShape.setPosition(paddleShape.getPosition().x, yNew);
    
    // update pastTimesteps and velocity
    pastTimesteps.push_back({yNew, ts});
    while (!pastTimesteps.empty() && (ts - pastTimesteps.front().ts > PADDLE_VELOCITY_TIME_RANGE)) {
        pastTimesteps.pop_front();
    }
    float tsDelta = pastTimesteps.back().ts - pastTimesteps.front().ts;
    float yDelta = pastTimesteps.back().y - pastTimesteps.front().y;
    if (tsDelta > 0) {
        velocity = yDelta / tsDelta;
    }
}

