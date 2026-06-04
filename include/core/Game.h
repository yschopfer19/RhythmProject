#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "../systems/InputSystem.h"
#include "../systems/NoteSystem.h"
#include "../systems/JudgementSystem.h"
#include "../systems/ScoreSystem.h"
#include "../audio/AudioSystem.h"
#include "../charts/Chart.h"
#include "Lane.h"
#include "Types.h"
#include "HoldNote.h"
#include "MainMenu.h"
#include "../ui/ResultScreen.h"

enum class GameState
{
    MENU,
    PLAYING,
    RESULT
};

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void loadChart(const Chart &chart);
    GameState getState();

private:
    sf::RenderWindow window;

    float elapsedTime = 0.0f;

    array<Lane, 4> lanes;

    InputSystem inputSystem;
    NoteSystem noteSystem;
    JudgementSystem judgementSystem;
    ScoreSystem scoreSystem;
    AudioSystem audioSystem;

    MainMenu mainMenu;
    unique_ptr<ResultScreen> resultScreen;
    GameState gameState = GameState::MENU;

    float lastNoteTime = 0.0f;
    float resultScreenStartTime = 0.0f;

    sf::Font hudFont;
    unique_ptr<sf::Text> scoreText;
    unique_ptr<sf::Text> comboText;
    unique_ptr<sf::Text> judgementText;
};