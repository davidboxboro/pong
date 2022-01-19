#include "utils.hpp"
#include <cmath>
#include <cstdlib>
#include <assert.h>
#include "constants.hpp"

float getRandUniform(float low, float high) {
    assert(high > low);
    float randZeroOne = static_cast<float>(std::rand()) / RAND_MAX;
    return low + randZeroOne * (high - low);
}

sf::Texture getRandomTexture() {
    sf::Texture texture;
    int randIdx = std::rand() % IMAGE_NAMES.size();
    texture.loadFromFile(RESOURCE_PATH + IMAGE_NAMES[randIdx]);
    return texture;
}
