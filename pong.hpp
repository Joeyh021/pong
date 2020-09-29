#ifndef PONG
#define PONG

#include <SFML/Graphics.hpp>

// forward declarations
class Ball;
class Paddle;
class object;

// base class for all the objects to inherit from, mainly for ease of managing them
class object {
   protected:
    sf::Shape* shape;
    float speed;

   public:
    object();  // define a constructor thats non-default but does nothing

    void draw(sf::RenderWindow& win) const;

    const sf::Color& get_colour() const;
    void set_colour(const sf::Color& colour);

    const sf::Vector2f& get_pos() const;
    void set_pos(const sf::Vector2f& pos);
    void move(const sf::Vector2f& movement);

    void set_speed(float s);
    float get_speed() const;
};

// the paddles for the players to control
class Paddle : public object {
   private:
    const sf::Vector2f size;
    sf::RectangleShape rect;

   public:
    int score;
    Paddle(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& colour, float speed);

    friend bool collided(const Ball& b, const Paddle& r);
};

// the ball object
class Ball : public object {
   private:
    const int radius;
    sf::CircleShape circle;
    sf::Vector2f trajectory;

   public:
    Ball(int radius, const sf::Vector2f& pos, const sf::Color& colour, float speed);

    void bounce(const sf::Vector2f& norm);
    void reset(const sf::Vector2f& p);

    void set_trajectory(const sf::Vector2f& v);
    const sf::Vector2f& get_trajectory() const;

    friend bool collided(const Ball& b, const Paddle& r);
    friend bool collided(const Ball& b, const sf::FloatRect& r);
};

#endif