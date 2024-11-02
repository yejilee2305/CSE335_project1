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


/**
 * class for the scoreboard
 * 
 */
class Scoreboard : public Item
{
private:
    int mX; /// X-coordinate of the scoreboard position.
    int mY; /// Y-coordinate of the scoreboard position.
    int mLevelScore; /// Score for the current level.
    int mGameScore; /// Total game score.
    int mGoodScoreIncrement; /// Points added for a good score.
    int mBadScoreDecrement; /// Points subtracted for a bad score.
    wxString mInstructions; /// Instructions text to be displayed.
    Game* mGame; /// Pointer to the associated Game instance.

public:
    /**
     * @brief Constructor for Scoreboard.
     *
     * @param game Pointer to the Game instance.
     * @param x X-coordinate for the scoreboard's position.
     * @param y Y-coordinate for the scoreboard's position.
     * @param goodScore Score increment for good actions (default is 10).
     * @param badScore Score decrement for bad actions (default is 0).
     * @param instructions Instruction text to display on the scoreboard (default is empty).
     */
    Scoreboard(Game* game, int x, int y, int goodScore = 10, int badScore = 0, wxString instructions = "");

    /**
     * @brief Accepts a visitor for this scoreboard.
     *
     * @param visitor Pointer to the ItemVisitor.
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitScoreBoard(this); }

    /**
     * @brief Resets the level score to zero.
     */
    void ResetLevelScore();

    /**
     * @brief Adds the good score increment to the level score.
     */
    void AddGoodScore();

    /**
     * @brief Subtracts the bad score decrement from the level score.
     */
    void AddBadScore();

    /**
     * @brief Updates the game score by adding the current level score.
     */
    void UpdateGameScore();

    /**
     * @brief Draws the scoreboard.
     *
     * @param graphics Shared pointer to the wxGraphicsContext where the scoreboard is drawn.
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * @brief Sets the instructions text to be displayed on the scoreboard.
     *
     * @param instructions The instruction text.
     */
    void SetInstructions(const wxString& instructions);

    /**
     * @brief Gets the current level score.
     *
     * @return int The level score.
     */
    int GetLevelScore() const;

    /**
     * @brief Gets the current game score.
     *
     * @return int The game score.
     */
    int GetGameScore() const;

    /**
     * @brief Gets the X-coordinate of the scoreboard.
     *
     * @return int The X-coordinate.
     */
    int GetX() const;

    /**
     * @brief Gets the Y-coordinate of the scoreboard.
     *
     * @return int The Y-coordinate.
     */
    int GetY() const;

private:
    /**
     * @brief Helper function to draw wrapped text within a specified width.
     *
     * @param graphics Shared pointer to the wxGraphicsContext used for drawing.
     * @param text The text to wrap and display.
     * @param x Starting X-coordinate.
     * @param y Starting Y-coordinate.
     * @param maxWidth The maximum width for each line before wrapping.
     */
    void DrawWrappedText(std::shared_ptr<wxGraphicsContext> graphics, const wxString& text,
                         int x, int y, int maxWidth);
};

#endif // SCOREBOARD_H
