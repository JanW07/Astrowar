#include "AWSFML.h"

AstrowarBoardSFML::AstrowarBoardSFML(AstrowarBoard &b) : board(b) {

    Background.setSize(sf::Vector2f(1600, 900));
    //background.loadFromFile("../ExtraFiles/Background1.jpg");
    background.loadFromFile("../ExtraFiles/Backgrounds/Background2.png");
    Background.setTexture(&background);

    Ship.setSize(sf::Vector2f(60, 60));
    ship.loadFromFile("../ExtraFiles/Spaceship2.jpg");
    Ship.setTexture(&ship);

    Bullet.setSize(sf::Vector2f(40, 40));
    bullet.loadFromFile("../ExtraFiles/Bullet.jpg");
    Bullet.setTexture(&bullet);

    Asteroid.setSize(sf::Vector2f(50, 50));
    asteroid.loadFromFile("../ExtraFiles/Asteroid.jpg");
    Asteroid.setTexture(&asteroid);

    Explosion.setSize(sf::Vector2f(50, 50));
    explosion.loadFromFile("../ExtraFiles/Explosion.png");
    Explosion.setTexture(&explosion);

    /*font.loadFromFile("../ExtraFiles/ARIBL0.ttf");
    score.setFont(font);
    bullets.setFont(font);
    text.setFont(font);

    score.setCharacterSize(18);
    score.setFillColor(sf::Color::White);
    score_points.setCharacterSize(18);
    score_points.setFillColor(sf::Color::White);

    bullets.setCharacterSize(18);
    bullets.setFillColor(sf::Color::White);

    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);

    no_bullets.setFont(font);
    no_bullets.setString("No bullets in magazine!!!");
    no_bullets.setCharacterSize(24);
    no_bullets.setFillColor(sf::Color::White);
    no_bullets.setPosition(620, 50);*/
}

void AstrowarBoardSFML::draw(sf::RenderWindow &win) {
    win.draw(Background);
    if(board.GetGameState()==RUNNING)drawShip(win);
    drawBullet(win);
    drawAsteroid(win);
}

void AstrowarBoardSFML::drawShip(sf::RenderWindow &win) {
    int x = board.GetShipPosX();
    int y = board.GetShipPosY();

    Ship.setPosition(x, y);
    if(board.GetGameType() == Play)ShipBoundingBox=Ship.getGlobalBounds();

    win.draw(Ship);
}
void AstrowarBoardSFML::drawBullet(sf::RenderWindow &win) {
    int PosX, PosY;
    int bullets = board.GetAmountofBullets();

    for(int i = 0; i<bullets; i++){
        PosX = board.GetBulletPosX(i);
        PosY = board.GetBulletPosY(i);

        Bullet.setPosition(PosX, PosY);
        BulletBoundingBox[i]=Bullet.getGlobalBounds();

        win.draw(Bullet);
    }
}
void AstrowarBoardSFML::drawAsteroid(sf::RenderWindow &win) {
    int PosX;
    int PosY;
    int amount = board.GetAsteroidAmount();

    for(int i = 0; i < amount; i++){
        PosX = board.GetAsteroidPosX(i);
        PosY = board.GetAsteroidPosY(i);
        Asteroid.setPosition(PosX, PosY);
        AsteroidBoundingBox[i]=Asteroid.getGlobalBounds();

        for(int j=0; j < board.GetAmountofBullets(); j++) {
            if (AsteroidBoundingBox[i].intersects(BulletBoundingBox[j])) {
                board.Destroy_Asteroid(j, i);

                Explosion.setPosition(PosX, PosY);
                win.draw(Explosion);

                std::cout << "Wybuch" << std::endl;
            }
        }

        for(int j = 0; j < board.GetAsteroidAmount(); j++){
            if(i!=j){

                PosX = board.GetAsteroidPosX(j);
                PosY = board.GetAsteroidPosY(j);
                Asteroid.setPosition(PosX, PosY);
                AsteroidBoundingBox[j]=Asteroid.getGlobalBounds();

                PosX = board.GetAsteroidPosX(i);
                PosY = board.GetAsteroidPosY(i);
                Asteroid.setPosition(PosX, PosY);
                AsteroidBoundingBox[i]=Asteroid.getGlobalBounds();

                if (AsteroidBoundingBox[i].intersects(AsteroidBoundingBox[j])) {
                    board.Changeto_DiagonalAsteroid(i , j);
                }
            }

        }

        if(AsteroidBoundingBox[i].intersects(ShipBoundingBox)){
            Explosion.setPosition(board.GetShipPosX(), board.GetShipPosY());

            win.draw(Explosion);

            board.ChangeGameState();

            std::cout << "Koniec Gry" << std::endl;
        }


        win.draw(Asteroid);
    }
}
