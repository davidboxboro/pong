#include "background.hpp"
#include "constants.hpp"

Background::Background() :
    topMargin(createMargin({0, 0})),
    bottomMargin(createMargin({0, WINDOW_HEIGHT - MARGIN_HEIGHT})) {}

sf::RectangleShape Background::createMargin(const sf::Vector2f& position) {
    sf::RectangleShape margin({WINDOW_WIDTH, MARGIN_HEIGHT});
    margin.setPosition(position);
    margin.setFillColor(MARGIN_COLOR);
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


