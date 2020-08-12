#include "pong.hpp"

#include <array>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const sf::Vector2i& v) {
    os << '(' << v.x << ", " << v.y << ')';
    return os;
}

Collidable::Collidable() : shape(nullptr){};

const sf::Color& Collidable::get_colour() const {
    return shape->getFillColor();
}

void Collidable::set_colour(const sf::Color& col) {
    shape->setFillColor(col);
}

const sf::Vector2f& Collidable::get_pos() const {
    return shape->getPosition();
}

void Collidable::set_pos(const sf::Vector2f& pos) {
    shape->setPosition(pos);
}

void Collidable::move(const sf::Vector2f& movement) {
    shape->move(movement);
}

void Collidable::draw(sf::RenderWindow& win) const {
    win.draw(*shape);
}

Paddle::Paddle(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& colour) : size(size) {
    rect = sf::RectangleShape(size);
    rect.setPosition(pos);
    shape = &rect;
}

bool Paddle::bounded(const sf::Vector2f& pos) const {
    const sf::Vector2f& rectpos = rect.getPosition();
    const sf::Vector2f& rectsize = rect.getSize();
}

Ball::Ball(int radius, const sf::Vector2f& pos, const sf::Color& colour) : radius(radius) {
    circle = sf::CircleShape(radius);
    circle.setPosition(pos);
    shape = &circle;
}

bool Ball::bounded(const sf::Vector2f& point) const {
    return 0;
}

void Ball::bounce(const sf::Vector2f& PoI) {}

int main() {
    sf::RenderWindow GameWindow(sf::VideoMode(1280, 720), "");
    GameWindow.setTitle("Pong");
    GameWindow.setFramerateLimit(60);

    // create the objects, store references to them in an array

    Paddle p1(sf::Vector2f(10.0f, 10.0f), sf::Vector2f(30.0f, 70.0f), sf::Color::White);
    Paddle p2(sf::Vector2f(10.0f, 10.0f), sf::Vector2f(30.0f, 170.0f), sf::Color::White);
    Ball ball(100, sf::Vector2f(100.0f, 100.0f), sf::Color::Red);

    std::array<Collidable*, 3> objects;
    objects[0] = &p1;
    objects[1] = &p2;
    objects[2] = &ball;

    sf::Vector2i mcoords;

    while(GameWindow.isOpen()) {
        sf::Event event;

        while(GameWindow.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    GameWindow.close();
                    break;
                default:
                    break;
            }
        }
        std::cout << (mcoords = sf::Mouse::getPosition(GameWindow));
        std::cout << p1.bounded(sf::Vector2f(mcoords)) << std::endl;

        GameWindow.clear(sf::Color::Black);

        // draw that frame
        for(auto a : objects) {
            a->draw(GameWindow);
        }

        GameWindow.display();
    };
}