/**
 * @file MainFrame.cpp
 * @author Zhi Lin
 */

#include "pch.h"
#include "MainFrame.h"
#include "Gate.h"

void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Sparty's Boots", wxDefaultPosition, wxDefaultSize,
           wxFULL_REPAINT_ON_RESIZE | wxDEFAULT_FRAME_STYLE);

    auto menuBar = new wxMenuBar();
    auto gateMenu = new wxMenu;

    gateMenu->Append(ID_ORGate, "Add OR Gate");
    gateMenu->Append(ID_ANDGate, "Add AND Gate");
    gateMenu->Append(ID_NOTGate, "Add NOT Gate");

    menuBar->Append(gateMenu, "&Gates");
    SetMenuBar(menuBar);

    CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);

    Bind(wxEVT_MENU, &MainFrame::OnAddORGate, this, ID_ORGate);
    Bind(wxEVT_MENU, &MainFrame::OnAddANDGate, this, ID_ANDGate);
}
void MainFrame::OnAddORGate(wxCommandEvent& event)
{
    ORGate* orGate = new ORGate();
}

void MainFrame::OnAddANDGate(wxCommandEvent& event)
{
    ANDGate* andGate = new ANDGate();
}

