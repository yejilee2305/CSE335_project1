/**
 * @file Scoreboard.cpp
 * @author Martin Sattam
 */

#include "pch.h"
#include "Scoreboard.h"
#include <wx/graphics.h>
#include <wx/pen.h>
#include <wx/brush.h>

const wxSize ScoreboardSize(380, 100);
const int SpacingScoresToInstructions = 40;
const int SpacingInstructionLines = 17;

Scoreboard::Scoreboard(Game* game, int x, int y, int goodScore, int badScore, wxString instructions)
    : Item(game, L""), mX(x), mY(y), mGoodScoreIncrement(goodScore), mBadScoreDecrement(badScore),
      mLevelScore(0), mGameScore(0)
{
    SetInstructions(instructions);
}

void Scoreboard::ResetLevelScore()
{
    mLevelScore = 0;
}

void Scoreboard::AddGoodScore()
{
    mLevelScore += mGoodScoreIncrement;
}

void Scoreboard::AddBadScore()
{
    mLevelScore -= mBadScoreDecrement;
}

void Scoreboard::UpdateGameScore()
{
    mGameScore += mLevelScore;
}

void Scoreboard::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Draw the scoreboard box
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->SetPen(wxPen(wxColour(0, 0, 0), 2));
    graphics->DrawRectangle(mX, mY, ScoreboardSize.GetWidth(), ScoreboardSize.GetHeight());

    // Set fonts for score and instructions
    auto scoreFont = graphics->CreateFont(25, L"Arial", wxFONTFLAG_BOLD, wxColour(24, 69, 59));
    auto instructionFont = graphics->CreateFont(15, L"Arial", wxFONTFLAG_BOLD, *wxBLACK);

    // Draw the scores at the top
    graphics->SetFont(scoreFont);
    graphics->DrawText(
        wxString::Format("Level: %d  Game: %d", 0, mGameScore),
        mX + 10, mY + 10
    );

    // Draw the wrapped instructions
    graphics->SetFont(instructionFont);
    DrawWrappedText(graphics, wxString(mInstructions), mX + 10, mY + SpacingScoresToInstructions, 360);
}

void Scoreboard::DrawWrappedText(std::shared_ptr<wxGraphicsContext> graphics, const wxString& text,
                                 int x, int y, int maxWidth)
{
    wxArrayString lines = wxSplit(text, '\n');

    double width, height;

    for (const auto& line : lines)
    {
        graphics->GetTextExtent(line, &width, &height);
        graphics->DrawText(line, x, y);
        y += height;
    }
}

void Scoreboard::SetInstructions(const wxString& instructions)
{
    mInstructions = instructions;
}

int Scoreboard::GetLevelScore() const
{
    return mLevelScore;
}

int Scoreboard::GetGameScore() const
{
    return mGameScore;
}

int Scoreboard::GetX() const
{
    return mX;
}

int Scoreboard::GetY() const
{
    return mY;
}