/**
 * @file MainFrame.h
 * @author Zhi Lin
 *
 *
 */

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>

class GameView;

class MainFrame : public wxFrame
{
private:
    /// View class for our Game
    GameView *mGameView;

public:
    void Initialize();
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
    void OnAddORGate(wxCommandEvent& event);
    void OnAddANDGate(wxCommandEvent& event);
    void OnAddNOTGate(wxCommandEvent& event);
    void OnAddSRFlipFlopGate(wxCommandEvent& event);

    enum
    {
        ID_ORGate = 1001,
        ID_ANDGate = 1002,
        ID_NOTGate = 1003
    };
};


#endif //MAINFRAME_H
