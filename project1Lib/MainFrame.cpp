/**
 * @file MainFrame.cpp
 * @author Zhi Lin
 */

#include "pch.h"
#include "MainFrame.h"

void MainFrame::Initialize()
{
    // adding wxDEFAULT_FRAME_STYLE might break the virtual pixel, not sure yet... ⚠⚠⚠
    Create(nullptr, wxID_ANY, L"Sparty's Boots", wxDefaultPosition, wxDefaultSize,
           wxFULL_REPAINT_ON_RESIZE | wxDEFAULT_FRAME_STYLE);

    auto menuBar = new wxMenuBar();
    SetMenuBar(menuBar);
    CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);
}
