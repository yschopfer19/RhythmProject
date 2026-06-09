#pragma once

#include <SFML/Graphics.hpp>

class UIHelper
{
public:
    // Gradient Rectangle Shapes
    static void drawGradientRect(
        sf::RenderWindow &window,
        sf::Vector2f position,
        sf::Vector2f size,
        sf::Color colorTopLeft,
        sf::Color colorTopRight,
        sf::Color colorBottomLeft,
        sf::Color colorBottomRight);

    // Styled Button mit Textur und Schatten
    static void drawButton(
        sf::RenderWindow &window,
        sf::Vector2f position,
        sf::Vector2f size,
        const sf::Text &text,
        bool hovered,
        bool pressed,
        sf::Color primaryColor = sf::Color(70, 130, 180),
        sf::Color hoverColor = sf::Color(100, 160, 220),
        sf::Color pressColor = sf::Color(50, 100, 150));

    // Zentrierter Text
    static void centerText(
        sf::Text &text,
        sf::Vector2f position,
        bool centerX = true,
        bool centerY = true);

    // Button Shadow
    static void drawShadow(
        sf::RenderWindow &window,
        sf::Vector2f position,
        sf::Vector2f size,
        float offset = 3.f,
        sf::Color color = sf::Color(0, 0, 0, 100));

    // Animated Glow Effect
    static void drawGlowEffect(
        sf::RenderWindow &window,
        sf::Vector2f position,
        sf::Vector2f size,
        sf::Color glowColor,
        float intensity);

    // Modern Separator Line
    static void drawSeparator(
        sf::RenderWindow &window,
        sf::Vector2f start,
        sf::Vector2f end,
        float thickness = 2.f,
        sf::Color color = sf::Color(100, 100, 100));
};
