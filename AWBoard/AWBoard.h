#ifndef ASTROWAR_AWBOARD_H
#define ASTROWAR_AWBOARD_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <sstream>
#include <vector>


enum GameState { RUNNING, FINISHED_LOSS };
enum Rotation {Up, Down};
enum GameType {Test, Play};
enum Difficulty{Easy, Normal, Hard};

struct Asteriod{
    int PositionX=0;
    int PositionY=0;
    bool diagonal;
    Rotation rotation;
};
struct Bullet{
    int PositionX=0;
    int PositionY=0;
};
struct SpaceShip{
    int PositionX=0;
    int PositionY=0;
    int ShipSpeed=7;
    Bullet bullet[10000];
    int BulletSpeed=15;
};

class AstrowarBoard{
    SpaceShip spaceShip;

    Asteriod asteroid[10000];
    int AsteroidSpeed=3;

    int amount_of_asteroids;
    int amount_of_generated_asteroids;

    int amount_of_bullets_on_board;
    int max_amount_of_bullets_on_board;

    GameState state = RUNNING;
    GameType type;
    Difficulty difficulty;

public:
    AstrowarBoard(GameType type);

    void MoveShip();
    int GetShipPosX();
    int GetShipPosY();

    void Shoot();
    void MoveBullets();
    int GetBulletPosX(int bulletNumber);
    int GetBulletPosY(int bulletNumber);
    int GetAmountofBullets();

    void CreateAsteroid();
    int GetAsteroidPosX(int asteroidNumber);
    int GetAsteroidPosY(int asteroidNumber);
    int GetAsteroidAmount();
    void Destroy_Asteroid(int BulletNumber, int AsteroidNumber);
    void Changeto_DiagonalAsteroid(int AsteroidOne, int AsteroidTwo);
    void MoveAsteroid();


    GameState GetGameState();
    void ChangeGameState();
    GameType GetGameType();
    void ChangeDifficulty(Difficulty dif);
    void RestartBoard();

    std::string getBulletsInShip();
};

#endif //ASTROWAR2XD_AWBOARD_H
