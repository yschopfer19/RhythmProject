#include <iostream>
#include <SFML/Graphics.hpp>

#include "Note.h"

using namespace std;
using namespace sf;

Note::Note(float x, float y, Color color, int speed, int lane_Index, float spawn_time)
    : position(x, y), speed(speed), lane_Index(lane_Index), spawn_time(spawn_time)
{
    shape.setPosition({x, y});
    shape.setSize({130, 20});
    shape.setFillColor(Color(100, 200, 255));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(Color(200, 255, 255));
}

void Note::draw(RenderWindow &window) const
{
    // Draw shadow
    RectangleShape shadow(shape.getSize());
    shadow.setPosition({position.x + 2.f, position.y + 2.f});
    shadow.setFillColor(Color(0, 0, 0, 100));
    window.draw(shadow);

    // Draw main note
    window.draw(shape);

    // Draw highlight line
    RectangleShape highlight({shape.getSize().x, 2.f});
    highlight.setPosition({position.x, position.y + 2.f});
    highlight.setFillColor(Color(200, 255, 255, 200));
    window.draw(highlight);
}

void Note::update(float songtime)
{
    if (songtime < spawn_time)
        return;

    float timeSinceSpawn = songtime - spawn_time;
    position.y = -50.0f + speed * timeSinceSpawn;

    shape.setPosition(position);

    // Farbe je nach state ändern
    switch (state)
    {
    case NoteState::ACTIVE:
        shape.setFillColor(Color(100, 200, 255));
        break;
    case NoteState::HIT:
        shape.setFillColor(Color(150, 255, 200));
        shape.setOutlineColor(Color(200, 255, 220));
        break;
    case NoteState::MISS:
        shape.setFillColor(Color(255, 100, 100));
        shape.setOutlineColor(Color(255, 150, 150));
        break;
    default:
        break;
    }
}

Vector2f Note::getPosition() const
{
    return position;
}

int Note::getlaneIndex() const
{
    return lane_Index;
}

float Note::getSpawnTime() const
{
    return spawn_time;
}

NoteState Note::getState() const
{
    return this->state;
}

void Note::setState(NoteState state)
{
    this->state = state;
}
