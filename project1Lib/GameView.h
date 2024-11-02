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
    long mMessageStartTime = 0; ///< Time when the level message was displayed
    long mEndingMessageTime = 0 ; ///< The time displaying closing message

    /// The game
    Game mGame;

    int mCurrentLevel = 0; ///< Current level of the game

    /// current item we are dragging
    std::shared_ptr<Item> mGrabbedItem;
    std::shared_ptr<Gate> mGrabbedGate = nullptr;
    PinOutput* mSelectedOutputPin = nullptr;
    std::shared_ptr<Wire> mDraggingWire;
    PinInput* mSelectedInputPin = nullptr;
    bool mDisplayLevelMessage = false;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// The stopwatch that assists in animation
    wxStopWatch mStopWatch;

    /// The current time
    long mTime = 0;

public:
    GameView();
    void OnTimer(wxTimerEvent& event);

    void OnPaint(wxPaintEvent& event);

    void Initialize(wxFrame* mainFrame);

    void OnMouseMove(wxMouseEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);

    void OnLevelOption(wxCommandEvent& event);
    void OnAddORGate(wxCommandEvent& event);
    auto OnAddANDGate(wxCommandEvent& event) -> void;
    auto OnAddNOTGate(wxCommandEvent& event) -> void;
    auto OnAddSRFLipFlopGate(wxCommandEvent& event) -> void;
    auto OnAddDFLipFlopGate(wxCommandEvent& event) -> void;
    void AddGate(std::shared_ptr<Gate> gate);
    void ToggleControlPoints();
    void DisplayLevelMessage(int level);
    /**
     * Getter for Game
     * @return The Game
     */
    Game* GetGame() { return &mGame; }
};


#endif //GAMEVIEW_H
