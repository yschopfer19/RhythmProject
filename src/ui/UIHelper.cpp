#include "UIHelper.h"
#include <vector>

using namespace sf;

void UIHelper::drawGradientRect(
    RenderWindow &window,
    Vector2f position,
    Vector2f size,
    Color colorTopLeft,
    Color colorTopRight,
    Color colorBottomLeft,
    Color colorBottomRight)
{
    // Create a 2x2 gradient texture
    std::vector<Color> gradientData(4);
    gradientData[0] = colorTopLeft;
    gradientData[1] = colorTopRight;
    gradientData[2] = colorBottomLeft;
    gradientData[3] = colorBottomRight;

    // Draw as 4 triangles
    ConvexShape quad(4);
    quad.setPoint(0, Vector2f(0, 0));
    quad.setPoint(1, Vector2f(size.x, 0));
    quad.setPoint(2, Vector2f(size.x, size.y));
    quad.setPoint(3, Vector2f(0, size.y));
    quad.setPosition(position);

    // Draw with color interpolation using RectangleShape with colors
    RectangleShape topLeft({size.x / 2, size.y / 2});
    topLeft.setPosition(position);
    topLeft.setFillColor(colorTopLeft);
    window.draw(topLeft);

    RectangleShape topRight({size.x / 2, size.y / 2});
    topRight.setPosition({position.x + size.x / 2, position.y});
    topRight.setFillColor(colorTopRight);
    window.draw(topRight);

    RectangleShape bottomLeft({size.x / 2, size.y / 2});
    bottomLeft.setPosition({position.x, position.y + size.y / 2});
    bottomLeft.setFillColor(colorBottomLeft);
    window.draw(bottomLeft);

    RectangleShape bottomRight({size.x / 2, size.y / 2});
    bottomRight.setPosition({position.x + size.x / 2, position.y + size.y / 2});
    bottomRight.setFillColor(colorBottomRight);
    window.draw(bottomRight);
}

void UIHelper::drawButton(
    RenderWindow &window,
    Vector2f position,
    Vector2f size,
    const Text &text,
    bool hovered,
    bool pressed,
    Color primaryColor,
    Color hoverColor,
    Color pressColor)
{
    // Draw shadow
    drawShadow(window, position, size, 4.f, Color(0, 0, 0, 80));

    // Determine button color based on state
    Color buttonColor = primaryColor;
    if (pressed)
    {
        buttonColor = pressColor;
        position.y += 2.f; // Pressed effect
    }
    else if (hovered)
    {
        buttonColor = hoverColor;
    }

    // Draw button
    RectangleShape button(size);
    button.setPosition(position);
    button.setFillColor(buttonColor);
    button.setOutlineColor(Color(255, 255, 255, 100));
    button.setOutlineThickness(1.5f);
    window.draw(button);

    // Draw glow on hover
    if (hovered && !pressed)
    {
        drawGlowEffect(window, position, size, hoverColor, 0.5f);
    }

    // Draw text
    window.draw(text);
}

void UIHelper::centerText(
    Text &text,
    Vector2f position,
    bool centerX,
    bool centerY)
{
    Rect<float> bounds = text.getLocalBounds();

    if (centerX)
    {
        text.setPosition(Vector2f(
            position.x - bounds.size.x / 2,
            text.getPosition().y));
    }
    if (centerY)
    {
        text.setPosition(Vector2f(
            text.getPosition().x,
            position.y - bounds.size.y / 2));
    }
}

void UIHelper::drawShadow(
    RenderWindow &window,
    Vector2f position,
    Vector2f size,
    float offset,
    Color color)
{
    RectangleShape shadow(size);
    shadow.setPosition({position.x + offset, position.y + offset});
    shadow.setFillColor(color);
    window.draw(shadow);
}

void UIHelper::drawGlowEffect(
    RenderWindow &window,
    Vector2f position,
    Vector2f size,
    Color glowColor,
    float intensity)
{
    for (int i = 0; i < 3; i++)
    {
        float expandSize = (3 - i) * 2.f;
        RectangleShape glow({size.x + expandSize, size.y + expandSize});
        glow.setPosition({position.x - expandSize / 2, position.y - expandSize / 2});
        glowColor.a = static_cast<uint8_t>(50 * intensity * (1 - i / 3.f));
        glow.setFillColor(Color::Transparent);
        glow.setOutlineColor(glowColor);
        glow.setOutlineThickness(1.f);
        window.draw(glow);
    }
}

void UIHelper::drawSeparator(
    RenderWindow &window,
    Vector2f start,
    Vector2f end,
    float thickness,
    Color color)
{
    RectangleShape separator({end.x - start.x, thickness});
    separator.setPosition(start);
    separator.setFillColor(color);
    window.draw(separator);
}
