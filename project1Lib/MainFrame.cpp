/**
 * @file MainFrame.cpp
 * @author Zhi Lin
 */

#include "pch.h"
#include "MainFrame.h"
#include "Gate.h"
#include "GameView.h"

void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Sparty's Boots", wxDefaultPosition, wxSize(1000, 800),
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
    auto gateMenu = new wxMenu();
    auto fileMenu = new wxMenu();

    gateMenu->Append(ID_ORGate, "Add OR Gate");
    gateMenu->Append(ID_ANDGate, "Add AND Gate");
    gateMenu->Append(ID_NOTGate, "Add NOT Gate");


    menuBar->Append(gateMenu, "&Gates");
    menuBar->Append(fileMenu, "&File");

    fileMenu->Append(wxFD_OPEN, "Load File");

    SetMenuBar(menuBar);
    CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);

    Bind(wxEVT_MENU, &MainFrame::OnAddORGate, this, ID_ORGate);
    Bind(wxEVT_MENU, &MainFrame::OnAddANDGate, this, ID_ANDGate);
    Bind(wxEVT_MENU, &MainFrame::OnFileOpen, this, wxFD_OPEN);
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

void MainFrame::OnFileOpen(wxCommandEvent& event)
{
    //    wxFileDialog loadFileDialog(this, L"Load Game file", L"", L"",
    //        L"Sparty Files (*.sparty)|*.sparty",wxFD_OPEN);
    //    if (loadFileDialog.ShowModal() == wxID_CANCEL)
    //    {
    //        return;
    //    }
    //    auto filename = loadFileDialog.GetPath();
    //mSparty.Load(filename);
    //    Refresh();
}
