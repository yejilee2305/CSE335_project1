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

    wxStopWatch mStopWatch;

    long mTime = 0;

    /// The game
    Game mGame;

    int mCurrentLevel = 0; ///< Current level of the game

    /// current item we are dragging
    std::shared_ptr<Item> mGrabbedItem;
    std::vector<std::shared_ptr<Gate>> mGates;
    std::shared_ptr<Gate> mGrabbedGate = nullptr;


public:
    GameView();
    void OnTimer(wxTimerEvent& event);

    void OnPaint(wxPaintEvent& event);

    void Initialize(wxFrame* mainFrame);

    void OnMouseMove(wxMouseEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);

    void OnLevelOption(wxCommandEvent& event);
    void OnDraw(wxGraphicsContext* gc, int width, int height);
    void OnAddORGate(wxCommandEvent& event);
    auto OnAddANDGate(wxCommandEvent& event) -> void;
    auto OnAddNOTGate(wxCommandEvent& event) -> void;
    auto OnAddSRFLipFlopGate(wxCommandEvent& event) -> void;
    auto OnAddDFLipFlopGate(wxCommandEvent& event) -> void;
    void AddGate(std::shared_ptr<Gate> gate);
};


#endif //GAMEVIEW_H
