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

/**
 * Constructor
 */
Game::Game()
{
    mSparty = std::make_shared<Sparty>(this, 315, 340, 100, wxPoint2DDouble(1100, 400), 0.25, 1000);
    mSensor = std::make_shared<Sensor>(this, 1, 350, -22, 360); // Initialize sensor
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

/**
 * Update the game state.
 */
void Game::Update(double elapsed)
{
    if (mSparty->IsKicking())
    {
        mSparty->mKickProgress += elapsed * 4;
        if (mSparty->mKickProgress >= 1.0)
        {
            mSparty->mKickProgress = 0.0;
            mSparty->SetKicking(false);
        }
    }

    for (auto& product : mProducts)
    {
        product->Update(elapsed);
    }

    // check if last product has touched the bottom of the screen
    CheckLastProduct();
}

/**
 * Handle mouse clicks.
 */
void Game::HandleMouseClick(int x, int y)
{
    auto item = HitTest(x, y);
    if (item != nullptr)
    {
        mGrabbedItem = item;
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
    double pixelWidth = mVirtualWidth;
    double pixelHeight = mVirtualHeight;

    double scaleX = (width) / pixelWidth;
    double scaleY = (height) / pixelHeight;
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

    // Draw the background
    wxBrush background(wxColour(230, 255, 230));
    graphics->SetBrush(background);
    graphics->DrawRectangle(0, 0, pixelWidth, pixelHeight);

    for (auto items : mItems)
    {
        items->Draw(graphics);
    }

    for (const auto& gate : mGates)
    {
        gate->Draw(graphics);
    }

    for (const auto& wire : mWires)
    {
        wire->Draw(graphics.get(), mShowControlPoints);
    }

    // auto product = std::make_shared<Product>(this, 100, // placement
    //                                          Product::Properties::Circle, // shape
    //                                          Product::Properties::Blue, // color
    //                                          Product::Properties::Izzo, // content
    //                                          false); // don't kick
    // product->SetOnConveyor(true, 100);
    // AddItem(product);

    // for (auto& product : mProducts)
    // {
    //     product->Draw(graphics);
    // }

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
 * Add a product to the game.
 */
void Game::AddProduct(std::shared_ptr<Product> product)
{
    mProducts.push_back(product);
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
    mProducts.clear();
    mGates.clear();
    mWires.clear();
}

void Game::CheckLastProduct()
{
    if (mProducts.empty())
    {
        return;
    }

    auto lastProduct = mProducts.back();

    if (lastProduct->GetY() > mVirtualHeight)
    {
        mLastProductPassed = true;
        mLastProductTimer += 0.016; // 60 fps

        if (mLastProductTimer >= mLastProductDelay)
        {
            // handle end of level here
            // load next level
        }
    }
}
