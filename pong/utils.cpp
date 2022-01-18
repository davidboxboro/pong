#include "utils.hpp"
#include <cmath>
#include <cstdlib>
#include <assert.h>

float getRandUniform(float low, float high) {
    assert(high > low);
    float randZeroOne = static_cast<float>(std::rand()) / RAND_MAX;
    return low + randZeroOne * (high - low);
}
