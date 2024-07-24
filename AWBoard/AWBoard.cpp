#include "AWBoard.h"

using namespace std;

AstrowarBoard::AstrowarBoard(GameType type) {
    amount_of_asteroids = 0;
    amount_of_generated_asteroids = 5;
    difficulty = Easy;

    amount_of_bullets_on_board = 0;
    max_amount_of_bullets_on_board = 2;

    spaceShip.PositionX = 0;
    spaceShip.PositionY = 400;

    this->type = type;
    if(type == Test){
        max_amount_of_bullets_on_board = 10000;
    }
}

void AstrowarBoard::MoveShip() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        if(spaceShip.PositionY <= -50){
            spaceShip.PositionY = 850; // o 50 wiecej niż ma okno ponieważ statek ma wielkosc 80x50 a sprawdzamy lewy gorny rog statku //
        } else{
            spaceShip.PositionY=spaceShip.PositionY-spaceShip.ShipSpeed;
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        if(spaceShip.PositionY >= 900){
            spaceShip.PositionY=0;
        } else{
            spaceShip.PositionY=spaceShip.PositionY+spaceShip.ShipSpeed;
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        if(spaceShip.PositionX <= 0){
            cout << "You cant move left" << endl;
        } else{
            spaceShip.PositionX = spaceShip.PositionX-spaceShip.ShipSpeed;
        }


    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        if(spaceShip.PositionX >= 1520){ // o 80 wiecej niż ma okno ponieważ statek ma wielkosc 80x50 a sprawdzamy lewy gorny rog statku //
            cout << "You cant move right" << endl;
        } else{
            spaceShip.PositionX = spaceShip.PositionX+spaceShip.ShipSpeed;
        }
    }
}
int AstrowarBoard::GetShipPosX() {
    return spaceShip.PositionX;
}
int AstrowarBoard::GetShipPosY() {
    return spaceShip.PositionY;
}

void AstrowarBoard::Shoot() {
    if(amount_of_bullets_on_board>=max_amount_of_bullets_on_board){
        return;
    }
        spaceShip.bullet[amount_of_bullets_on_board].PositionX = spaceShip.PositionX;
        spaceShip.bullet[amount_of_bullets_on_board].PositionY = spaceShip.PositionY;
        amount_of_bullets_on_board++;
}
void AstrowarBoard::MoveBullets() {
    for(int i=0; i<amount_of_bullets_on_board; i++){
        if(spaceShip.bullet[i].PositionX > 1650){
            for(int z = 1; z<(amount_of_bullets_on_board - i); z++){
                spaceShip.bullet[i+z-1].PositionX = spaceShip.bullet[i + z].PositionX;
                spaceShip.bullet[i+z-1].PositionY = spaceShip.bullet[i + z].PositionY;
            }
            amount_of_bullets_on_board--;
        }
        spaceShip.bullet[i].PositionX = spaceShip.bullet[i].PositionX + spaceShip.BulletSpeed;
    }
}
int AstrowarBoard::GetBulletPosX(int bulletNumber){
    return spaceShip.bullet[bulletNumber].PositionX;
}
int AstrowarBoard::GetBulletPosY(int bulletNumber){
    return spaceShip.bullet[bulletNumber].PositionY;
}
int AstrowarBoard::GetAmountofBullets() {
    return amount_of_bullets_on_board;
}

void AstrowarBoard::CreateAsteroid() {

    switch (difficulty) {
        case Easy: {
            cout << "Easy" << endl;
            AsteroidSpeed = 2;
            break;
        }
        case Normal: {
            cout << "Normal" << endl;
            amount_of_generated_asteroids = 10;
            AsteroidSpeed = 4;
            break;
        }
        case Hard: {
            cout << "Hard" << endl;
            amount_of_generated_asteroids = 15;
            AsteroidSpeed = 7;
            break;
        }
    }
    int PosX = 1600;
    int PosY = 0;
    int amount = (rand() % amount_of_generated_asteroids);


    for (int i = 0; i < amount; i++) {
        PosY = (rand() % 12) * 76;


        int diagonalornot = rand()%5;
        asteroid[amount_of_asteroids].diagonal= false;

        if(diagonalornot==4){
            asteroid[amount_of_asteroids].diagonal= true;
            asteroid[amount_of_asteroids].rotation= Up;
        }

        for(int y = 0; y < amount_of_asteroids; y++){
            if (asteroid[y].PositionY == PosY && asteroid[y].PositionX == PosX){
                return;
            }
        }

            asteroid[amount_of_asteroids].PositionX = PosX;
            asteroid[amount_of_asteroids].PositionY = PosY;

            amount_of_asteroids++;


        }
    }
