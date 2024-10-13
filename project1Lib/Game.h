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
#include "Beam.h"
#include "Conveyor.h"
#include "Item.h"

class Game
{
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

    void Add(std::shared_ptr<Item> item);

    std::shared_ptr<Item> HitTest(int x, int y);

    void Clear();


private:

    /// all of the items in our game
    std::vector<std::shared_ptr<Item>> mItems;

    int currentLevel;
    Sparty sparty;
    Conveyor conveyor;
    Sensor sensor;
    // Beam beam;
    // std::vector<Gate* gates>;
    int score;
    bool gameOver;
};


#endif //GAME_H
