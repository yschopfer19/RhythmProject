#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "NoteSystem.h"
#include "Note.h"
#include "Types.h"

using namespace std;
using namespace sf;

void NoteSystem::addNote(unique_ptr<Note> note)
{
    notes.push_back(move(note));
}

void NoteSystem::update(float songtime, const array<float, 4> &hitY)
{
    for (auto &note : notes)
    {
        if (note->getState() == NoteState::WAITING &&
            songtime >= note->getSpawnTime())
        {
            note->setState(NoteState::ACTIVE);
        }

        if (note->getState() == NoteState::ACTIVE || 
            note->getState() == NoteState::HELD || 
            note->getState() == NoteState::RELEASED)
        {
            note->update(songtime);

            int lane = note->getlaneIndex();

            if (note->getState() == NoteState::ACTIVE && 
                note->getPosition().y > hitY[lane] + 30)
            {
                note->setState(NoteState::MISS);
                pendingMisses++;
            }
        }
    }
}

void NoteSystem::draw(sf::RenderWindow &window)
{
    for (auto &note : notes)
    {
        if (note->getState() == NoteState::ACTIVE ||
            note->getState() == NoteState::HELD ||
            note->getState() == NoteState::RELEASED)
        {
            note->draw(window);
        }
    }
}

vector<unique_ptr<Note>> &NoteSystem::getNotes()
{
    return notes;
}

int NoteSystem::popMisses()
{
    int result = pendingMisses;
    pendingMisses = 0;
    return result;
}