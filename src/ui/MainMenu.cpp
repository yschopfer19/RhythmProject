#include <iostream>

#include "MainMenu.h"

using namespace std;
using namespace sf;

MainMenu::MainMenu(RenderWindow &window)
    : m_window(window)
{
    if (!m_font.openFromFile("C:/Users/yanni/Desktop/RhythmProject/assets/Arimo-VariableFont_wght.ttf"))
    {
        cout << "Fehler beim Laden der Schrift!" << endl;
    }

    m_playButton.setSize({200.f, 80.f});
    m_playButton.setPosition({300.f, 250.f});
    m_playButton.setFillColor(sf::Color::Blue);

    m_playText = std::make_unique<Text>(m_font, "PLAY", 32);
    m_playText->setPosition({350.f, 270.f});
}

void MainMenu::draw()
{
    m_window.draw(m_playButton);
    m_window.draw(*m_playText);
}

void MainMenu::handleEvent(const sf::Event &event)
{
    if (auto *mouseButton = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseButton->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f mousePos = m_window.mapPixelToCoords(mouseButton->position);
            if (m_playButton.getGlobalBounds().contains(mousePos))
            {
                m_playPressed = true;
            }
        }
    }
    if (const auto *mouseMove = event.getIf<Event::MouseMoved>())
    {
        sf::Vector2f mousePos =
            m_window.mapPixelToCoords(mouseMove->position);

        m_buttonHovered =
            m_playButton.getGlobalBounds().contains(mousePos);
    }
}

void MainMenu::update()
{
    // Button Hover-Effekt
    if (m_buttonHovered)
    {
        m_playButton.setFillColor(Color::Cyan);
    }
    else
    {
        m_playButton.setFillColor(Color::Blue);
    }
}

bool MainMenu::isPlayPressed() const
{
    return m_playPressed;
}

void MainMenu::reset()
{
    m_playPressed = false;
}