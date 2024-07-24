#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "AWBoard/AWBoard.h"
#include "AWSFML/AWSFML.h"
#include "AWSFML/Menu.h"

// INSTRUKCJA //
// Poruszanie:
// W lub Up --> Gora //
// S lub Down --> Doł //
// D lub Right --> Prawo //
// A lub Left --> Lewo //
// Space --> Strzal //

int main() {
    srand (time(NULL));

    AstrowarBoard board(Play); // Test - spaceship no collision // Start_Game - normal game //
    AstrowarBoardSFML view(board);
    SFMLMenu MainMenu(board);

    // Asteroid //
    sf::Clock asteroid_clock;
    sf::Time Asteroid_elapsed;
    sf::Time asteroid_time = sf::milliseconds(500);

    sf::Music music;
    music.openFromFile("../press-x-twice.ogg");
    music.setVolume(30);
    music.play();
    music.setLoop(true);

    sf::RenderWindow window(sf::VideoMode(1600, 900), "ASTROWAR !!!");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);

    sf::Event event;

    while (window.isOpen()) {

        while(!MainMenu.PlaySelected() && window.isOpen()){
            window.clear();
            MainMenu.draw(window);
            window.display();



            while (window.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:{
                        window.close();
                        break;
                    }
                    case sf::Event::KeyPressed:{
                        MainMenu.Move(window);
                        break;
                    }
                    case sf::Event::MouseMoved: {
                        //cout << "Ruch" << endl;
                        MainMenu.ChoseOptionMove(event);
                        break;
                    }
                    case sf::Event::MouseButtonPressed: {
                        cout << "Click" << endl;
                        MainMenu.ChoseOptionClick(event, window);
                        break;
                    }
                }
            }
        }

        if(board.GetGameState() == FINISHED_LOSS){
            window.clear();
            view.draw(window);
            window.display();
            sf::sleep(sf::seconds(3));
            MainMenu.ChangePlaySelected();
            board.RestartBoard();
        }

        Asteroid_elapsed = asteroid_clock.getElapsedTime();


        board.MoveBullets();
        board.MoveAsteroid();
        board.MoveShip();

        if(Asteroid_elapsed > asteroid_time){
            board.CreateAsteroid();
            asteroid_clock.restart();
        }

        window.clear();
        view.draw(window);
        window.display();

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:{
                    window.close();
                    break;
                }
                case sf::Event::KeyPressed:{
                    if(event.key.code == sf::Keyboard::Space){
                        board.Shoot();
                    }
                }

            }
        }
    }

    return 0;
}
