#include "Menu.h"

SFMLMenu::SFMLMenu(AstrowarBoard &b) : board(b)  {
    Font.loadFromFile("../ExtraFiles/ARIBL0.ttf");
    isSelected = false;
    isPlaySelected = false;
    MenuSelected = Start_Game;

    // StartGame
    StartGame.setFont(Font);
    StartGame.setCharacterSize(70);
    StartGame.setPosition(650, 200);
    StartGame.setFillColor(Color::White);
    StartGame.setString("Start");
    StartGameBoundingBox = StartGame.getGlobalBounds();
    // StartGame

    // Difficulty
    Difficulty.setFont(Font);
    Difficulty.setCharacterSize(70);
    Difficulty.setPosition(425, 425);
    Difficulty.setFillColor(Color::White);
    Difficulty.setString("Difficulty:");
    DifficultyBoundingBox = Difficulty.getGlobalBounds();

    Difficulty_Now.setFont(Font);
    Difficulty_Now.setCharacterSize(70);
    Difficulty_Now.setPosition(850, 425);
    Difficulty_Now.setFillColor(Color::White);
    Difficulty_Now.setString("Easy");
    DifficultyNowBoundingBox = Difficulty_Now.getGlobalBounds();

    board.ChangeDifficulty(Easy);
    // Difficulty

    // ExitGame
    ExitGame.setFont(Font);
    ExitGame.setCharacterSize(70);
    ExitGame.setPosition(650, 650);
    ExitGame.setFillColor(Color::White);
    ExitGame.setString("Exit");
    ExitGameBoundingBox = ExitGame.getGlobalBounds();
    // ExitGame

    Mouse.setSize(sf::Vector2f(15, 15));

    Background.setSize(sf::Vector2f(1600, 900));
    background.loadFromFile("../ExtraFiles/Backgrounds/Background_Menu.jpg");
    Background.setTexture(&background);
}

void SFMLMenu::draw(RenderWindow &win) {
    StartGame.setFillColor(Color::White);
    Difficulty.setFillColor(Color::White);
    Difficulty_Now.setFillColor(Color::White);
    ExitGame.setFillColor(Color::White);

    if(MenuSelected == Start_Game){
        StartGame.setFillColor(Color::Yellow);
    }
    if(MenuSelected==Select_Difficulty){
        Difficulty.setFillColor(Color::Yellow);
        Difficulty_Now.setFillColor(Color::Yellow);
    }
    if(MenuSelected==Exit_Game){
        ExitGame.setFillColor(Color::Yellow);
    }

    win.draw(Background);
    win.draw(StartGame);
    win.draw(Difficulty);
    win.draw(Difficulty_Now);
    win.draw(ExitGame);
}

void SFMLMenu::Move(RenderWindow & win) {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        cout << "Up" << endl;
        if(MenuSelected==Select_Difficulty){
            MenuSelected = Start_Game;
            return;
        }
        if(MenuSelected==Exit_Game){
            MenuSelected=Select_Difficulty;
            return;
        }
        return;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        cout << "Down" << endl;
        if(MenuSelected == Start_Game){
            MenuSelected=Select_Difficulty;
            return;
        }
        if(MenuSelected==Select_Difficulty){
            MenuSelected=Exit_Game;
            return;
        }
        return;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
        cout << "Enter" << endl;
        UseOptions(win);

    }
}

bool SFMLMenu::PlaySelected() {
    return isPlaySelected;
}
void SFMLMenu::ChangePlaySelected() {
    if(isPlaySelected){
        isPlaySelected = false;
    } else{
        isPlaySelected = true;
    }
}

void SFMLMenu::UseOptions(RenderWindow & win) {
    if(MenuSelected==Start_Game){
        isPlaySelected = true;
    }

    if(MenuSelected==Select_Difficulty){
        if(Difficulty_Now.getString()=="Easy"){
            Difficulty_Now.setString("Normal");
            board.ChangeDifficulty(Normal);
            return;
        }
        if(Difficulty_Now.getString()=="Normal"){
            Difficulty_Now.setString("Hard");
            board.ChangeDifficulty(Hard);
            return;
        }
        if(Difficulty_Now.getString()=="Hard"){
            Difficulty_Now.setString("Easy");
            board.ChangeDifficulty(Easy);
            return;
        }
    }


    if(MenuSelected==Exit_Game){
        win.close();
    }

    isSelected = true;
    return;
}
bool SFMLMenu::IsMouseOnOptions() {
    if(MouseBoundingBox.intersects(StartGameBoundingBox)){
        return true;
    }
    if(MouseBoundingBox.intersects(DifficultyBoundingBox) || Mouse.getGlobalBounds().intersects(DifficultyNowBoundingBox)){
        return true;
    }
    if(MouseBoundingBox.intersects(ExitGameBoundingBox)){
        return true;
    }
    return false;
}

void SFMLMenu::ChoseOptionMove(Event event) {
    int x = event.mouseMove.x;
    int y = event.mouseMove.y;
    Mouse.setPosition(x, y);
    MouseBoundingBox = Mouse.getGlobalBounds();
    if(MouseBoundingBox.intersects(StartGameBoundingBox)){
        MenuSelected = Start_Game;
    }
    if(MouseBoundingBox.intersects(DifficultyBoundingBox) || Mouse.getGlobalBounds().intersects(DifficultyNowBoundingBox)){
        MenuSelected = Select_Difficulty;
    }
    if(MouseBoundingBox.intersects(ExitGameBoundingBox)){
        MenuSelected = Exit_Game;
    }
}
void SFMLMenu::ChoseOptionClick(Event event, RenderWindow & win) {
    int x = event.mouseButton.x;
    int y = event.mouseButton.y;
    Mouse.setPosition(x, y);
    MouseBoundingBox = Mouse.getGlobalBounds();
    if(IsMouseOnOptions() && (event.mouseButton.button == sf::Mouse::Left)){
        UseOptions(win);
    }
}