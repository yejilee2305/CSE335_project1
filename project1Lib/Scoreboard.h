/**
 * @file Scoreboard.h
 * @author Martin Sattam
 *
 *
 */
#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <string>
#include "wx/wx.h"
#include "pch.h"

class Scoreboard {
private:
 // Get position
 int mX;
 int mY;

 // Scores, incrementing and decreasing
 int mLevelScore;
 int mGameScore;
 int mGoodScoreIncrement; // Score goes up
 int mBadScoreDecrement; // Score goes down

 // Displays text for level goal
 std::string mInstructions;

public:
 // Constructor
 Scoreboard(int x, int y, int goodScore = 10, int badScore = 0);

 // Resets level score to zero
 void ResetLevelScore();

 // Adds to the level score for a correct action
 void AddGoodScore();

 // Removes from level score for an incorrect action
 void AddBadScore();

 // Updates the game score when the level is finished
 void UpdateGameScore();

 // Draws the scoreboard on the screen
 void Draw(wxGraphicsContext* graphics);

 // Sets the instructions text
 void SetInstructions(const std::string& instructions);

 // Getters for scores and position
 int GetLevelScore() const;
 int GetGameScore() const;
 int GetX() const;
 int GetY() const;
};

#endif // SCOREBOARD_H
