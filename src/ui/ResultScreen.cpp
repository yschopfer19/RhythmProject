#include "ResultScreen.h"
#include <iostream>

using namespace std;
using namespace sf;

ResultScreen::ResultScreen(RenderWindow &window)
    : m_window(window)
{
    if (!m_font.openFromFile("C:/Users/yanni/Desktop/RhythmProject/assets/Arimo-VariableFont_wght.ttf"))
    {
        cout << "Fehler beim Laden der ResultScreen Schrift!" << endl;
    }

    // Titel
    m_resultTitle = make_unique<Text>(m_font, "RESULT", 60);
    m_resultTitle->setPosition({300.f, 50.f});
    m_resultTitle->setFillColor(Color::White);

    // Score Label
    m_scoreLabel = make_unique<Text>(m_font, "Score:", 32);
    m_scoreLabel->setPosition({150.f, 150.f});
    m_scoreLabel->setFillColor(Color::Yellow);

    // Score Value
    m_scoreValue = make_unique<Text>(m_font, "0", 40);
    m_scoreValue->setPosition({150.f, 200.f});
    m_scoreValue->setFillColor(Color::White);

    // Combo Label
    m_comboLabel = make_unique<Text>(m_font, "Max Combo:", 32);
    m_comboLabel->setPosition({150.f, 300.f});
    m_comboLabel->setFillColor(Color::Yellow);

    // Combo Value
    m_comboValue = make_unique<Text>(m_font, "0", 40);
    m_comboValue->setPosition({150.f, 350.f});
    m_comboValue->setFillColor(Color::White);

    // Menu Button
    m_menuButton = RectangleShape({200.f, 50.f});
    m_menuButton.setPosition({300.f, 480.f});
    m_menuButton.setFillColor(Color::Blue);

    m_menuText = make_unique<Text>(m_font, "Main Menu", 24);
    m_menuText->setPosition({320.f, 490.f});
    m_menuText->setFillColor(Color::White);
}

void ResultScreen::handleEvent(const Event &event)
{
    if (auto *mouseButton = event.getIf<Event::MouseButtonPressed>())
    {
        if (mouseButton->button == Mouse::Button::Left)
        {
            Vector2f mousePos = m_window.mapPixelToCoords(mouseButton->position);
            if (m_menuButton.getGlobalBounds().contains(mousePos))
            {
                m_menuPressed = true;
            }
        }
    }
    if (const auto *mouseMove = event.getIf<Event::MouseMoved>())
    {
        Vector2f mousePos =
            m_window.mapPixelToCoords(mouseMove->position);

        m_buttonHovered =
            m_menuButton.getGlobalBounds().contains(mousePos);
    }
}

void ResultScreen::update()
{
    // Button Hover-Effekt
    if (m_buttonHovered)
    {
        m_menuButton.setFillColor(Color::Cyan);
    }
    else
    {
        m_menuButton.setFillColor(Color::Blue);
    }
}

void ResultScreen::draw()
{
    m_window.draw(*m_resultTitle);
    m_window.draw(*m_scoreLabel);
    m_window.draw(*m_scoreValue);
    m_window.draw(*m_comboLabel);
    m_window.draw(*m_comboValue);
    m_window.draw(m_menuButton);
    m_window.draw(*m_menuText);
}

void ResultScreen::setResults(int score, int maxCombo)
{
    m_score = score;
    m_maxCombo = maxCombo;
    m_scoreValue->setString(to_string(score));
    m_comboValue->setString(to_string(maxCombo));
}

bool ResultScreen::isMenuPressed() const
{
    return m_menuPressed;
}

void ResultScreen::reset()
{
    m_menuPressed = false;
    m_buttonHovered = false;
    m_score = 0;
    m_maxCombo = 0;
    m_scoreValue->setString("0");
    m_comboValue->setString("0");
}
