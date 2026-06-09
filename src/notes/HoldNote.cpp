#include <iostream>
#include <SFML/Graphics.hpp>

#include "HoldNote.h"

using namespace std;
using namespace sf;

HoldNote::HoldNote(float x, float y, Color color, int speed, int lane_Index, float spawn_time, float note_length)
    : Note(x, y, color, speed, lane_Index, spawn_time), note_length(note_length), hold_end_y(0.0f)
{
    shape.setSize({130, note_length});
    // Hold notes have different colors
    shape.setFillColor(Color(255, 150, 100));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(Color(255, 200, 150));
}

void HoldNote::update(float songtime)
{
    if (state == NoteState::HELD)
    {
        if (lastTime < 0.0f)
            lastTime = songtime;

        float deltatime = songtime - lastTime;
        lastTime = songtime;

        note_length -= speed * deltatime;

        if (note_length <= 0.0f)
        {
            note_length = 0.0f;
            setState(NoteState::HIT);
        }

        position.y = hold_end_y - note_length;

        shape.setSize({shape.getSize().x, note_length});
        shape.setPosition(position);

        return;
    }
    else
    {
        if (songtime < spawn_time)
            return;

        float timeSinceSpawn = songtime - spawn_time;
        float bottomY = -50.0f + speed * timeSinceSpawn; // unteres Ende
        position.y = bottomY - note_length;              // oberes Ende

        shape.setSize({shape.getSize().x, note_length});
        shape.setPosition(position);
    }
}

float HoldNote::getNoteLength() const
{
    return this->note_length;
}

void HoldNote::onPress(float hitzoneY, Judgement &outJudgement)
{
    if (getState() != NoteState::ACTIVE)
        return;

    float distance = abs((position.y + note_length) - hitzoneY);

    if (distance < 22.0f)
    {
        hold_end_y = position.y + note_length;
        setState(NoteState::HELD);
        outJudgement = Judgement::PERFECT;
    }
    else if (distance < 35.0f)
    {
        hold_end_y = position.y + note_length;
        setState(NoteState::HELD);
        outJudgement = Judgement::GOOD;
    }
    else
    {
        setState(NoteState::MISS);
        outJudgement = Judgement::MISS;
    }
}

void HoldNote::onRelease(float hitzoneY, Judgement &outJudgement)
{
    if (getState() != NoteState::HELD)
        return;

    float distance = abs(position.y - hitzoneY);

    if (distance < 22.0f)
    {
        setState(NoteState::HIT);
        outJudgement = Judgement::PERFECT;
    }
    else if (distance < 35.0f)
    {
        setState(NoteState::HIT);
        outJudgement = Judgement::GOOD;
    }
    else
    {
        setState(NoteState::MISS);
        outJudgement = Judgement::MISS;
    }
}
