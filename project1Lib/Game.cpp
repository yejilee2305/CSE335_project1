/**
 * @file Game.cpp
 * @author Yeji Lee
 * @author Nicolas Roberts
 */

#include "pch.h"
#include "Beam.h"
#include "Sensor.h"
#include "Gate.h"
#include "Game.h"
#include "XMLParser.h"
#include "Scoreboard.h"
#include "Conveyor.h"
#include "Pins.h"
#include "PinInput.h"
#include "Wire.h"
#include <unordered_map>
#include <unordered_set>
#include <stack>

#include "BeamVisitor.h"
#include "GateVisitor.h"
#include "ProductVisitor.h"
#include "WireVisitor.h"
#include "SpartyVisitor.h"

/// border for the game to make it black
const int BigNumberBorder = 2000;

/**
 * Constructor
 */
Game::Game()
{
}


/**
 * load the game
 * 
 * @param filename 
 */
void Game::Load(const wxString& filename)
{
    auto xmlParser = XMLParser(this);
    xmlParser.Load(filename);
}

/**
 * Start a specific level.
 * 
 * @param levelNumber the level number
 */
void Game::StartLevel(int levelNumber)
{
    std::wstring levelFile = L"levels/level" + std::to_wstring(levelNumber) + L".xml";
    Load(levelFile);
}

void Game::AddWire(PinOutput* outputPin, PinInput* inputPin)
{
    //inputPin->SetConnection(outputPin);
    inputPin->ConnectToOutput(outputPin);
    outputPin->ConnectToInput(inputPin);
}

/**
 * used for topological sort of the gates
 * 
 * @param gate  the gate
 * @param visited  the visited set
 * @param Stack  the stack
 */
void topologicalSortUtil(Gate* gate, std::unordered_set<Gate*>& visited, std::stack<Gate*>& Stack)
{
    visited.insert(gate);

    for (auto& inputPin : gate->GetInputPins())
    {
        if (inputPin.HasConnection())
        {
            auto connectedGate = inputPin.GetConnectedGate();
            if (connectedGate && visited.find(connectedGate) == visited.end())
            {
                topologicalSortUtil(connectedGate, visited, Stack);
            }
        }
    }

    Stack.push(gate);
}

void Game::ComputeGateOutputs()
{
    GateComputeOutputVisitor computeVisitor;
    Accept(&computeVisitor);
}

/**
 * update the game
 * 
 * @param elapsed time
 */
void Game::Update(double elapsed)
{
    //---- DO NOT REMOVE THIS
    for (auto& item : mItems)
    {
        item->Update(elapsed);
    }
    //---- DO NOT REMOVE THIS

    BeamVisitor beamVisitor;
    for (const auto& item : mItems)
    {
        item->Accept(&beamVisitor);
    }

    bool anyBeamBroken = false;
    const auto& beams = beamVisitor.GetBeams();
    for (auto beam : beams)
    {
        if (beam->IsBroken())
        {
            anyBeamBroken = true;
            break;
        }
    }

    if (anyBeamBroken)
    {
        SpartyVisitor spartyVisitor;
        for (const auto& item : mItems)
        {
            item->Accept(&spartyVisitor);
        }

        const auto& spartys = spartyVisitor.GetSpartys();
        for (auto sparty : spartys)
        {
            sparty->Kick();
        }
    }

    ProductVisitor productVisitor;
    for (const auto& item : mItems)
    {
        item->Accept(&productVisitor);
    }
    const auto& products = productVisitor.GetProducts();
}

/**
 * Handle mouse clicks.
 * 
 * @param event the mouse event 
 */
void Game::HandleMouseClick(wxMouseEvent& event)
{
    int x = event.GetX();
    int y = event.GetY();
}

/**
 * Handle mouse move events.
 * 
 * @param x x axis 
 * @param y y axis 
 * @param event the mouse event 
 */
void Game::HandleMouseMove(int x, int y, wxMouseEvent& event)
{
    // Check if an item is currently being moved by the mouse
    if (mGrabbedItem != nullptr)
    {
        // Continue to move the item only while the left button is down
        if (event.LeftIsDown())
        {
            mGrabbedItem->SetLocation(x, y); // Update the item's location to the current mouse coordinates
        }
        else
        {
            // When the left button is released, we release the item
            mGrabbedItem = nullptr;
        }
    }
}

