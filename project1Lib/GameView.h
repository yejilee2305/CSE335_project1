/**
 * @file GameView.h
 * @author Nicolas Roberts
 *
 *  Class that implements the child window our program draws in.
 */

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "Game.h"

/**
* View class for our game
*/
class GameView : public wxWindow
{
private:
    /// The timer that allows for animation
    wxTimer mTimer;

    /// The game
    Game mGame;

    int mCurrentLevel = 1; ///< Current level of the game

    /// current item we are dragging
    std::shared_ptr<Item> mGrabbedItem;

public:
    GameView();

    void OnPaint(wxPaintEvent& event);

    void Initialize(wxFrame* mainFrame);

    void OnMouseMove(wxMouseEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
};


#endif //GAMEVIEW_H
