/**
 * @file Game.cpp
 * @author Yeji Lee
 * @author Nicolas Roberts
 */

#include "pch.h"
#include "Game.h"

#include "Beam.h"
#include "Sensor.h"
#include "Gate.h"
#include "XMLParser.h"
#include "Scoreboard.h"
#include "Conveyor.h"
#include "Pins.h"
#include "PinInput.h"
#include "Wire.h"
#include "PinOutput.h"

const double frameTime = 0.016; //60 fps
/**
 * Constructor
 */
Game::Game()
{
    mSparty = std::make_shared<Sparty>(this, 345, 340, 100, wxPoint2DDouble(1100, 400), 0.25, 1000);
}

/**
 * Load the game level from a level XML file
 * @param filename The filename of the level XML file
 */
void Game::Load(const wxString& filename)
{
    auto xmlParser = XMLParser(this);
    xmlParser.Load(filename);
}

void Game::StartLevel(int levelNumber)
{
    //starting certain level
}
void Game::AddWire(PinOutput* outputPin, PinInput* inputPin)
{
    mWires.push_back(std::make_shared<Wire>(outputPin, inputPin));
}

void Game::DrawWires(std::shared_ptr<wxGraphicsContext> graphics)
{
    for (const auto& wire : mWires)
    {
        wire->Draw(graphics.get(), mShowControlPoints);
    }
}

void Game::Update(double elapsed) {
    // Update kick progress
    if (mSparty->IsKicking()) {
        mSparty->mKickProgress += elapsed * 4; // Adjust speed as needed
        if (mSparty->mKickProgress >= 1.0) {
            mSparty->mKickProgress = 0.0;  // Reset after kick
            mSparty->SetKicking(false);    // Stop kicking
        }
    }
}


void Game::HandleMouseClick(int x, int y)
{
    auto item = HitTest(x, y);
    if (item != nullptr)
    {
        mGrabbedItem = item;
    }
}


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

void Game::ConnectGates(Gate* outputGate, Gate* inputGate)
{
    if (outputGate && inputGate)
    {
        //outputGate->ConnectTo(inputGate);
    }
}

void Game::AddItem(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

void Game::AddGate(std::shared_ptr<Gate> gate)
{
    mGates.push_back(gate); // Add the new gate to the list
}

/**
 * Draws the content of the game on the screen
 * @param graphics The graphics context to be drawn on
 * @param width Width to use to scale
 * @param height Height to use to scale
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    int pixelWidth = mVirtualWidth;
    int pixelHeight = mVirtualHeight;

    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = 0;
    if (height > pixelHeight * mScale)
    {
        mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
    }

    graphics->PushState();
    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    for (auto items : mItems)
    {
        // items->Draw(graphics);
    }


    wxBrush background(wxColour(230, 255, 230));
    graphics->SetBrush(background);
    graphics->DrawRectangle(0, 0, pixelWidth, pixelHeight);
    for (const auto& gate : mGates)
    {
        gate->Draw(graphics);
    }
    for (const auto& wire : mWires)
    {
        wire->Draw(graphics.get(), mShowControlPoints);
    }
    // Create a temporary scoreboard for this draw cycle
    auto scoreboard = std::make_shared<Scoreboard>(this, 600, 40, 10, -5);
    scoreboard->SetInstructions(
        "Make Sparty kick all product from the conveyor\n that are not Izzo or Smith.");

    // Draw the scoreboard within the graphics context
    scoreboard->Draw(graphics);

    auto conveyor = std::make_shared<Conveyor>(this, 150, 400, 100, 800, wxPoint(60, -390));

    conveyor->Draw(graphics, 60, -390);


    auto beam = std::make_shared<Beam>(this, 242, 437, -175);
    beam->Draw(graphics);

    if (mSparty) {
        mSparty->Draw(graphics);
    }




    // auto product = std::make_shared<Product>(this, 100, // placement
    //                                          Product::Properties::Circle, // shape
    //                                          Product::Properties::Blue, // color
    //                                          Product::Properties::Izzo, // content
    //                                          false); // don't kick
    // product->SetOnConveyor(true, 100);
    // AddItem(product);

    // for (const auto& item : mItems)
    // {
    //     item->Draw(graphics);
    // }
    graphics->PopState();
}




/**
 * Test x,y click location to see if we clicked on a item
 * @param x x location in pixel
 * @param y y location in pixel
 * @return pointer to the item we clicked on or nullptr if none
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
 * Deletes all the known items in the game
 */
void Game::Clear()
{
    mItems.clear();
    mProducts.clear();
}

void Game::AddProduct(std::shared_ptr<Product> product)
{
    mProducts.push_back(product);
}
