/**
 * @file Scoreboard.h
 * @author Martin Sattam
 *
 *
 */
#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <string>
#include <wx/graphics.h>
#include "Item.h"

class Scoreboard : public Item
{
private:
    int mX;
    int mY;
    int mLevelScore;
    int mGameScore;
    int mGoodScoreIncrement;
    int mBadScoreDecrement;
    wxString mInstructions;

public:
    Scoreboard(Game* game, int x, int y, int goodScore = 10, int badScore = 0, wxString instructions = "");
    void Accept(ItemVisitor* visitor) override { visitor->VisitScoreBoard(this); }

    void ResetLevelScore();
    void AddGoodScore();
    void AddBadScore();
    void UpdateGameScore();
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    void SetInstructions(const wxString& instructions);

    int GetLevelScore() const;
    int GetGameScore() const;
    int GetX() const;
    int GetY() const;

private:
    // Helper function to draw wrapped text.
    void DrawWrappedText(std::shared_ptr<wxGraphicsContext> graphics, const wxString& text,
                         int x, int y, int maxWidth);
};

#endif // SCOREBOARD_H
