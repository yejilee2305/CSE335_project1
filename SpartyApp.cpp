/**
 * @file SpartyApp.cpp
 * @author Zhi Lin
 */

#include "pch.h"
#include "SpartyApp.h"
#include <MainFrame.h>

#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif


bool SpartyApp::OnInit()
{
#ifdef WIN32
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();


    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}
