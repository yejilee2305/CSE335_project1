/**
 * @file Game.cpp
 * @author Yeji Lee
 */

#include "pch.h"
#include "Game.h"

Game::Game() : currentLevel(0),
 score(0),
 gameOver(false),
 sparty(100, 200, 50, wxPoint2DDouble(0.0, 0.0), 1.5, 2.0),
 conveyor(0, 300, 5, 100, wxPoint(0,0)),
 sensor(50.0, 20.0)  // Pass double values for Sensor initialization
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


void Game::ConnectGates(Gate* outputGate, Gate* inputGate) {
 if (outputGate && inputGate) {
  //outputGate->ConnectTo(inputGate);
 }
}

int Game::GetScore() const {
 return score;
}

void Game::NextLevel() {
 currentLevel++;
 StartLevel(currentLevel);
}

void Game::AddGate(Gate* gate) {
 if (gate) {
  //gates.push_back(gate);  // 게이트 목록에 추가
 }
}

bool Game::IsGameOver() const {
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
