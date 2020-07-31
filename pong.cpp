#include "pong.hpp"

#include <array>

Collidable::Collidable(const sf::Vector2f& pos, const sf::Color& colour) : pos(pos), colour(colour){};

const sf::Color& Collidable::get_colour() const {
    return colour;
}

void Collidable::set_colour(const sf::Color& col) {
    colour = col;
}

const sf::Vector2f& Collidable::get_pos() const {
    return pos;
}

void Collidable::set_pos(const sf::Vector2f& p) {
    pos = p;
}

void Collidable::move(const sf::Vector2f& movement) {
    pos += movement;
}

Paddle::Paddle(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& colour) : size(size), Collidable(pos, colour) {
    shape = sf::RectangleShape(size);
}

bool Paddle::bounded(const sf::Vector2f& point) const {}

void Paddle::draw(sf::RenderWindow& win) const {
    win.draw(shape);
}

Ball::Ball(int radius, const sf::Vector2f& pos, const sf::Color& colour) : radius(radius), Collidable(pos, colour) {}

bool Ball::bounded(const sf::Vector2f& point) const {}

void Ball::draw(sf::RenderWindow& win) const {
    win.draw(shape);
}

void Ball::bounce(const sf::Vector2f& PoI) {}

int main() {
    sf::RenderWindow GameWindow(sf::VideoMode(1280, 720), "");
    GameWindow.setTitle("Pong");
    GameWindow.setFramerateLimit(60);

    // create the objects, store references to them in an array
    Paddle p1(sf::Vector2f(2.0f, 2.0f), sf::Vector2f(0.0f, 0.0f), sf::Color::White);
    Paddle p2(sf::Vector2f(2.0f, 2.0f), sf::Vector2f(0.0f, 0.0f), sf::Color::White);
    Ball ball(5, sf::Vector2f(100.0f, 100.0f), sf::Color::Red);

    std::array<Collidable*, 3> objects;
    objects[0] = &p1;
    objects[1] = &p2;
    objects[2] = &ball;

    while(GameWindow.isOpen()) {
        sf::Event event;

        while(GameWindow.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    GameWindow.close();
                    break;
            }
        }
        GameWindow.clear(sf::Color::Black);

        // draw that frame
        for(auto a : objects) {
            a->draw(GameWindow);
        }

        GameWindow.display();
    };
}