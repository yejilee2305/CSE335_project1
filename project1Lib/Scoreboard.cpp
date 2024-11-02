/**
 * @file Scoreboard.cpp
 * @author Martin Sattam
 */

#include "pch.h"
#include "Game.h"
#include "Scoreboard.h"
#include <wx/graphics.h>
#include <wx/pen.h>
#include <wx/brush.h>

/**
 * @return the size of the scoreboard
 */
const wxSize ScoreboardSize(380, 100); ///< Size of the scoreboard box
const int SpacingScoresToInstructions = 40; ///< space between scores and instructions
const int SpacingInstructionLines = 17; ///< space between instruction lines
/**
 * @brief Constructor for Scoreboard.
 *
 * @param game Pointer to the Game instance associated with the scoreboard.
 * @param x X-coordinate for the scoreboard's position.
 * @param y Y-coordinate for the scoreboard's position.
 * @param goodScore The increment for the good score.
 * @param badScore The decrement for the bad score.
 * @param instructions Instruction text to be displayed on the scoreboard.
 */
Scoreboard::Scoreboard(Game* game, int x, int y, int goodScore, int badScore, wxString instructions)
    : Item(game, L""), mX(x), mY(y), mGame(game), mGoodScoreIncrement(goodScore), mBadScoreDecrement(badScore),
      mLevelScore(0), mGameScore(0)
{
    SetInstructions(instructions);
}
/**
 * @brief Resets the level score to zero.
 */
void Scoreboard::ResetLevelScore()
{
    mLevelScore = 0;
}
/**
 * @brief Adds the good score increment to the level score.
 */
void Scoreboard::AddGoodScore()
{
    mLevelScore += mGoodScoreIncrement;
}
/**
 * @brief Subtracts the bad score decrement from the level score.
 */
void Scoreboard::AddBadScore()
{
    mLevelScore -= mBadScoreDecrement;
}
/**
 * @brief Updates the game score by adding the level score to it.
 */
void Scoreboard::UpdateGameScore()
{
    mGameScore += mLevelScore;
}
/**
 * @brief Draws the scoreboard on the graphics context.
 *
 * @param graphics Shared pointer to the wxGraphicsContext where the scoreboard will be drawn.
 */
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
    int currentLevel = mGame->GetCurrentLevel();
    graphics->SetFont(scoreFont);
    graphics->DrawText(
        wxString::Format("Level: %d  Game: %d", currentLevel, mGameScore),
        mX + 10, mY + 10
    );

    // Draw the wrapped instructions
    graphics->SetFont(instructionFont);
    DrawWrappedText(graphics, wxString(mInstructions), mX + 10, mY + SpacingScoresToInstructions, 360);
}
/**
 * @brief Draws wrapped text within a specified width on the graphics context.
 *
 * @param graphics Shared pointer to the wxGraphicsContext used for drawing text.
 * @param text The text to wrap and draw.
 * @param x The starting X-coordinate.
 * @param y The starting Y-coordinate.
 * @param maxWidth The maximum width for the text line before wrapping.
 */
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
/**
 * @brief Sets the instructions text to be displayed on the scoreboard.
 *
 * @param instructions The instruction text to display.
 */
void Scoreboard::SetInstructions(const wxString& instructions)
{
    mInstructions = instructions;
}
/**
 * @brief Gets the current level score.
 *
 * @return int The level score.
 */
int Scoreboard::GetLevelScore() const
{
    return mLevelScore;
}
/**
 * @brief Gets the current game score.
 *
 * @return int The game score.
 */
int Scoreboard::GetGameScore() const
{
    return mGameScore;
}
/**
 * @brief Gets the X-coordinate of the scoreboard.
 *
 * @return int The X-coordinate.
 */
int Scoreboard::GetX() const
{
    return mX;
}
/**
 * @brief Gets the Y-coordinate of the scoreboard.
 *
 * @return int The Y-coordinate.
 */
int Scoreboard::GetY() const
{
    return mY;
}