#ifndef ASTROWAR2XD_MENU_H
#define ASTROWAR2XD_MENU_H

#include <SFML/Graphics.hpp>
#include "../AWBoard/AWBoard.h"
#include <iostream>

using namespace std;
using namespace sf;

// Podczas tworzenia menu do gry wspomogłem się materiałami zawartymi na stronie: https://www.youtube.com/watch?v=bOG8667yePY //

enum Selected{Start_Game, Select_Difficulty, Exit_Game};

class SFMLMenu{
    Selected MenuSelected;
    bool isSelected;
    bool isPlaySelected;

    Font Font;
    Text StartGame;
    FloatRect StartGameBoundingBox;
    Text Difficulty;
    FloatRect DifficultyBoundingBox;
    Text Difficulty_Now;
    FloatRect DifficultyNowBoundingBox;
    Text ExitGame;
    FloatRect ExitGameBoundingBox;

    RectangleShape Mouse;
    FloatRect MouseBoundingBox;

    Texture background;
    RectangleShape Background;

    AstrowarBoard & board;

public:

    SFMLMenu(AstrowarBoard & b);
    void draw(RenderWindow & win);
    void Move(RenderWindow & win);
    bool PlaySelected();
    void ChangePlaySelected();

    void UseOptions(RenderWindow & win);
    bool IsMouseOnOptions();

    void ChoseOptionClick(Event event, RenderWindow & win);
    void ChoseOptionMove(Event event);
};

#endif //ASTROWAR2XD_MENU_H
