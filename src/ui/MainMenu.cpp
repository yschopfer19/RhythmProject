#include <iostream>
#include <cmath>

#include "MainMenu.h"
#include "UIHelper.h"
#include "UITheme.h"

using namespace std;
using namespace sf;

MainMenu::MainMenu(RenderWindow &window)
    : m_window(window), m_animationTime(0.f)
{
    if (!m_font.openFromFile("C:/Users/yanni/Desktop/RhythmProject/assets/Arimo-VariableFont_wght.ttf"))
    {
        cout << "Fehler beim Laden der Schrift!" << endl;
    }

    // Title - zentriert oben
    m_titleText = std::make_unique<Text>(m_font, "RhythmProject", 80);
    m_titleText->setFillColor(UITheme::Text);
    m_titleText->setOutlineThickness(0.f);

    // Subtitle
    m_subtitleText = std::make_unique<Text>(m_font, "Tap the Beat", 28);
    m_subtitleText->setFillColor(UITheme::TextSecondary);

    // Play Button - zentriert
    m_playButton.setSize({220.f, 80.f});
    m_playButton.setPosition({(800.f - 220.f) / 2.f, 350.f});
    m_playButton.setFillColor(UITheme::Surface);

    m_playText = std::make_unique<Text>(m_font, "PLAY", 40);
    m_playText->setFillColor(sf::Color::White);
    m_playText->setOutlineThickness(1.f);
}

void MainMenu::drawBackground()
{
    // Gradient background
    UIHelper::drawGradientRect(
        m_window,
        {0.f, 0.f},
        {800.f, 600.f},
        UITheme::BackgroundTop,
        UITheme::BackgroundTopRight,
        UITheme::BackgroundBottomLeft,
        UITheme::BackgroundBottomRight);
}

void MainMenu::drawTitle()
{
    // Zentriere Titel
    Rect<float> titleBounds = m_titleText->getLocalBounds();
    m_titleText->setPosition(
        Vector2f((800.f - titleBounds.size.x) / 2.f, 60.f));

    // Zentriere Subtitle
    Rect<float> subtitleBounds = m_subtitleText->getLocalBounds();
    m_subtitleText->setPosition(
        Vector2f((800.f - subtitleBounds.size.x) / 2.f, 160.f));

    m_window.draw(*m_titleText);
    m_window.draw(*m_subtitleText);
}

void MainMenu::draw()
{
    drawBackground();
    drawTitle();

    // Draw button with styling
    Vector2f buttonPos = m_playButton.getPosition();
    Vector2f buttonSize = m_playButton.getSize();

    // Bestimme button farbe
    Color buttonColor = UITheme::Surface;

    if (m_buttonHovered)
    {
        buttonColor = UITheme::SurfaceHover;
    }

    // Shadow
    RectangleShape shadow(buttonSize);
    shadow.setPosition({buttonPos.x + 3.f, buttonPos.y + 3.f});
    shadow.setFillColor(sf::Color(0, 0, 0, 100));
    m_window.draw(shadow);

    // Button
    m_playButton.setFillColor(buttonColor);
    m_playButton.setOutlineColor(sf::Color(255, 255, 255, 150));
    m_playButton.setOutlineThickness(2.f);
    m_window.draw(m_playButton);

    // Glow on hover
    if (m_buttonHovered)
    {
        m_playButton.setOutlineColor(UITheme::Accent);
    }
    else
    {
        m_playButton.setOutlineColor(UITheme::Border);
    }

    m_playButton.setOutlineThickness(1.f);

    // Text zentriert im Button
    Rect<float> textBounds = m_playText->getLocalBounds();
    m_playText->setPosition(
        Vector2f(buttonPos.x + (buttonSize.x - textBounds.size.x) / 2.f,
                 buttonPos.y + (buttonSize.y - textBounds.size.y) / 2.f - 5.f));
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
    m_animationTime += 0.016f; // ~60 FPS
}

bool MainMenu::isPlayPressed() const
{
    return m_playPressed;
}

void MainMenu::reset()
{
    m_playPressed = false;
}