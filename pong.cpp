#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow GameWindow(sf::VideoMode(1280, 720), "");
    GameWindow.setTitle("Pong");

    while(GameWindow.isOpen()) {
        sf::Event event;

        while(GameWindow.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    GameWindow.close();
                    break;
            }
        }
    };
}