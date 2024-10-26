/**
 * @file MainFrame.cpp
 * @author Zhi Lin
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"
#include "ids.h"

void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Sparty's Boots",
        wxDefaultPosition, wxSize(1000, 800),
        wxFULL_REPAINT_ON_RESIZE | wxDEFAULT_FRAME_STYLE);

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer(wxVERTICAL);

    mGameView = new GameView();
    mGameView->Initialize(this);

    // Add it to the sizer
    sizer->Add(mGameView, 1, wxEXPAND | wxALL);

    // Set the sizer for this frame
    SetSizer(sizer);

    // Layout (place) the child windows.
    Layout();

    auto menuBar = new wxMenuBar();
    auto fileMenu = new wxMenu();
    auto helpMenu = new wxMenu();
    auto levelMenu = new wxMenu();
    auto gateMenu = new wxMenu();

    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");
    menuBar->Append(levelMenu, "&Level");
    menuBar->Append(gateMenu, "&Gates");
    SetMenuBar(menuBar);
    auto viewMenu = new wxMenu();

    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
    levelMenu->Append(IDM_LEVEL0, L"Level 0", L"Select Level 0");
    levelMenu->Append(IDM_LEVEL1, L"Level 1", L"Select Level 1");
    levelMenu->Append(IDM_LEVEL2, L"Level 2", L"Select Level 2");
    levelMenu->Append(IDM_LEVEL3, L"Level 3", L"Select Level 3");
    levelMenu->Append(IDM_LEVEL4, L"Level 4", L"Select Level 4");
    levelMenu->Append(IDM_LEVEL5, L"Level 5", L"Select Level 5");
    levelMenu->Append(IDM_LEVEL6, L"Level 6", L"Select Level 6");
    levelMenu->Append(IDM_LEVEL7, L"Level 7", L"Select Level 7");
    levelMenu->Append(IDM_LEVEL8, L"Level 8", L"Select Level 8");
    gateMenu->Append(ID_ORGate, "Add OR Gate");
    gateMenu->Append(ID_ANDGate, "Add AND Gate");
    gateMenu->Append(ID_NOTGate, "Add NOT Gate");
    gateMenu->Append(IDM_SRFLIP_GATE, "Add SR-Flip Flop Gate");
    gateMenu->Append(IDM_DRFLIP_GATE, "Add D-Flip Flop Gate");
    mControlPointsMenuItem = viewMenu->AppendCheckItem(wxID_ANY, "Show Control Points", "Toggle display of Bézier curve control points");

    menuBar->Append(viewMenu, "&View");
    CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);

    Bind(wxEVT_MENU, &MainFrame::OnAddORGate, this, ID_ORGate);
    Bind(wxEVT_MENU, &MainFrame::OnAddANDGate, this, ID_ANDGate);
    Bind(wxEVT_MENU, &MainFrame::OnAddNOTGate, this, ID_NOTGate);
    Bind(wxEVT_MENU, &MainFrame::OnAddSRFlipFlopGate, this, IDM_SRFLIP_GATE);
    Bind(wxEVT_MENU, &MainFrame::OnAddDFlipFlopGate, this, IDM_DRFLIP_GATE);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
    Bind(wxEVT_MENU, &MainFrame::OnToggleControlPoints, this, mControlPointsMenuItem->GetId());
}
void MainFrame::OnToggleControlPoints(wxCommandEvent& event)
{
    mGameView->ToggleControlPoints();
    mGameView->Refresh();
}
void MainFrame::OnAddORGate(wxCommandEvent& event)
{
    auto orGate = std::make_shared<ORGate>();
    orGate->SetPosition(350, 250); // Set initial position
    mGameView->AddGate(orGate); // Add the gate to the view
}

void MainFrame::OnAddANDGate(wxCommandEvent& event)
{
    auto andGate = std::make_shared<ANDGate>();
    andGate->SetPosition(400, 300); // Set initial position
    mGameView->AddGate(andGate); // Add the gate to the view
}
void MainFrame::OnAddNOTGate(wxCommandEvent& event)
{
    auto notGate = std::make_shared<NOTGate>();
    notGate->SetPosition(320, 240); // Set initial position
    mGameView->AddGate(notGate); // Add the gate to the view
}
void MainFrame::OnAddSRFlipFlopGate(wxCommandEvent& event)
{
    auto srFlipFlop = std::make_shared<SRFlipFlopGate>();
    srFlipFlop->SetPosition(290, 230); // Set initial position
    mGameView->AddGate(srFlipFlop); // Add the gate to the view
}
void MainFrame::OnAddDFlipFlopGate(wxCommandEvent& event)
{
    // Create an D gate and set its initial position
    auto dFlipFlop = std::make_shared<DFlipFlopGate>();
    dFlipFlop->SetPosition(295, 190);

    // Add the D gate to the game
    mGameView->AddGate(dFlipFlop);
}

/**
 * Exit menu option handlers
 * @param event The Exit event
 */
void MainFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

/**
 * Handles About item event from menu.
 * Method displays a dialog showing info about application.
 * @param event The event object associated with the About action.
 */
void MainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox(L"Welcome to the Game!",
                 L"About Sparty's Boots",
                 wxOK,
                 this);
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}
