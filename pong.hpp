#ifndef PONG
#define PONG

#include <SFML/Graphics.hpp>

#define PI 3.141592653

class object {
   protected:
    sf::Shape* shape;

   public:
    object();

    virtual bool bounded(const sf::Vector2f& point) const = 0;

    void draw(sf::RenderWindow& win) const;

    const sf::Color& get_colour() const;
    void set_colour(const sf::Color& colour);

    const sf::Vector2f& get_pos() const;
    void set_pos(const sf::Vector2f& pos);
    void move(const sf::Vector2f& movement);
};

class Ball;

class Paddle : public object {
   private:
    const sf::Vector2f size;
    sf::RectangleShape rect;

   public:
    float speed;
    Paddle(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& colour);

    bool bounded(const sf::Vector2f& point) const override;

    friend bool collided(const Ball& b, const Paddle& r);
};

class Ball : public object {
   private:
    const int radius;
    sf::CircleShape circle;
    sf::Vector2f trajectory;

   public:
    float speed;

    Ball(int radius, const sf::Vector2f& pos, const sf::Color& colour);

    bool bounded(const sf::Vector2f& point) const override;

    const sf::Vector2f& get_centre() const;

    void bounce(const sf::Vector2f& norm);

    void set_trajectory(const sf::Vector2f& v);

    const sf::Vector2f& get_trajectory() const;

    friend bool collided(const Ball& b, const Paddle& r);
};

#endif