#ifndef PONG
#define PONG
#include <SFML/Graphics.hpp>
class Collidable {
   protected:
    sf::Vector2f pos;
    sf::Color colour;

   public:
    Collidable(const sf::Vector2f& pos, const sf::Color& colour);

    virtual bool bounded(const sf::Vector2f& point) const = 0;
    virtual void draw(sf::RenderWindow& win) const = 0;
    friend bool collided(const Collidable& objA, const Collidable& objB);

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
    sf::RectangleShape shape;

   public:
    Paddle(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& colour);

    bool bounded(const sf::Vector2f& point) const override;

    void draw(sf::RenderWindow& win) const override;
};

class Ball : public Collidable {
   private:
    const int radius;
    sf::CircleShape shape;

   public:
    Ball(int radius, const sf::Vector2f& pos, const sf::Color& colour);

    bool bounded(const sf::Vector2f& point) const override;

    void draw(sf::RenderWindow& win) const override;

    void bounce(const sf::Vector2f& PoI);

    void set_pos(const sf::Vector2f p);
};

#endif