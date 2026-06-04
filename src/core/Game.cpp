#include "Game.h"
#include "../charts/ChartLoader.h"
#include <array>
#include "GameConfig.h"
#include "MainMenu.h"

using namespace std;
using namespace sf;

Game::Game()
    : window(sf::VideoMode({800, 600}), "Rhythm Game"),
      mainMenu(window),
      lanes({Lane(50.0f, 50.0f, 130.0f, 500.0f, Color::Blue, Color::White),
             Lane(220.0f, 50.0f, 130.0f, 500.0f, Color::Blue, Color::White),
             Lane(390.0f, 50.0f, 130.0f, 500.0f, Color::Blue, Color::White),
             Lane(560.0f, 50.0f, 130.0f, 500.0f, Color::Blue, Color::White)})
{
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    if (!hudFont.openFromFile("C:/Users/yanni/Desktop/RhythmProject/assets/Arimo-VariableFont_wght.ttf"))
        cout << "Fehler beim Laden der HUD Schrift!" << endl;

    scoreText = make_unique<sf::Text>(hudFont, "", 24);
    comboText = make_unique<sf::Text>(hudFont, "", 24);
    judgementText = make_unique<sf::Text>(hudFont, "", 32);

    scoreText->setPosition({10.f, 10.f});
    comboText->setPosition({10.f, 40.f});
    judgementText->setPosition({300.f, 400.f});

    resultScreen = make_unique<ResultScreen>(window);
}

void Game::loadChart(const Chart &chart)
{
    const auto &notes = chart.getNotes();
    lastNoteTime = 0.0f;

    for (const auto &chartNote : notes)
    {
        float hitTime = chartNote.time;
        float endTime = hitTime + chartNote.duration;
        lastNoteTime = max(lastNoteTime, endTime);

        float spawnTime = max(0.0f, hitTime - GameConfig::NOTE_TRAVEL_TIME);
        if (chartNote.duration > 0.0f)
        {
            // HoldNote erstellen
            auto note = make_unique<HoldNote>(
                lanes[chartNote.lane].getHitzonePosition().x,
                -50.0f - (chartNote.duration * GameConfig::NOTE_SPEED),
                Color::White,
                GameConfig::NOTE_SPEED,
                chartNote.lane,
                spawnTime,
                chartNote.duration * GameConfig::NOTE_SPEED // duration in Pixel umrechnen
            );
            noteSystem.addNote(move(note));
        }
        else
        {
            auto note = make_unique<Note>(
                lanes[chartNote.lane].getHitzonePosition().x,
                -50.0f,
                Color::White,
                GameConfig::NOTE_SPEED,
                chartNote.lane,
                spawnTime);

            noteSystem.addNote(move(note));
        }
    }
}

void Game::run()
{
    Clock clock;

    while (window.isOpen())
    {
        // Time elapsed = clock.restart();
        // Seconds dt{ elapsed.asSeconds() };

        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    auto event = window.pollEvent();
    while (event)
    {
        if (event->is<Event::Closed>())
            window.close();

        if (gameState == GameState::MENU)
        {
            mainMenu.update();
            mainMenu.handleEvent(*event);
            if (mainMenu.isPlayPressed())
            {
                Chart testChart = ChartLoader::createTestChart();
                loadChart(testChart);
                if (!audioSystem.load(testChart.musicPath))
                    cout << "Fehler beim Laden der Musik!" << endl;
                audioSystem.play();
                gameState = GameState::PLAYING;
            }
        }
        else if (gameState == GameState::RESULT)
        {
            resultScreen->handleEvent(*event);
            if (resultScreen->isMenuPressed())
            {
                gameState = GameState::MENU;
                resultScreen->reset();
                scoreSystem.reset();
                noteSystem.reset();
                audioSystem.stop();
                mainMenu.reset();
            }
        }
        else
        {
            inputSystem.handleEvent(*event);
        }

        event = window.pollEvent();
    }
}

void Game::update()
{
    if (gameState == GameState::PLAYING)
    {
        Seconds songTime = audioSystem.getSongTime();

        // Check if it's time to transition to result screen
        if (songTime.value >= lastNoteTime + 2.0f)
        {
            gameState = GameState::RESULT;
            resultScreen->setResults(scoreSystem.getScore(), scoreSystem.getMaxCombo());
            return;
        }

        array<float, 4> hitY;
        for (int i = 0; i < 4; i++)
            hitY[i] = lanes[i].getHitzonePosition().y;

        noteSystem.update(songTime.value, hitY);

        int missed = noteSystem.popMisses();

        for (int i = 0; i < missed; i++)
            scoreSystem.addJudgement(Judgement::MISS);

        auto inputs = inputSystem.pollInputs();

        for (const auto &input : inputs)
        {
            Judgement judgement;
            if (input.action == InputAction::Press)
            {
                judgement = judgementSystem.evaluatePress(
                    input.lane,
                    hitY[input.lane.value],
                    noteSystem.getNotes(),
                    songTime.value);
            }
            else
            {
                judgement = judgementSystem.evaluateRelease(
                    input.lane,
                    hitY[input.lane.value],
                    noteSystem.getNotes());
            }

            scoreSystem.addJudgement(judgement);
        }
    }
    else if (gameState == GameState::RESULT)
    {
        resultScreen->update();
    }
}

void Game::render()
{
    window.clear(Color::Black);

    if (gameState == GameState::MENU)
    {
        mainMenu.draw();
    }
    else if (gameState == GameState::PLAYING)
    {
        for (const auto &lane : lanes)
            lane.draw(window);

        noteSystem.draw(window);

        scoreText->setString("Score: " + to_string(scoreSystem.getScore()));
        comboText->setString("Combo: " + to_string(scoreSystem.getCombo()));

        window.draw(*scoreText);
        window.draw(*comboText);
    }
    else if (gameState == GameState::RESULT)
    {
        resultScreen->draw();
    }

    window.display();
}

/*GameState Game::getState()
{
    return this->gameState;
}*/