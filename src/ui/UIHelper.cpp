#include "UIHelper.h"

#include <SFML/Graphics.hpp>

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
    // Echter interpolierter Farbverlauf statt vier Rechtecken
    VertexArray vertices(PrimitiveType::Triangles, 6);

    const Vector2f topLeft = position;
    const Vector2f topRight = {
        position.x + size.x,
        position.y};

    const Vector2f bottomLeft = {
        position.x,
        position.y + size.y};

    const Vector2f bottomRight = {
        position.x + size.x,
        position.y + size.y};

    // Erstes Dreieck
    vertices[0] = Vertex{topLeft, colorTopLeft};
    vertices[1] = Vertex{topRight, colorTopRight};
    vertices[2] = Vertex{bottomRight, colorBottomRight};

    // Zweites Dreieck
    vertices[3] = Vertex{topLeft, colorTopLeft};
    vertices[4] = Vertex{bottomRight, colorBottomRight};
    vertices[5] = Vertex{bottomLeft, colorBottomLeft};

    window.draw(vertices);
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
    // Dezenter Schatten
    drawShadow(
        window,
        position,
        size,
        5.f,
        Color(0, 0, 0, 65));

    Color buttonColor = primaryColor;

    if (pressed)
    {
        buttonColor = pressColor;
        position.y += 2.f;
    }
    else if (hovered)
    {
        buttonColor = hoverColor;
    }

    RectangleShape button(size);

    button.setPosition(position);
    button.setFillColor(buttonColor);

    // Dünne Border statt dickem "Game UI"-Outline
    button.setOutlineThickness(1.f);

    if (hovered)
    {
        button.setOutlineColor(
            Color(100, 200, 255, 190));
    }
    else
    {
        button.setOutlineColor(
            Color(255, 255, 255, 30));
    }

    window.draw(button);

    // Glow nur sehr subtil
    if (hovered && !pressed)
    {
        drawGlowEffect(
            window,
            position,
            size,
            Color(100, 200, 255),
            0.35f);
    }

    window.draw(text);
}

void UIHelper::centerText(
    Text &text,
    Vector2f position,
    bool centerX,
    bool centerY)
{
    const Rect<float> bounds =
        text.getLocalBounds();

    Vector2f newPosition =
        text.getPosition();

    if (centerX)
    {
        newPosition.x =
            position.x - bounds.position.x - bounds.size.x / 2.f;
    }

    if (centerY)
    {
        newPosition.y =
            position.y - bounds.position.y - bounds.size.y / 2.f;
    }

    text.setPosition(newPosition);
}

void UIHelper::drawShadow(
    RenderWindow &window,
    Vector2f position,
    Vector2f size,
    float offset,
    Color color)
{
    RectangleShape shadow(size);

    shadow.setPosition({position.x + offset,
                        position.y + offset});

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
    // Nur zwei sehr dezente Glow-Layer
    for (int i = 0; i < 2; ++i)
    {
        const float expansion =
            3.f + static_cast<float>(i) * 3.f;

        RectangleShape glow({size.x + expansion * 2.f,
                             size.y + expansion * 2.f});

        glow.setPosition({position.x - expansion,
                          position.y - expansion});

        glow.setFillColor(Color::Transparent);

        const float alphaFactor =
            (i == 0) ? 40.f : 18.f;

        glowColor.a = static_cast<uint8_t>(
            alphaFactor * intensity);

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
    const float width =
        end.x - start.x;

    RectangleShape separator({width,
                              thickness});

    separator.setPosition(start);
    separator.setFillColor(color);

    window.draw(separator);
}