#include "background.hpp"
#include "constants.hpp"
#include "utils.hpp"

Background::Background() :
    texture(getRandomTexture()),
    topMargin(createMargin({0, 0})),
    bottomMargin(createMargin({0, WINDOW_HEIGHT - MARGIN_HEIGHT})) {
    texture.setRepeated(true);
}

sf::RectangleShape Background::createMargin(const sf::Vector2f& position) const {
    sf::RectangleShape margin({WINDOW_WIDTH, MARGIN_HEIGHT});
    margin.setPosition(position);
    margin.setTexture(&texture);
    margin.setTextureRect({
        0,
        0,
        static_cast<int>(texture.getSize().y * WINDOW_WIDTH / MARGIN_HEIGHT * 2),
        static_cast<int>(texture.getSize().y * 2)
    });
    return margin;
}

void Background::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(topMargin, states);
    target.draw(bottomMargin, states);
}

const sf::RectangleShape& Background::getTopMargin() const {
    return topMargin;
}

const sf::RectangleShape& Background::getBottomMargin() const {
    return bottomMargin;
}

void Background::makeNewBackground() {
    texture = getRandomTexture();
    texture.setRepeated(true);
    topMargin.setTextureRect({
        0,
        0,
        static_cast<int>(texture.getSize().y * WINDOW_WIDTH / MARGIN_HEIGHT * 2),
        static_cast<int>(texture.getSize().y * 2)
    });
    bottomMargin.setTextureRect({
        0,
        0,
        static_cast<int>(texture.getSize().y * WINDOW_WIDTH / MARGIN_HEIGHT * 2),
        static_cast<int>(texture.getSize().y * 2)
    });
}

