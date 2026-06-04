#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "JudgementSystem.h"

class ScoreSystem
{
public:
    void addJudgement(Judgement judgement);

    int getScore();
    int getCombo();
    int getMaxCombo();
    void reset();

private:
    int combo = 0;
    int score = 0;
    int maxCombo = 0;
    int perfectCount = 0;
    int goodCount = 0;
    int missCount = 0;
};
