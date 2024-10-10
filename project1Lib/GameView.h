/**
 * @file GameView.h
 * @author Nicolas Roberts
 *
 *
 */
 
#ifndef GAMEVIEW_H
#define GAMEVIEW_H



class GameView : public wxWindow {
private:
    /// The game
    //Game mGame;


public:
    GameView();

    void OnPaint(wxPaintEvent& event);

    void Initialize(wxFrame *mainFrame);
};



#endif //GAMEVIEW_H
