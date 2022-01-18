#ifndef background_hpp
#define background_hpp

#include <SFML/Graphics.hpp>

class Background : public sf::Drawable {
private:
    const sf::RectangleShape topMargin;
    const sf::RectangleShape bottomMargin;
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    static sf::RectangleShape createMargin(const sf::Vector2f& position); // helper for constructor
public:
    Background();
    const sf::RectangleShape& getTopMargin() const;
    const sf::RectangleShape& getBottomMargin() const;
};

#endif /* background_hpp */
