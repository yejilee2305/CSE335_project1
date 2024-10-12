/**
 * @file Game.h
 * @author Yeji Lee
 *
 *
 */
 
#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Gate.h"
#include "Sparty.h"
#include "Sensor.h"
//#include "Beam.h"
#include "Conveyor.h"

class Game {
private:
 int currentLevel;
 Sparty sparty;
 Conveyor conveyor;
 Sensor sensor;
 //Beam beam;
 std::vector<Gate*> gates;
 int score;
 bool gameOver;

 void ResetGameState();

public:
 void StartGame();
 void StartLevel(int levelNumber);

 void Update();

 void ConnectGates(Gate* outputGate, Gate* inputGate);

 int GetScore() const;

 void NextLevel();

 void AddGate(Gate* gate);

 bool IsGameOver() const;

};



#endif //GAME_H
