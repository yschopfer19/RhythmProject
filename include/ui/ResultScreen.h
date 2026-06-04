#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

using namespace std;
using namespace sf;

class ResultScreen
{
public:
    ResultScreen(RenderWindow &window);

    void handleEvent(const sf::Event &event);

    void update();
    void draw();

    void setResults(int score, int maxCombo);
    bool isMenuPressed() const;
    void reset();

private:
    RenderWindow &m_window;

    RectangleShape m_menuButton;
    unique_ptr<Text> m_menuText;

    unique_ptr<Text> m_scoreLabel;
    unique_ptr<Text> m_scoreValue;

    unique_ptr<Text> m_comboLabel;
    unique_ptr<Text> m_comboValue;

    unique_ptr<Text> m_resultTitle;

    Font m_font;

    bool m_menuPressed = false;
    int m_score = 0;
    int m_maxCombo = 0;

    bool m_buttonHovered = false;
};
