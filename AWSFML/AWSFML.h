#ifndef ASTROWAR_AWSFML_H
#define ASTROWAR_AWSFML_H

#include "SFML/Graphics.hpp"
#include "../AWBoard/AWBoard.h"

class AstrowarBoardSFML{

    AstrowarBoard & board;

    sf::RectangleShape Background;
    sf::RectangleShape Ship;
    sf::FloatRect ShipBoundingBox;
    sf::RectangleShape Bullet;
    sf::FloatRect BulletBoundingBox[100];
    sf::RectangleShape Asteroid;
    sf::FloatRect AsteroidBoundingBox[1000];
    sf::RectangleShape Explosion;

    sf::Texture background;
    sf::Texture ship;
    sf::Texture asteroid;
    sf::Texture bullet;
    sf::Texture explosion;

    sf::Font font;
    sf::Text score;
    sf::Text score_points;
    sf::Text bullets;
    sf::Text no_bullets;
    sf::Text text;

public:
    AstrowarBoardSFML(AstrowarBoard & b);

    void draw (sf::RenderWindow & win);

    void drawAsteroid (sf::RenderWindow & win);

    void drawShip(sf::RenderWindow & win);

    void SpaceShipAnimation();

    void drawBullet(sf::RenderWindow & win);

    void count_and_draw_Score(sf::RenderWindow & win, sf::Time timeScore);

    bool AddMaxBulletsInShip(sf::Time addmaxbullet);
    bool SpeedUpAsteroid(sf::Time speedupasteroidtime);
    bool MoveBulletsTime(sf::Time movebullets);
    bool MoveAsteroid(sf::Time moveasteroid, sf::RenderWindow &win);
    bool AddBulletsTime(sf::Time addbullet);
};

#endif //ASTROWAR_AWSFML_H
