#include <SFML/Window.hpp>
#include <iostream>

int main() {
    sf::Window window(sf::VideoMode(800, 600), "new window");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    std::cout << event.key.code;
                    break;
            }
        }
    }
    return 0;
}