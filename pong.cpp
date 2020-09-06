#include "pong.hpp"

#include <array>
#include <cmath>
#include <iostream>

// helper function to print a vector via operator overload
std::ostream& operator<<(std::ostream& os, const sf::Vector2i& v) {
    os << '(' << v.x << ", " << v.y << ')';
    return os;
}
// helper to get magnitude for a vector, for normalising it
inline float magnitude(const sf::Vector2f& v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}

// functions for the object base class
// constructor, sets *shape to nullptr as not to leave it uninitialised
// but this constructor isnt meant to be called as this class is purely a base for the other objects
// and to increase code resue bc they are largely similar
// I am well aware this is overcomplicated for something so simple but i wanted to do it for the sake of it
object::object() : shape(nullptr){};

// colour getters and setters
const sf::Color& object::get_colour() const {
    return shape->getFillColor();
}

void object::set_colour(const sf::Color& col) {
    shape->setFillColor(col);
}

// position getters and setters
const sf::Vector2f& object::get_pos() const {
    return shape->getPosition();
}

void object::set_pos(const sf::Vector2f& pos) {
    shape->setPosition(pos);
}

// move the shape
void object::move(const sf::Vector2f& movement) {
    shape->move(movement);
}

// draw the shape to the window
void object::draw(sf::RenderWindow& win) const {
    win.draw(*shape);
}
// speed getters and setters
void object::set_speed(float s) {
    speed = s;
}

float object::get_speed() const {
    return speed;
}

// Paddle class functions
// constructor inits attributes and passes saves a shape pointer so the base half of the class can do stuff
Paddle::Paddle(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& colour, float speed) : size(size), speed(speed) {
    rect = sf::RectangleShape(size);
    rect.setPosition(pos);
    shape = &rect;
}

// Ball class functions
// constructor does similar to rect
Ball::Ball(int radius, const sf::Vector2f& pos, const sf::Color& colour, float speed) : radius(radius), speed(speed) {
    circle = sf::CircleShape(radius);
    circle.setPosition(pos);
    circle.setFillColor(colour);
    shape = &circle;
    trajectory = sf::Vector2f(0.0f, 0.0f);  // zeroed intially so that we dont forget to redo it
}

// bounces the ball with respect to the normal of the surface its bouncing off
void Ball::bounce(const sf::Vector2f& norm) {
    if (norm.x == 0) {
        trajectory.y *= -1;
    } else {
        trajectory.x *= -1;
    }
}

// getters and setters for the trajectory of the ball
void Ball::set_trajectory(const sf::Vector2f& v) {
    trajectory.x = v.x / magnitude(v);
    trajectory.y = v.y / magnitude(v);
}

const sf::Vector2f& Ball::get_trajectory() const {
    return trajectory;
}

// collision detection functions, one for a paddle and a ball, another for just a bounding rect and a ball
bool collided(const Ball& b, const Paddle& r) {
    return b.circle.getGlobalBounds().intersects(r.rect.getGlobalBounds());
}

bool collided(const Ball& b, const sf::FloatRect& r) {
    return b.circle.getGlobalBounds().intersects(r);
}

int main() {
    // setup game window
    sf::RenderWindow GameWindow(sf::VideoMode(1280, 720), "");
    GameWindow.setTitle("Pong");
    GameWindow.setFramerateLimit(60);

    // create the objects, store references to them in an array
    Paddle pL(sf::Vector2f(30.0f, 400.0f), sf::Vector2f(30.0f, 70.0f), sf::Color::White, 5);
    Paddle pR(sf::Vector2f(30.0f, 400.0f), sf::Vector2f(1250.0f, 70.0f), sf::Color::White, 5);
    Ball ball(15, sf::Vector2f(640.0f, 360.0f), sf::Color::Red, 5);
    std::array<object*, 3> objects;
    objects[0] = &pL;
    objects[1] = &pR;
    objects[2] = &ball;

    // create boundaries for the ball
    sf::FloatRect top(0, -5, 1280, 5);
    sf::FloatRect bottom(0, 720, 1280, 5);
    sf::FloatRect left(-5, 0, 5, 720);
    sf::FloatRect right(1280, 0, 5, 720);

    // variable to store mouse coords for debug purposes
    sf::Vector2i mcoords;

    ball.set_trajectory(sf::Vector2f(1.0f, 1.0f));  // set initial ball trajectory (this should be done randomly)

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
            pL.move(sf::Vector2f(0, -1) * pL.get_speed());
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            pL.move(sf::Vector2f(0, 1) * pL.get_speed());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            pR.move(sf::Vector2f(0, -1) * pR.get_speed());
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            pR.move(sf::Vector2f(0, 1) * pR.get_speed());
        }

        std::cout << (mcoords = sf::Mouse::getPosition(GameWindow)) << std::endl;

        GameWindow.clear(sf::Color::Black);

        if (collided(ball, top)) {
            ball.bounce(sf::Vector2f(0, 1));
        } else if (collided(ball, bottom)) {
            ball.bounce(sf::Vector2f(0, -1));
        } else if (collided(ball, pL)) {
            ball.bounce(sf::Vector2f(1, 0));
        } else if (collided(ball, pR)) {
            ball.bounce(sf::Vector2f(-1, 0));
        }

        ball.move(ball.get_trajectory() * ball.get_speed());

        // draw that frame
        for (auto a : objects) {
            a->draw(GameWindow);
        }

        GameWindow.display();
    };
}