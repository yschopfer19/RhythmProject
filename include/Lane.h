#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Lane
{
public:
    Lane(float x, float y, float width, float height, Color color_lane, Color color_hitzone);

    void draw(RenderWindow &window) const;
    void drawEnhanced(RenderWindow &window, bool active = false) const;

    Vector2f getHitzonePosition() const;
    Vector2f getLanePosition() const;
    Vector2f getLaneSize() const;

private:
    RectangleShape shape_lane;
    RectangleShape shape_hitzone;
    Vector2f position_hitzone;
    Vector2f position_lane;
    Vector2f size_lane;
    Color color_lane_base;
    Color color_hitzone_base;
};