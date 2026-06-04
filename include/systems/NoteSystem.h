#pragma once

#include <array>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Types.h"
#include "Note.h"

using namespace std;
using namespace sf;

class NoteSystem
{
public:
    void addNote(unique_ptr<Note> note);

    void update(float songtime, const array<float, 4> &hitY);

    void draw(RenderWindow &window);

    vector<unique_ptr<Note>> &getNotes();

    int popMisses();

    void reset();

private:
    vector<unique_ptr<Note>> notes;
    int pendingMisses = 0;
};