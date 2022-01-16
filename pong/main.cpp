// Pong game

#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::CircleShape ball(5);
    sf::Vector2f vel(200, 200);
    sf::Vector2f pos(50, 50);
    
    sf::RenderWindow window(sf::VideoMode(2500, 1500), "window");
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        float elapsed = clock.restart().asSeconds();
        pos += vel * elapsed;
        window.clear();
        ball.setPosition(pos);
        window.draw(ball);
        window.display();
    }
}
