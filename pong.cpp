#include "pong.hpp"

#include <array>
#include <cmath>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const sf::Vector2i& v) {
    os << '(' << v.x << ", " << v.y << ')';
    return os;
}

inline float magnitude(const sf::Vector2f& v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}

inline float dot(const sf::Vector2f& v1, const sf::Vector2f v2) {
    return (v1.x + v2.x) * (v1.y + v2.y);
}
object::object() : shape(nullptr){};

const sf::Color& object::get_colour() const {
    return shape->getFillColor();
}

void object::set_colour(const sf::Color& col) {
    shape->setFillColor(col);
}

const sf::Vector2f& object::get_pos() const {
    return shape->getPosition();
}

void object::set_pos(const sf::Vector2f& pos) {
    shape->setPosition(pos);
}

void object::move(const sf::Vector2f& movement) {
    shape->move(movement);
}

void object::draw(sf::RenderWindow& win) const {
    win.draw(*shape);
}

Paddle::Paddle(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& colour) : size(size) {
    rect = sf::RectangleShape(size);
    rect.setPosition(pos);
    shape = &rect;
}

bool Paddle::bounded(const sf::Vector2f& pos) const {
    return rect.getGlobalBounds().contains(pos);
}

Ball::Ball(int radius, const sf::Vector2f& pos, const sf::Color& colour) : radius(radius) {
    circle = sf::CircleShape(radius);
    circle.setPosition(pos);
    shape = &circle;
    trajectory = sf::Vector2f(0.0f, 0.0f);
}

const sf::Vector2f& Ball::get_centre() const {
    return circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());
}

bool Ball::bounded(const sf::Vector2f& point) const {
    auto centre = get_centre();
    return (magnitude(centre - point) < circle.getRadius());
}

void Ball::bounce(const sf::Vector2f& norm) {
    if (norm.x != 0) {
        trajectory.x *= norm.x;
    } else {
        trajectory.y *= norm.y;
    }
}

void Ball::set_trajectory(const sf::Vector2f& v) {
    trajectory.x = v.x / magnitude(v);
    trajectory.y = v.y / magnitude(v);
}

const sf::Vector2f& Ball::get_trajectory() const {
    return trajectory;
}

bool collided(const Ball& b, const Paddle& r) {
    return b.circle.getGlobalBounds().intersects(r.rect.getGlobalBounds());
}

int main() {
    sf::RenderWindow GameWindow(sf::VideoMode(1280, 720), "");
    GameWindow.setTitle("Pong");
    GameWindow.setFramerateLimit(60);

    // create the objects, store references to them in an arrayw

    Paddle pL(sf::Vector2f(30.0f, 400.0f), sf::Vector2f(30.0f, 70.0f), sf::Color::White);
    Paddle pR(sf::Vector2f(30.0f, 400.0f), sf::Vector2f(1250.0f, 70.0f), sf::Color::White);
    Ball ball(30, sf::Vector2f(640.0f, 360.0f), sf::Color::Red);
    std::array<object*, 3> objects;
    objects[0] = &pL;
    objects[1] = &pR;
    objects[2] = &ball;

    sf::Vector2i mcoords;
    ball.set_trajectory(sf::Vector2f(1.0f, 1.0f));  // set initial ball speed
    ball.speed = 2;
    pL.speed = pR.speed = 5;

    pL.speed = 5;
    while (GameWindow.isOpen()) {
        sf::Event event;

        while (GameWindow.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    GameWindow.close();
                    break;
                default:
                    break;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            pL.move(sf::Vector2f(0, -1) * pL.speed);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            pL.move(sf::Vector2f(0, 1) * pL.speed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            pR.move(sf::Vector2f(0, -1) * pR.speed);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            pR.move(sf::Vector2f(0, 1) * pR.speed);
        }

        std::cout << (mcoords = sf::Mouse::getPosition(GameWindow)) << std::endl;

        GameWindow.clear(sf::Color::Black);

        if (collided(ball, pL)) {
            ball.bounce(sf::Vector2f(1, 0));
        } else if (collided(ball, pR)) {
            ball.bounce(sf::Vector2f(-1, 0));
        } else if (ball.get_pos().x <= 0) {
            ball.bounce(sf::Vector2f(0, 1));
        } else if (ball.get_pos().x >= GameWindow.getSize().x) {
            ball.bounce(sf::Vector2f(0, -1));
        }

        ball.move(ball.get_trajectory() * ball.speed);
        // draw that frame
        for (auto a : objects) {
            a->draw(GameWindow);
        }

        GameWindow.display();
    };
}