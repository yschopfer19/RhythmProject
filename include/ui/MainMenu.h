#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class MainMenu
{
public:
    MainMenu(RenderWindow &window);

    void handleEvent(const sf::Event &event);

    void update();
    void draw();

    bool isPlayPressed() const;
    void reset();

private:
    RenderWindow &m_window;

    RectangleShape m_playButton;
    unique_ptr<Text> m_playText;
    Font m_font;

    bool m_playPressed = false;

    bool m_buttonHovered = false;
};