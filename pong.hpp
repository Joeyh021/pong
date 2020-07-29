#ifndef PONG
#define PONG
#include <SFML/Graphics.hpp>
class Collidable {
   protected:
    sf::Vector2i pos;
    sf::Color colour;

   public:
    virtual bool bounded(const sf::Vector2i& point) const;
    virtual void draw() const;
    friend bool collided(const Collidable& objA, const Collidable& objB);

    const sf::Vector2i& get_size() const;

    const sf::Color& get_colour() const;
    void set_colour(const sf::Color& colour);

    const sf::Vector2i& get_pos() const;
    void set_pos(const sf::Vector2i& pos);
    void move(const sf::Vector2i& movement);
};

bool collided(const Collidable& objA, const Collidable& objB);

class Paddle : Collidable {
   private:
    const sf::Vector2i size;
    sf::RectangleShape shape;

   public:
    Paddle(sf::Vector2i size, sf::Vector2i pos, sf::Color colour);
    Paddle(sf::Vector2i size, sf::Color colour);

    bool bounded(const sf::Vector2i& point) const;

    void draw() const;
};

class Ball : Collidable {
   private:
    const int radius;
    sf::CircleShape shape;

   public:
    Ball(sf::Vector2i size, sf::Vector2i pos, sf::Color colour);
    Ball(sf::Vector2i size, sf::Color colour);

    bool bounded(const sf::Vector2i& point) const;

    void draw() const;

    void bounce(const sf::Vector2i& impact);
};

#endif