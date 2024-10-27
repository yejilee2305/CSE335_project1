/**
 * @file XMLParser.cpp
 * @author Yeji Lee
 * @author Nicolas Roberts
 */

#include "pch.h"
#include "XMLParser.h"

#include "Beam.h"
#include "Game.h"
#include "Sensor.h"
#include "Conveyor.h"
#include "Scoreboard.h"

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
    int virtualHeight;
    int virtualWidth;

    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox("Unable to load Game file");
        return;
    }
    mGame->Clear();

    auto root = xmlDoc.GetRoot();

    auto sizeString = root->GetAttribute("size", "0,0");
    sizeString.BeforeFirst(',').ToInt(&virtualWidth);
    sizeString.AfterFirst(',').ToInt(&virtualHeight);

    auto child = root->GetChildren();
    for(; child; child = child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"items")
        {
            auto node = child->GetChildren();
            XmlItems(node);
        }
    }
    mGame->SetVirtualWidth(virtualWidth);
    mGame->SetVirtualHeight(virtualHeight);
}

/**
 * Handle a node of type item.
 * @param node Xml node
 */
void XMLParser::XmlItems(wxXmlNode* node)
{
    for(; node; node = node->GetNext())
    {
        shared_ptr<Item> item;
        auto name = node->GetName();
        if (name == L"sensor")
        {
            int x = 0, y = 0;
            node->GetAttribute(L"x", "0").ToInt(&x);
            node->GetAttribute(L"y", "0").ToInt(&y);
            item = make_shared<Sensor>(mGame, x, y, x, y);
        }
        else if (name == L"conveyor")
        {
            int x = 0, y = 0, speed = 0, height = 0;
            wxString panelStr;


            node->GetAttribute(L"x", "0").ToInt(&x);
            node->GetAttribute(L"y", "0").ToInt(&y);
            node->GetAttribute(L"speed", "0").ToInt(&speed);
            node->GetAttribute(L"height", "0").ToInt(&height);
            panelStr = node->GetAttribute(L"panel", "0,0");

            int panelX = 0, panelY = 0;
            panelStr.BeforeFirst(',').ToInt(&panelX);
            panelStr.AfterFirst(',').ToInt(&panelY);

            wxPoint panelPnt(panelX, panelY);

            item = make_shared<Conveyor>(mGame, x, y, speed, height, panelPnt);
        }
        else if (name == L"scoreboard")
        {
            int x = 0, y = 0, goodScore = 0, badScore = 0;

            node->GetAttribute(L"x", "0").ToInt(&x);
            node->GetAttribute(L"y", "0").ToInt(&y);
            node->GetAttribute(L"good", "0").ToInt(&goodScore);
            node->GetAttribute(L"bad", "0").ToInt(&badScore);

            wxString instructions = node->GetNodeContent().Trim(true).Trim(false);

            item = make_shared<Scoreboard>(mGame, x, y, goodScore, badScore);
        }
        else if (name == L"beam")
        {
            int x = 0, y = 0, sender = 0;

            node->GetAttribute(L"x", "0").ToInt(&x);
            node->GetAttribute(L"y", "0").ToInt(&y);
            node->GetAttribute(L"sender", "0").ToInt(&sender);

            item = make_shared<Beam>(mGame, x, y, sender);
        }

        if(item != nullptr)
        {
            item->XmlLoad(node);
            mGame->AddItem(item);
        }
    }
}
