#ifndef background_hpp
#define background_hpp

#include <SFML/Graphics.hpp>

class Background : public sf::Drawable {
private:
    sf::Texture texture;
    sf::RectangleShape topMargin;
    sf::RectangleShape bottomMargin;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    sf::RectangleShape createMargin(const sf::Vector2f& position) const; // helper for constructor
public:
    Background();
    const sf::RectangleShape& getTopMargin() const;
    const sf::RectangleShape& getBottomMargin() const;
    void makeNewBackground();
};

#endif /* background_hpp */
