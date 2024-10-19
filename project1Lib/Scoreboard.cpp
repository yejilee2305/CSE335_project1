/**
 * @file Scoreboard.cpp
 * @author Martin Sattam
 */

#include "Scoreboard.h"
#include <wx/graphics.h>
#include <wx/pen.h>
#include <wx/brush.h>

const wxSize ScoreboardSize(380, 100);
const int SpacingScoresToInstructions = 40;
const int SpacingInstructionLines = 17;

Scoreboard::Scoreboard(Game* game, int x, int y, int goodScore, int badScore)
    : Item(game, L""), mX(x + 160), mY(y), mGoodScoreIncrement(goodScore), mBadScoreDecrement(badScore),
      mLevelScore(0), mGameScore(0)
{
    mInstructions = "Level: 1 Game: 0\nMake Sparty kick all product from the conveyor that are not Izzo or Smith.";
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
        wxString::Format("Level: %d  Game: %d", 1, mGameScore),
        mX + 10, mY + 10
    );

    // Draw the wrapped instructions
    graphics->SetFont(instructionFont);
    DrawWrappedText(graphics, wxString(mInstructions), mX + 10, mY + SpacingScoresToInstructions, 360);
}

void Scoreboard::DrawWrappedText(std::shared_ptr<wxGraphicsContext> graphics, const wxString& text,
                                 int x, int y, int maxWidth)
{
    // Split the input text into words
    wxArrayString words = wxSplit(text, ' ');
    wxString currentLine;
    int currentY = y;

    // Variables to store the width and height of text
    double width, height;

    // Iterate through each word and build lines within the max width
    for (size_t i = 0; i < words.size(); ++i)
    {
        wxString testLine = currentLine + words[i] + " ";

        // Measure the width of the test line
        graphics->GetTextExtent(testLine, &width, &height);

        if (width > maxWidth)
        {
            // Draw the current line if it exceeds the width
            graphics->DrawText(currentLine, x, currentY);
            currentLine = words[i] + " "; // Start a new line with the current word
            currentY += SpacingInstructionLines; // Move to the next line
        }
        else
        {
            // If it fits, keep adding words to the current line
            currentLine = testLine;
        }
    }

    // Draw the last line
    if (!currentLine.IsEmpty())
    {
        graphics->DrawText(currentLine, x, currentY);
    }
}

void Scoreboard::SetInstructions(const std::string& instructions)
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
