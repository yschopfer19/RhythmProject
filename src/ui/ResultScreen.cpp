#include "ResultScreen.h"
#include "UIHelper.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace sf;

ResultScreen::ResultScreen(RenderWindow &window)
    : m_window(window)
{
    if (!m_font.openFromFile("C:/Users/yanni/Desktop/RhythmProject/assets/Arimo-VariableFont_wght.ttf"))
    {
        cout << "Fehler beim Laden der ResultScreen Schrift!" << endl;
    }

    // Titel - centered
    m_resultTitle = make_unique<Text>(m_font, "RESULT", 72);
    m_resultTitle->setFillColor(Color(100, 200, 255));
    m_resultTitle->setOutlineThickness(2.f);
    m_resultTitle->setOutlineColor(Color(50, 150, 200));

    // Score Label
    m_scoreLabel = make_unique<Text>(m_font, "Score", 32);
    m_scoreLabel->setFillColor(Color(255, 200, 100));

    // Score Value
    m_scoreValue = make_unique<Text>(m_font, "0", 56);
    m_scoreValue->setFillColor(Color(255, 255, 200));
    m_scoreValue->setOutlineThickness(1.f);
    m_scoreValue->setOutlineColor(Color(255, 200, 100));

    // Combo Label
    m_comboLabel = make_unique<Text>(m_font, "Max Combo", 32);
    m_comboLabel->setFillColor(Color(150, 200, 255));

    // Combo Value
    m_comboValue = make_unique<Text>(m_font, "0", 56);
    m_comboValue->setFillColor(Color(200, 230, 255));
    m_comboValue->setOutlineThickness(1.f);
    m_comboValue->setOutlineColor(Color(150, 200, 255));

    // Menu Button - zentriert unten
    m_menuButton = RectangleShape({220.f, 70.f});
    m_menuButton.setPosition({(800.f - 220.f) / 2.f, 480.f});
    m_menuButton.setFillColor(Color(70, 130, 180));

    m_menuText = make_unique<Text>(m_font, "BACK TO MENU", 28);
    m_menuText->setFillColor(Color::White);
    m_menuText->setOutlineThickness(1.f);
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
        m_menuButton.setFillColor(Color(100, 160, 220));
    }
    else
    {
        m_menuButton.setFillColor(Color(70, 130, 180));
    }
}

void ResultScreen::draw()
{
    // Background gradient
    UIHelper::drawGradientRect(
        m_window,
        {0.f, 0.f},
        {800.f, 600.f},
        Color(10, 20, 50),   // Top Left
        Color(20, 30, 80),   // Top Right
        Color(20, 40, 100),  // Bottom Left
        Color(30, 60, 120)); // Bottom Right

    // Title - centered
    Rect<float> titleBounds = m_resultTitle->getLocalBounds();
    m_resultTitle->setPosition(
        Vector2f((800.f - titleBounds.size.x) / 2.f, 30.f));
    m_window.draw(*m_resultTitle);

    // Separator line under title
    UIHelper::drawSeparator(
        m_window,
        {100.f, 120.f},
        {700.f, 120.f},
        2.f,
        Color(100, 150, 200));

    // Score section - left side
    float scoreX = 150.f;
    float scoreY = 180.f;

    Rect<float> scoreLabelBounds = m_scoreLabel->getLocalBounds();
    m_scoreLabel->setPosition(
        Vector2f(scoreX + (300.f - scoreLabelBounds.size.x) / 2.f, scoreY));
    m_window.draw(*m_scoreLabel);

    Rect<float> scoreValueBounds = m_scoreValue->getLocalBounds();
    m_scoreValue->setPosition(
        Vector2f(scoreX + (300.f - scoreValueBounds.size.x) / 2.f, scoreY + 60.f));
    m_window.draw(*m_scoreValue);

    // Decorative box around score
    RectangleShape scoreBox({280.f, 180.f});
    scoreBox.setPosition({scoreX + 10.f, scoreY - 10.f});
    scoreBox.setFillColor(Color::Transparent);
    scoreBox.setOutlineColor(Color(100, 200, 255, 150));
    scoreBox.setOutlineThickness(2.f);
    m_window.draw(scoreBox);

    // Combo section - right side
    float comboX = 450.f;
    float comboY = 180.f;

    Rect<float> comboLabelBounds = m_comboLabel->getLocalBounds();
    m_comboLabel->setPosition(
        Vector2f(comboX + (300.f - comboLabelBounds.size.x) / 2.f, comboY));
    m_window.draw(*m_comboLabel);

    Rect<float> comboValueBounds = m_comboValue->getLocalBounds();
    m_comboValue->setPosition(
        Vector2f(comboX + (300.f - comboValueBounds.size.x) / 2.f, comboY + 60.f));
    m_window.draw(*m_comboValue);

    // Decorative box around combo
    RectangleShape comboBox({280.f, 180.f});
    comboBox.setPosition({comboX + 10.f, comboY - 10.f});
    comboBox.setFillColor(Color::Transparent);
    comboBox.setOutlineColor(Color(150, 200, 255, 150));
    comboBox.setOutlineThickness(2.f);
    m_window.draw(comboBox);

    // Menu Button
    Vector2f buttonPos = m_menuButton.getPosition();
    Vector2f buttonSize = m_menuButton.getSize();

    // Shadow
    RectangleShape shadow(buttonSize);
    shadow.setPosition({buttonPos.x + 3.f, buttonPos.y + 3.f});
    shadow.setFillColor(Color(0, 0, 0, 100));
    m_window.draw(shadow);

    // Button
    m_menuButton.setOutlineColor(Color(255, 255, 255, 150));
    m_menuButton.setOutlineThickness(2.f);
    m_window.draw(m_menuButton);

    // Glow on hover
    if (m_buttonHovered)
    {
        RectangleShape glow(buttonSize);
        glow.setPosition(buttonPos);
        glow.setFillColor(Color::Transparent);
        glow.setOutlineColor(Color(100, 160, 220, 150));
        glow.setOutlineThickness(2.f);
        glow.setScale({1.05f, 1.05f});
        glow.setOrigin({buttonSize.x / 2, buttonSize.y / 2});
        glow.setPosition({buttonPos.x + buttonSize.x / 2, buttonPos.y + buttonSize.y / 2});
        m_window.draw(glow);
    }

    // Text centered in button
    Rect<float> textBounds = m_menuText->getLocalBounds();
    m_menuText->setPosition(
        Vector2f(buttonPos.x + (buttonSize.x - textBounds.size.x) / 2.f,
                 buttonPos.y + (buttonSize.y - textBounds.size.y) / 2.f - 5.f));
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
