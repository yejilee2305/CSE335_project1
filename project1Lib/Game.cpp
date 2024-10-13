/**
 * @file Game.cpp
 * @author Yeji Lee
 */

#include "pch.h"
#include "Game.h"

/// initial item X location
const int InitialX = 100;

/// initial item Y location
const int InitialY = 100;


Game::Game() : currentLevel(0),
               score(0),
               gameOver(false),
               sparty(this, 100, 200, 50, wxPoint2DDouble(0.0, 0.0), 1.5, 2.0),
               conveyor(this, 0, 300, 5, 100, wxPoint(0, 0)),
               sensor(this, 50.0, 20.0) // Pass double values for Sensor initialization
{
    // resetting game
}

void Game::StartGame()
{
    StartLevel(0);
}

void Game::StartLevel(int levelNumber)
{
    //starting certain level
}

void Game::Update()
{
    if (!gameOver)
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
        NextLevel();
    }
}


void Game::ConnectGates(Gate* outputGate, Gate* inputGate)
{
    if (outputGate && inputGate)
    {
        //outputGate->ConnectTo(inputGate);
    }
}

int Game::GetScore() const
{
    return score;
}

void Game::NextLevel()
{
    currentLevel++;
    StartLevel(currentLevel);
}

void Game::AddGate(Gate* gate)
{
    if (gate)
    {
        //gates.push_back(gate);  // 게이트 목록에 추가
    }
}

bool Game::IsGameOver() const
{
    return gameOver;
}

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

void Game::OnDraw(std::shared_ptr<wxGraphicsContext> gc, int width, int height)
{
    // Convert shared_ptr to raw pointer for wxGraphicsContext
    wxGraphicsContext* rawGc = gc.get();

    // Set the background to a specific color (you can adjust as necessary)
    rawGc->SetBrush(*wxBLACK_BRUSH);
    rawGc->DrawRectangle(0, 0, width, height);

    // Draw the conveyor (assuming Conveyor has a Draw method)
    conveyor.Draw(rawGc);

    // Draw Sparty (assuming Sparty has a Draw method)
    sparty.Draw(rawGc);

    // Draw products on the conveyor (assuming Product has a Draw method)
    for (const auto& product : conveyor.GetProducts())
    {
        product->Draw(rawGc);
    }

    // Optionally draw any gates or other game elements
    for (const auto& gate : gates)
    {
        gate->Draw(rawGc);
    }
}

/**
 * test x,y click location to see if it we clicked on a item
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
 * deletes all the known items in the aquarium
 */
void Game::Clear()
{
    mItems.clear();
}

/**
 * adds the item to the game
 * @param item new item to add
 */
void Game::Add(std::shared_ptr<Item> item)
{
    item->SetLocation(InitialX, InitialY);
    mItems.push_back(item);
}
