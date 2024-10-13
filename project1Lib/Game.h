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
    // GetScore() const;

    // next level
    //void NextLevel();

    void AddItem(std::shared_ptr<Item> item);

    // check if game has ended
    bool IsGameOver() const;

    void OnDraw(std::shared_ptr<wxGraphicsContext> gc, int width, int height);

    std::shared_ptr<Item> HitTest(int x, int y);

    void Clear();

    void Add(std::shared_ptr<Item> item);

private:
    /**
    * Represents the width of the virtual playing area.
    */
    double mVirtualWidth;
    /**
    * Represents the height of the virtual playing area.
    */
    double mVirtualHeight;
    /**
    * Represents the scaling factor of the virtual playing area.
    */
    double mScale;
    /**
    * X offset for drawing
    */
    double mXOffset;
    /**
    * Y offset for drawing
    */
    double mYOffset;

    /// Directory containing the system images
    std::wstring mImagesDirectory;

    /// All of the items to populate our game
    std::vector<std::shared_ptr<Item>> mItems;


};



#endif //GAME_H
