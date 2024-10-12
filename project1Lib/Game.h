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
public:
 Game();

 // starting game
 void StartGame();

 // starting level ____
 void StartLevel(int Number);

 //game update
 void Update();

 // connecting gates
 void ConnectGates(Gate* outputGate, Gate* inputGate);

 // score
 int GetScore() const;

 // next level
 void NextLevel();

 // new gate
 void AddGate(Gate* gate);

 // check if game has ended
 bool IsGameOver() const;

 void OnDraw(std::shared_ptr<wxGraphicsContext> gc, int width, int height);

private:
 int currentLevel;
 Sparty sparty;
 Conveyor conveyor;
 Sensor sensor;
 //Beam beam;
 //std::vector<Gate* gates>;
 int score;
 bool gameOver;

};



#endif //GAME_H
