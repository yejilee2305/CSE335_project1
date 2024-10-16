/**
 * @file Game.cpp
 * @author Yeji Lee
 * @author Nicolas Roberts
 */

#include "pch.h"
#include "Game.h"
#include "Sensor.h"
#include "Gate.h"
#include "XMLParser.h"

/**
 * Constructor
 */
Game::Game()
{
}

/**
 * Load the game level from a level XML file
 * @param filename The filename of the level XML file
 */
void Game::Load(const wxString &filename)
{
    auto xmlParser = XMLParser(this);
    xmlParser.Load(filename);
}

void Game::StartLevel(int levelNumber)
{
//starting certain level
}

void Game::Update()
{
 //if (!gameOver)
 {
  //conveyor.Update();

  //sensor.Update(conveyor.GetCurrentProduct());
  //beam.Update(conveyor.GetCurrentProduct());

  //for (auto& gate : gates) {
   //gate->Update();
  }

  //sparty.Update(beam.IsActive(), sensor.GetProductType());

  //if (beam.IsActive() && sparty.ShouldKick())
  {
   //core += sparty.Kick(conveyor.GetCurrentProduct()) ? 10 : -5;
  }

  //if (conveyor.IsFinished())
  {
   //NextLevel();
  }
 }


void Game::ConnectGates(Gate* outputGate, Gate* inputGate) {
 if (outputGate && inputGate) {
  //outputGate->ConnectTo(inputGate);
 }
}

//int Game::GetScore() const {
 //return score;
//}

//void Game::NextLevel() {
 //currentLevel++;
 //StartLevel(currentLevel);
//}

void Game::AddItem(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}


//bool Game::IsGameOver() const {
 //return gameOver;
//}

// void Game::ResetGameState() {
//  score = 0;
//  currentLevel = 0;
//  gameOver = false;
//
//  //sparty.Reset();
//  conveyor.ResetProducts();
//  //sensor.Reset();
//  //beam.Reset();
//  gates.clear();
// }
void Game::AddGate(std::shared_ptr<Gate> gate) {
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
    // Determine the size of the playing area in pixels
    // This is up to you...
    int pixelWidth = mVirtualWidth;
    int pixelHeight = mVirtualHeight;

    //
    // Automatic Scaling
    //
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
        items->Draw(graphics);
    }

    //
    // Drawing a rectangle that is the playing area size
    //
    wxBrush background(wxColour(230,255,230));

    graphics->SetBrush(background);
    graphics->DrawRectangle(0, 0, pixelWidth, pixelHeight);

    graphics->PopState();

    for (const auto& gate : mGates)
    {
     gate->Draw(graphics); // Call the draw method for each gate
    }
}


/**
 * Test x,y click location to see if it we clicked on a item
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

/**
 * Deletes all the known items in the game
 */
void Game::Clear()
{
    mItems.clear();
}