int AstrowarBoard::GetAsteroidPosX(int asteroidNumber) {
    return asteroid[asteroidNumber].PositionX;
}
int AstrowarBoard::GetAsteroidPosY(int asteroidNumber) {
    return asteroid[asteroidNumber].PositionY;
}
int AstrowarBoard::GetAsteroidAmount() {
    return amount_of_asteroids;
}
void AstrowarBoard::MoveAsteroid() {

    for(int i = 0; i<amount_of_asteroids; i++) {

        if(asteroid[i].diagonal){
            if(asteroid[i].PositionY>=850){
                asteroid[i].rotation = Down;
            }
            if(asteroid[i].PositionY<=0){
                asteroid[i].rotation = Up;
            }
            if(asteroid[i].rotation == Up) {
                asteroid[i].PositionX = asteroid[i].PositionX - 1;
                asteroid[i].PositionY = asteroid[i].PositionY + AsteroidSpeed;
            }
            if(asteroid[i].rotation == Down){
                asteroid[i].PositionX = asteroid[i].PositionX - 1;
                asteroid[i].PositionY = asteroid[i].PositionY - AsteroidSpeed;
            }
        }

        asteroid[i].PositionX = asteroid[i].PositionX - AsteroidSpeed;

        if (asteroid[i].PositionX <=-100) {
            for (int y = 1; y < (amount_of_asteroids - i); y++) {
                if(asteroid[i + y].diagonal) {
                    asteroid[i + y - 1].PositionX = asteroid[i + y].PositionX;
                    asteroid[i + y - 1].PositionY = asteroid[i + y].PositionY;
                    asteroid[i+y-1].rotation = asteroid[i+y].rotation;
                    asteroid[i + y - 1].diagonal = true;
                }
                else{
                    asteroid[i + y - 1].PositionX = asteroid[i + y].PositionX;
                    asteroid[i + y - 1].PositionY = asteroid[i + y].PositionY;
                    asteroid[i + y - 1].diagonal = false;
                }
            }
            amount_of_asteroids--;
        }
    }

}
void AstrowarBoard::Destroy_Asteroid(int BulletNumber, int AsteroidNumber) {

    for(int i = BulletNumber; i<=amount_of_bullets_on_board; i++){
        spaceShip.bullet[i].PositionX=spaceShip.bullet[i+1].PositionX;
        spaceShip.bullet[i].PositionY=spaceShip.bullet[i+1].PositionY;
    }
    amount_of_bullets_on_board--;

    for(int i = AsteroidNumber+1; i<amount_of_asteroids; i++){


        if(asteroid[i].diagonal) {
            asteroid[i - 1].PositionX = asteroid[i].PositionX;
            asteroid[i - 1].PositionY = asteroid[i].PositionY;
            asteroid[i-1].rotation = asteroid[i].rotation;
            asteroid[i - 1].diagonal = true;
        } else{
            asteroid[i - 1].PositionX = asteroid[i].PositionX;
            asteroid[i - 1].PositionY = asteroid[i].PositionY;
            asteroid[i - 1].diagonal = false;
        }
    }

    amount_of_asteroids--;
}
void AstrowarBoard::Changeto_DiagonalAsteroid(int AsteroidOne, int AsteroidTwo) {

    if(asteroid[AsteroidOne].diagonal && asteroid[AsteroidTwo].diagonal){
        if(asteroid[AsteroidOne].rotation==Up){ asteroid[AsteroidTwo].rotation = Up;}
        else{asteroid[AsteroidTwo].rotation = Down;}

        if(asteroid[AsteroidOne].rotation==Up){asteroid[AsteroidOne].rotation = Down;}
        else{
            asteroid[AsteroidOne].rotation = Up;
        }
    }

    if(asteroid[AsteroidOne].diagonal && !asteroid[AsteroidTwo].diagonal){
        asteroid[AsteroidTwo].diagonal = true;

        if(asteroid[AsteroidOne].rotation==Up){ asteroid[AsteroidTwo].rotation = Up;}
        else{asteroid[AsteroidTwo].rotation = Down;}

        if(asteroid[AsteroidOne].rotation==Up){asteroid[AsteroidOne].rotation = Down;}
        else{
                asteroid[AsteroidOne].rotation = Up;
        }
    }
    if(!asteroid[AsteroidOne].diagonal && asteroid[AsteroidTwo].diagonal){
        asteroid[AsteroidOne].diagonal = true;

        if(asteroid[AsteroidTwo].rotation==Up){ asteroid[AsteroidOne].rotation = Up;}
        else{asteroid[AsteroidOne].rotation = Down;}

        if(asteroid[AsteroidTwo].rotation==Up){asteroid[AsteroidTwo].rotation = Down;}
        else{
            asteroid[AsteroidTwo].rotation = Up;
        }
    }
}

void AstrowarBoard::ChangeGameState() {
    state = FINISHED_LOSS;
}
GameState AstrowarBoard::GetGameState() {
    return state;
}
GameType AstrowarBoard::GetGameType() {
    return type;
}
void AstrowarBoard::ChangeDifficulty(Difficulty dif) {
    difficulty = dif;
}
void AstrowarBoard::RestartBoard() {
    amount_of_asteroids = 0;
    state = RUNNING;

    amount_of_bullets_on_board = 0;
    max_amount_of_bullets_on_board = 2;

    spaceShip.PositionX = 0;
    spaceShip.PositionY = 400;
}