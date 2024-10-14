/**
 * @file SpartyApp.cpp
 * @author Zhi Lin
 */

#include "pch.h"
#include "SpartyApp.h"
#include <MainFrame.h>
#include <XMLParser.h>


bool SpartyApp::OnInit()
{

    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();


    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    XMLParser parser;
    parser.ParseConfiguration("config.xml");

    return true;
}
