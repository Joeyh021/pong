#ifndef PONG
#define PONG
#include <SFML/Graphics.hpp>
class Collidable {
   protected:
    sf::Shape* shape;

   public:
    Collidable();

    virtual bool bounded(const sf::Vector2f& point) const = 0;
    friend bool collided(const Collidable& objA, const Collidable& objB);

    void draw(sf::RenderWindow& win) const;

    const sf::Color& get_colour() const;
    void set_colour(const sf::Color& colour);

    const sf::Vector2f& get_pos() const;
    void set_pos(const sf::Vector2f& pos);
    void move(const sf::Vector2f& movement);
};

bool collided(const Collidable& objA, const Collidable& objB);

class Paddle : public Collidable {
   private:
    const sf::Vector2f size;
    sf::RectangleShape rect;

   public:
    Paddle(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& colour);

    bool bounded(const sf::Vector2f& point) const override;
};

class Ball : public Collidable {
   private:
    const int radius;
    sf::CircleShape circle;

   public:
    Ball(int radius, const sf::Vector2f& pos, const sf::Color& colour);

    bool bounded(const sf::Vector2f& point) const override;

    void bounce(const sf::Vector2f& PoI);

};

#endif