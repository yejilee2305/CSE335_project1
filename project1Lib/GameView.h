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

    int mCurrentLevel = 0; ///< Current level of the game

    /// current item we are dragging
    std::shared_ptr<Item> mGrabbedItem;
    std::vector<std::shared_ptr<Gate>> mGates;

public:
    GameView();

    void OnPaint(wxPaintEvent& event);

    void Initialize(wxFrame* mainFrame);

    void OnMouseMove(wxMouseEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);

    void OnLevelOption(wxCommandEvent& event);
    void OnDraw(wxGraphicsContext* gc, int width, int height);
    void OnAddORGate(wxCommandEvent& event);
    auto OnAddANDGate(wxCommandEvent& event) -> void;
    void AddGate(std::shared_ptr<Gate> gate);
};


#endif //GAMEVIEW_H
