/**
 * @file Game.cpp
 * @author Yeji Lee
 */

#include "pch.h"
#include "Game.h"
#include "Sensor.h"

/**
 * Constructor
 */
Game::Game()
{

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

void Game::OnDraw(std::shared_ptr<wxGraphicsContext> gc, int width, int height)
{
    // Determine the size of the playing area in pixels
    // This is up to you...
    int pixelWidth = 1304;
    int pixelHeight = 900;

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

    gc->PushState();

    gc->Translate(mXOffset, mYOffset);
    gc->Scale(mScale, mScale);

    //
    // Drawing a rectangle that is the playing area size
    //
    wxBrush background(*wxRED);

    gc->SetBrush(background);
    gc->DrawRectangle(0, 0, pixelWidth, pixelHeight);

    gc->PopState();
}