/**
 * Draw the game.
 * 
 * @param graphics 
 * @param width 
 * @param height 
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    // Define the virtual game area dimensions (pixelWidth and pixelHeight) for scaling calculations
    double pixelWidth = mVirtualWidth;
    double pixelHeight = mVirtualHeight;

    // Calculate scaling factors for both X and Y directions
    double scaleX = width / pixelWidth;
    double scaleY = height / pixelHeight;

    // Choose the minimum scale to maintain the aspect ratio
    mScale = (scaleX < scaleY) ? scaleX : scaleY;

    // Center the scaled game content within the window by calculating offsets
    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = (height - pixelHeight * mScale) / 2.0;

    // Set the initial graphics state and apply translation and scaling
    graphics->PushState();
    graphics->Translate(mXOffset, mYOffset); // Centering offset
    graphics->Scale(mScale, mScale); // Apply scaling for consistent sizing

    // Draw the background color for the entire virtual game area
    wxBrush background(wxColour(230, 255, 230)); // Light green background
    graphics->SetBrush(background);
    graphics->DrawRectangle(0, 0, pixelWidth, pixelHeight); // Fill the virtual area


    /// WE ARE ONLY ALLOW TO HAVE ONE LIST  https://cse335.egr.msu.edu/project1-fs24/description.php read Rules and Requirements
    // Draw each item in the game (e.g., products, obstacles) with the applied scaling
    for (const auto& item : mItems)
    {
        item->Draw(graphics);
    }

    WireDrawingVisitor wireVisitor(graphics.get(), mShowControlPoints);
    Accept(&wireVisitor);


    // for drawing the black box outside of the view
    graphics->SetBrush(wxBrush(*wxBLACK));
    graphics->SetPen(wxPen(*wxBLACK));

    graphics->DrawRectangle(-BigNumberBorder, 0, BigNumberBorder - 1,
                            BigNumberBorder);

    graphics->DrawRectangle(pixelWidth + 1, 0, BigNumberBorder, BigNumberBorder);

    graphics->DrawRectangle(0, -BigNumberBorder, BigNumberBorder,
                            BigNumberBorder - 1);

    graphics->DrawRectangle(0, pixelHeight + 1, BigNumberBorder, BigNumberBorder);


    // Restore the original graphics state to avoid affecting subsequent draws
    graphics->PopState();
}


/**
 * Add an item to the game.
 * 
 * @param item
 */
void Game::AddItem(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * add a gate to the game
 * 
 * @param gate 
 */
void Game::AddGate(std::shared_ptr<Gate> gate)
{
    AddItem(gate);
}

/**
 * Test if a click is on an item.
 * 
 * @param x 
 * @param y 
 * @return std::shared_ptr<Item> 
 */
std::shared_ptr<Item> Game::HitTest(int x, int y)
{
    for (auto i = mItems.begin(); i != mItems.end(); i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return nullptr;
}

/**
 * Test if a click is on a gate.
 * 
 * @param x x axis 
 * @param y y axis
 * @return std::shared_ptr<Item>  the item
 */
std::shared_ptr<Item> Game::HitTestGate(double x, double y)
{
    GateHitTestVisitor hitTestVisitor(x, y);
    Accept(&hitTestVisitor);
    Gate* hitGate = hitTestVisitor.GetHitGate();
    if (hitGate)
    {
        for (const auto& gate : mItems)
        {
            if (gate.get() == hitGate)
            {
                return gate;
            }
        }
    }
    return nullptr;
}

/**
 * Clear all items from the game.
 */
void Game::Clear()
{
    mItems.clear();
}


void Game::StartNextLevel()
{
    mCurrentLevel += 1;
    std::wstring nextLevelFile = L"levels/level" + std::to_wstring(mCurrentLevel) + L".xml";
    Clear();
    Load(nextLevelFile);
}


void Game::Accept(ItemVisitor* visitor)
{
    for (const auto& item : mItems)
    {
        if (item)
        {
            item->Accept(visitor);
        }
    }
}
