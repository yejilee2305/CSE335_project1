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
    auto fileMenu = new wxMenu;

    gateMenu->Append(ID_ORGate, "Add OR Gate");
    gateMenu->Append(ID_ANDGate, "Add AND Gate");
    gateMenu->Append(ID_NOTGate, "Add NOT Gate");


    menuBar->Append(gateMenu, "&Gates");
    SetMenuBar(menuBar);

    fileMenu->Append(wxFD_OPEN, "Load File");

    CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);

    Bind(wxEVT_MENU, &MainFrame::OnAddORGate, this, ID_ORGate);
    Bind(wxEVT_MENU, &MainFrame::OnAddANDGate, this, ID_ANDGate);
    Bind(wxEVT_MENU, &MainFrame::OnFileOpen, this, wxFD_OPEN);
}
void MainFrame::OnAddORGate(wxCommandEvent& event)
{
    ORGate* orGate = new ORGate();
}

void MainFrame::OnAddANDGate(wxCommandEvent& event)
{
    ANDGate* andGate = new ANDGate();
}

void MainFrame::OnFileOpen(wxCommandEvent& event)
{
    wxFileDialog loadFileDialog(this, L"Load Aquarium file", L"", L"",
        L"Sparty Files (*.sparty)|*.sparty",wxFD_OPEN);
    if (loadFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }
    auto filename = loadFileDialog.GetPath();
    //mSparty.Load(filename);
    Refresh();
}
