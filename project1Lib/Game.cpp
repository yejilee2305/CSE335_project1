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

/**
 * Constructor
 */
Game::Game()
{
    mConveyor = std::make_shared<Conveyor>(this, 200, 400, 5, 800, wxPoint(60, -390));
}

/**
 * Load the game level from an XML file.
 */
void Game::Load(const wxString& filename)
{
    auto xmlParser = XMLParser(this);
    xmlParser.Load(filename);
}

/**
 * Start a specific level.
 */
void Game::StartLevel(int levelNumber)
{
    // Logic for starting the level
}

void Game::AddWire(PinOutput* outputPin, PinInput* inputPin) {
    // Set the parent gate for the output pin
    outputPin->SetParentGate(outputPin->GetParentGate());

    mWires.push_back(std::make_shared<Wire>(outputPin, inputPin));
    inputPin->SetConnection(outputPin); // Connect the input pin to the output pin
}

void Game::DrawWires(std::shared_ptr<wxGraphicsContext> graphics)
{
    for (const auto& wire : mWires)
    {
        wire->Draw(graphics.get(), mShowControlPoints);
    }
}
void topologicalSortUtil(Gate* gate, std::unordered_set<Gate*>& visited, std::stack<Gate*>& Stack) {
    visited.insert(gate);

    for (auto& inputPin : gate->GetInputPins()) {
        if (inputPin.HasConnection()) {
            auto connectedGate = inputPin.GetConnectedGate();
            if (connectedGate && visited.find(connectedGate) == visited.end()) {
                topologicalSortUtil(connectedGate, visited, Stack);
            }
        }
    }

    Stack.push(gate);
}
void Game::ComputeGateOutputs() {
    std::unordered_set<Gate*> visited;
    std::stack<Gate*> Stack;

    for (auto& gate : mGates) {
        if (visited.find(gate.get()) == visited.end()) {
            topologicalSortUtil(gate.get(), visited, Stack);
        }
    }

    // Now process the gates in reverse order
    while (!Stack.empty()) {
        Gate* gate = Stack.top();
        Stack.pop();
        gate->ComputeOutput(); // Compute the output of the gate
    }
}
/**
 * Update the game state.
 */
void Game::Update(double elapsed) {
     if (mConveyor) {
         mConveyor->Update();  // Update the conveyor’s position if it's running
    }

    // DO NOT REMOVE THIS
    for (auto& item : mItems)
    {
        item->Update(elapsed);
    }
}

/**
 * Handle mouse clicks.
 */
void Game::HandleMouseClick(wxMouseEvent& event)
{
    int x = event.GetX();
    int y = event.GetY();

    if (mConveyor->CheckStartButtonClick(x, y)) {
        wxLogMessage("Start button clicked.");
        mConveyor->Start();
    }
    else if (mConveyor->CheckStopButtonClick(x, y)) {
        wxLogMessage("Stop button clicked.");
        mConveyor->Stop();
    }
    else {
        wxLogMessage("Clicked outside start/stop buttons.");
    }
}

/**
 * Handle mouse movements.
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
 * Draw all game components.
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
    graphics->Translate(mXOffset, mYOffset);  // Centering offset
    graphics->Scale(mScale, mScale);          // Apply scaling for consistent sizing

    // Draw the background color for the entire virtual game area
    wxBrush background(wxColour(230, 255, 230));  // Light green background
    graphics->SetBrush(background);
    graphics->DrawRectangle(0, 0, pixelWidth, pixelHeight);  // Fill the virtual area


    /// WE ARE ONLY ALLOW TO HAVE ONE LIST  https://cse335.egr.msu.edu/project1-fs24/description.php read Rules and Requirements
    // Draw each item in the game (e.g., products, obstacles) with the applied scaling
    for (const auto& item : mItems) {
        item->Draw(graphics);
    }

    // Draw all gates
    for (const auto& gate : mGates) {
        gate->Draw(graphics);
    }
    // Draw wires with optional control points for visualization (e.g., debugging or editor mode)
    for (const auto& wire : mWires) {
        wire->Draw(graphics.get(), mShowControlPoints);
    }
    if (mConveyor) {
        mConveyor->Draw(graphics);
    }



    // Restore the original graphics state to avoid affecting subsequent draws
    graphics->PopState();
}


/**
 * Add an item to the game.
 */
void Game::AddItem(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * Add a gate to the game.
 */
void Game::AddGate(std::shared_ptr<Gate> gate)
{
    mGates.push_back(gate);
}

/**
 * Test if a click is on an item.
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
 */
std::shared_ptr<Gate> Game::HitTestGate(double x, double y)
{
    for (auto& gate : mGates)
    {
        if (gate->HitTest(x, y))
        {
            return gate;
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
    mGates.clear();
    mWires.clear();
}

