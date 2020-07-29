#include <SFML/Window.hpp>
#include <iostream>

int main() {
    sf::Window window(sf::VideoMode(800, 600), "new window");  // new window
    while (window.isOpen()) {                                  // main event loop
        sf::Event event;                                       // event type variable to hold the event
        while (window.pollEvent(event)) {                      // pop the event into the event var
            switch (event.type) {                              // handle the events
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