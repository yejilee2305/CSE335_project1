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

    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
    levelMenu->Append(IDM_LEVEL0, L"Level 0", L"Select Level 0");
    levelMenu->Append(IDM_LEVEL1, L"Level 1", L"Select Level 1");
    levelMenu->Append(IDM_LEVEL2, L"Level 2", L"Select Level 2");
    levelMenu->Append(IDM_LEVEL3, L"Level 3", L"Select Level 3");
    gateMenu->Append(ID_ORGate, "Add OR Gate");
    gateMenu->Append(ID_ANDGate, "Add AND Gate");
    gateMenu->Append(ID_NOTGate, "Add NOT Gate");
    SetMenuBar(menuBar);
    CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);

    Bind(wxEVT_MENU, &MainFrame::OnAddORGate, this, ID_ORGate);
    Bind(wxEVT_MENU, &MainFrame::OnAddANDGate, this, ID_ANDGate);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
}

void MainFrame::OnAddORGate(wxCommandEvent& event)
{
    auto orGate = std::make_shared<ORGate>();
    orGate->SetPosition(100, 100); // Set initial position
    mGameView->AddGate(orGate); // Add the gate to the view
}

void MainFrame::OnAddANDGate(wxCommandEvent& event)
{
    auto andGate = std::make_shared<ANDGate>();
    andGate->SetPosition(200, 100); // Set initial position
    mGameView->AddGate(andGate); // Add the gate to the view
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
