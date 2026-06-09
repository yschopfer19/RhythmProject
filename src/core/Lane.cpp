#include <SFML/Graphics.hpp>

#include "Lane.h"

using namespace sf;

Lane::Lane(float x, float y, float width, float height, Color color_lane, Color color_hitzone)
    : position_hitzone(x, y + height - 20),
      position_lane(x, y),
      size_lane(width, height),
      color_lane_base(color_lane),
      color_hitzone_base(color_hitzone)
{
    shape_lane.setPosition({position_lane});
    shape_lane.setSize({width, height});
    shape_lane.setFillColor(Color(30, 40, 70, 200)); // Dunklere base farbe
    shape_lane.setOutlineThickness(2.f);
    shape_lane.setOutlineColor(Color(100, 150, 200, 150));

    shape_hitzone.setPosition({position_hitzone});
    shape_hitzone.setSize({width, 20});
    shape_hitzone.setFillColor(color_hitzone);
    shape_hitzone.setOutlineThickness(2.f);
    shape_hitzone.setOutlineColor(Color(200, 255, 255));
}

void Lane::draw(RenderWindow &window) const
{
    window.draw(shape_lane);
    window.draw(shape_hitzone);
}

void Lane::drawEnhanced(RenderWindow &window, bool active) const
{
    // Draw Lane background with gradient effect
    RectangleShape laneBackground(size_lane);
    laneBackground.setPosition(position_lane);
    if (active)
    {
        // Aktivierte Lane hat hellere Farbe
        laneBackground.setFillColor(Color(50, 80, 120, 220));
        laneBackground.setOutlineColor(Color(150, 200, 255, 200));
    }
    else
    {
        laneBackground.setFillColor(Color(30, 40, 70, 200));
        laneBackground.setOutlineColor(Color(100, 150, 200, 150));
    }
    laneBackground.setOutlineThickness(2.f);
    window.draw(laneBackground);

    // Draw inner gradient lines
    RectangleShape gradientLine1({size_lane.x, 1.f});
    gradientLine1.setPosition({position_lane.x, position_lane.y + 10.f});
    gradientLine1.setFillColor(Color(100, 150, 200, 80));
    window.draw(gradientLine1);

    RectangleShape gradientLine2({size_lane.x, 1.f});
    gradientLine2.setPosition({position_lane.x, position_lane.y + size_lane.y - 30.f});
    gradientLine2.setFillColor(Color(100, 150, 200, 80));
    window.draw(gradientLine2);

    // Draw Hitzone with glow
    window.draw(shape_hitzone);

    if (active)
    {
        // Glow effect when lane is active
        RectangleShape hitZoneGlow(shape_hitzone.getSize());
        hitZoneGlow.setPosition(position_hitzone);
        hitZoneGlow.setFillColor(Color::Transparent);
        hitZoneGlow.setOutlineColor(Color(200, 255, 255, 150));
        hitZoneGlow.setOutlineThickness(2.f);
        hitZoneGlow.setScale({1.1f, 1.1f});
        window.draw(hitZoneGlow);
    }
}

Vector2f Lane::getHitzonePosition() const
{
    return position_hitzone;
}

Vector2f Lane::getLanePosition() const
{
    return position_lane;
}

Vector2f Lane::getLaneSize() const
{
    return size_lane;
}