/**
 * @file MainFrame.h
 * @author Zhi Lin
 *
 *
 */

#ifndef MAINFRAME_H
#define MAINFRAME_H


class MainFrame : public wxFrame
{
private:

public:
    void Initialize();
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnAddORGate(wxCommandEvent& event);
    void OnAddANDGate(wxCommandEvent& event);
    enum
    {
        ID_ORGate = 1001,
        ID_ANDGate = 1002,
        ID_NOTGate = 1003
    };
};


#endif //MAINFRAME_H
