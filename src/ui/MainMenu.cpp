#include <iostream>
#include <cmath>

#include "MainMenu.h"
#include "UIHelper.h"

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
    m_titleText->setFillColor(sf::Color(100, 200, 255));
    m_titleText->setOutlineThickness(2.f);
    m_titleText->setOutlineColor(sf::Color(50, 150, 200));

    // Subtitle
    m_subtitleText = std::make_unique<Text>(m_font, "Tap the Beat", 28);
    m_subtitleText->setFillColor(sf::Color(150, 200, 255));

    // Play Button - zentriert
    m_playButton.setSize({220.f, 80.f});
    m_playButton.setPosition({(800.f - 220.f) / 2.f, 350.f});
    m_playButton.setFillColor(sf::Color(70, 130, 180));

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
        sf::Color(10, 20, 50),   // Top Left - Dark Blue
        sf::Color(20, 30, 80),   // Top Right - Darker Blue
        sf::Color(20, 40, 100),  // Bottom Left - Navy
        sf::Color(30, 60, 120)); // Bottom Right - Deep Navy

    // Decorative circles/shapes
    CircleShape circle1(100.f);
    circle1.setFillColor(sf::Color(70, 130, 180, 50));
    circle1.setPosition({-50.f, -50.f});
    m_window.draw(circle1);

    CircleShape circle2(80.f);
    circle2.setFillColor(sf::Color(100, 160, 220, 40));
    circle2.setPosition({700.f, 450.f});
    m_window.draw(circle2);
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
    Color buttonColor = sf::Color(70, 130, 180);
    if (m_buttonHovered)
    {
        buttonColor = sf::Color(100, 160, 220);
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
        for (int i = 0; i < 2; i++)
        {
            RectangleShape glow(buttonSize);
            glow.setPosition(buttonPos);
            glow.setFillColor(sf::Color::Transparent);
            glow.setOutlineColor(sf::Color(100, 160, 220, 80 - i * 30));
            glow.setOutlineThickness(2.f);
            glow.setScale({1.f + i * 0.1f, 1.f + i * 0.1f});
            glow.setOrigin({buttonSize.x / 2, buttonSize.y / 2});
            glow.setPosition({buttonPos.x + buttonSize.x / 2, buttonPos.y + buttonSize.y / 2});
            m_window.draw(glow);
        }
    }

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