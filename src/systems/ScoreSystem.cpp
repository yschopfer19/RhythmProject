#include <iostream>
#include <SFML/Graphics.hpp>
#include "ScoreSystem.h"

using namespace std;
using namespace sf;

void ScoreSystem::addJudgement(Judgement judgement)
{
    switch (judgement)
    {
    case Judgement::PERFECT:
        score += 300;
        combo++;
        perfectCount++;
        break;
    case Judgement::GOOD:
        score += 100;
        combo++;
        goodCount++;
        break;
    case Judgement::MISS:
        combo = 0;  // Combo reset!
        missCount++;
        break;
    case Judgement::HOLD:
    case Judgement::RELEASE:
    case Judgement::NONE:
        return;
    default:
        break;
    }
    if (combo > maxCombo)
        maxCombo = combo;

    cout << JudgementSystem::judgementToString(judgement) 
         << " | Score: " << score 
         << " | maxCombo: " << maxCombo
         << " | Combo: " << combo << endl;
}

int ScoreSystem::getScore()
{
    return score;
}

int ScoreSystem::getCombo()
{
    return combo;
}

int ScoreSystem::getMaxCombo()
{
    return maxCombo;
}

void ScoreSystem::reset()
{
    this->combo = 0;
    this->maxCombo = 0;
    this->score = 0;
    this->perfectCount = 0;
    this->goodCount = 0;
    this->missCount = 0; 
}