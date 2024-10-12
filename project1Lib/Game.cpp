/**
 * @file Game.cpp
 * @author Yeji Lee
 */

#include "pch.h"
#include "Game.h"

// Game::Game() : sensor(), currentLevel(0), score(0), gameOver(false) {
//  ResetGameState();
// }

void Game::StartGame()
{
 StartLevel(0);
}

void Game::StartLevel(int levelNumber)
{
 currentLevel = levelNumber;
 //sparty.Reset();
 conveyor.ResetProducts();
 //sensor.Reset();
 //beam.Reset();
 gates.clear();
}

void Game::Update()
{
 if (!gameOver)
 {
  //conveyor.Update();

  //sensor.Update(conveyor.GetCurrentProduct());
  //beam.Update(conveyor.GetCurrentProduct());

  for (auto& gate : gates) {
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
  gates.push_back(gate);  // 게이트 목록에 추가
 }
}

bool Game::IsGameOver() const {
 return gameOver;
}

void Game::ResetGameState() {
 score = 0;
 currentLevel = 0;
 gameOver = false;

 //sparty.Reset();
 conveyor.ResetProducts();
 //sensor.Reset();
 //beam.Reset();
 gates.clear();
}
