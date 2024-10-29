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
#include "Product.h"

using namespace std;

/**
 * Constructor
 * @param game The game to load levels into
 */
XMLParser::XMLParser(Game* game) : mGame(game)
{
}

/**
 * Loads in all the values from the XML file into the member variables in Game.
 * @param filename The filename of the XML file to be loaded.
 */
void XMLParser::Load(const wxString& filename)
{
    int virtualHeight;
    int virtualWidth;

    wxXmlDocument xmlDoc;
    if (!xmlDoc.Load(filename))
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
    for (; child; child = child->GetNext())
    {
        auto name = child->GetName();
        if (name == L"items")
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
    for (; node; node = node->GetNext())
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

            auto conveyor = make_shared<Conveyor>(mGame, x, y, speed, height, panelPnt);
            conveyor->XmlLoad(node);
            mGame->AddItem(conveyor);

            auto productNode = node->GetChildren();
            for (; productNode; productNode = productNode->GetNext())
            {
                if (productNode->GetName() == L"product")
                {
                    wxString placementStr = productNode->GetAttribute(L"placement", L"0");
                    int placement = 0;
                    if (placementStr.StartsWith(L"+"))
                    {
                        placementStr = placementStr.Mid(1);
                        placementStr.ToInt(&placement);
                    }
                    else
                    {
                        placementStr.ToInt(&placement);
                    }

                    // shape
                    wxString shapeStr = productNode->GetAttribute(L"shape", L"square");
                    Product::Properties shape;
                    if (shapeStr == L"square")
                        shape = Product::Properties::Square;
                    else if (shapeStr == L"circle")
                        shape = Product::Properties::Circle;
                    else if (shapeStr == L"diamond")
                        shape = Product::Properties::Diamond;
                    else
                        shape = Product::Properties::Square; // default if fail

                    // color
                    wxString colorStr = productNode->GetAttribute(L"color", L"red");
                    Product::Properties color;
                    if (colorStr == L"red")
                        color = Product::Properties::Red;
                    else if (colorStr == L"green")
                        color = Product::Properties::Green;
                    else if (colorStr == L"blue")
                        color = Product::Properties::Blue;
                    else
                        color = Product::Properties::Red; // default if fail

                    // content
                    wxString contentStr = productNode->GetAttribute(L"content", L"none");
                    Product::Properties content;
                    if (contentStr == L"izzo")
                        content = Product::Properties::Izzo;
                    else if (contentStr == L"smith")
                        content = Product::Properties::Smith;
                    else if (contentStr == L"basketball")
                        content = Product::Properties::Basketball;
                    else if (contentStr == L"football")
                        content = Product::Properties::Football;
                    else
                        content = Product::Properties::Football; // default if fail

                    // kick attribute
                    wxString kickStr = productNode->GetAttribute(L"kick", L"no");
                    bool kick = (kickStr == L"yes");

                    auto product = make_shared<Product>(mGame, placement, shape, color, content, kick);
                    product->XmlLoad(productNode);
                    product->SetConveyor(conveyor.get());

                    int conveyorX = conveyor->GetX();
                    int conveyorY = conveyor->GetY();
                    int conveyorHeight = conveyor->GetHeight();
                    int productPlacement = placement;

                    int productY = conveyorY - (conveyorHeight / 2) + productPlacement;

                    product->SetLocation(conveyorX, productY);

                    mGame->AddItem(product);
                }
            }
        }
        else if (name == L"scoreboard")
        {
            int x = 0, y = 0, goodScore = 0, badScore = 0;

            node->GetAttribute(L"x", "0").ToInt(&x);
            node->GetAttribute(L"y", "0").ToInt(&y);
            node->GetAttribute(L"good", "0").ToInt(&goodScore);
            node->GetAttribute(L"bad", "0").ToInt(&badScore);

            wxString instructions;
            for (auto child = node->GetChildren(); child; child = child->GetNext())
            {
                if (child->GetType() == wxXML_TEXT_NODE)
                {
                    instructions += child->GetContent();
                }
                else if (child->GetName() == L"br")
                {
                    instructions += L"\n";
                }
            }

            item = make_shared<Scoreboard>(mGame, x, y, goodScore, badScore, instructions);
        }
        else if (name == L"beam")
        {
            int x = 0, y = 0, sender = 0;

            node->GetAttribute(L"x", "0").ToInt(&x);
            node->GetAttribute(L"y", "0").ToInt(&y);
            node->GetAttribute(L"sender", "0").ToInt(&sender);

            item = make_shared<Beam>(mGame, x, y, sender);
        }
        else if (name == L"sparty")
        {
            int x = 0, y = 0, height = 0;
            double kickDuration = 0.0, kickSpeed = 0.0;
            wxString pinStr;

            node->GetAttribute(L"x", "0").ToInt(&x);
            node->GetAttribute(L"y", "0").ToInt(&y);
            node->GetAttribute(L"height", "0").ToInt(&height);
            node->GetAttribute(L"kick-duration", "0.0").ToDouble(&kickDuration);
            node->GetAttribute(L"kick-speed", "0.0").ToDouble(&kickSpeed);
            pinStr = node->GetAttribute(L"pin", "0,0");

            int pinX = 0, pinY = 0;
            pinStr.BeforeFirst(',').ToInt(&pinX);
            pinStr.AfterFirst(',').ToInt(&pinY);
            wxPoint pin(pinX, pinY);

            item = make_shared<Sparty>(mGame, x, y, height, pin, kickDuration, kickSpeed);
        }

        if (item != nullptr)
        {
            item->XmlLoad(node);
            mGame->AddItem(item);
        }
    }
}
