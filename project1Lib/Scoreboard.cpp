/**
 * @file Scoreboard.cpp
 * @author Martin Sattam
 */
 
#include "Scoreboard.h"
#include <wx/graphics.h>
#include <wx/pen.h>
#include <wx/brush.h>

Scoreboard::Scoreboard(int x, int y, int goodScore, int badScore)
    : mX(x), mY(y), mGoodScoreIncrement(goodScore), mBadScoreDecrement(badScore), mLevelScore(0), mGameScore(0) {}

void Scoreboard::ResetLevelScore() {
 mLevelScore = 0;
}

void Scoreboard::AddGoodScore() {
 mLevelScore += mGoodScoreIncrement;
}

void Scoreboard::AddBadScore() {
 mLevelScore -= mBadScoreDecrement;
}

void Scoreboard::UpdateGameScore() {
 mGameScore += mLevelScore;
}

void Scoreboard::Draw(wxGraphicsContext* graphics) {

}

void Scoreboard::SetInstructions(const std::string& instructions) {
 mInstructions = instructions;
}

int Scoreboard::GetLevelScore() const {
 return mLevelScore;
}

int Scoreboard::GetGameScore() const {
 return mGameScore;
}

int Scoreboard::GetX() const {
 return mX;
}

int Scoreboard::GetY() const {
 return mY;
}