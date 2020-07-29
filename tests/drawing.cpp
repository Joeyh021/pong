#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "New Window");  // create new window of type RenderWindow for drawing into

    // main loop
    while(window.isOpen()) {
        sf::Event event;

        while(window.pollEvent(event)) {  // pop event queue
            switch(event.type) {          // handle events
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        // define shit to be drawn
        sf::RectangleShape rect1(sf::Vector2f(100.0f, 100.0f));

        window.clear(sf::Color::Black);  // call clear before anything to clear the current frame

        window.draw(rect1);

        window.display();  // display the current frame
    }
}