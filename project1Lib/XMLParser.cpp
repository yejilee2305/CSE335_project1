/**
 * @file XMLParser.cpp
 * @author Yeji Lee
 */

#include "pch.h"
#include "XMLParser.h"
#include "Game.h"

using namespace std;

/**
 * Constructor
 * @param game The game to load levels into
 */
XMLParser::XMLParser(Game *game) : mGame(game)
{
}

/**
 * Loads in all the values from the XML file into the member variables in Game.
 * @param filename The filename of the XML file to be loaded.
 */
void XMLParser::Load(const wxString &filename)
{
    double virtualHeight;
    double virtualWidth;

    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox("Unable to load Game file");
        return;
    }
    mGame->Clear();

    auto root = xmlDoc.GetRoot();

    auto sizeString = root->GetAttribute("size", "0,0");
    sizeString.BeforeFirst(',').ToDouble(&virtualWidth);
    sizeString.AfterFirst(',').ToDouble(&virtualHeight);

    auto child = root->GetChildren();
    for(; child; child = child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"items")
        {
            auto node = child->GetChildren();
            //XmlItems(node);
        }
    }
    //mGame->SetVirtualWidth(virtualWidth);
    //mGame->SetVirtualHeight(virtualHeight);
}

//Add Function called XMLItems to load in the items