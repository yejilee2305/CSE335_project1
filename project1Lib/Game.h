/**
 * @file Game.h
 * @author Yeji Lee
 * @author Nicolas Roberts
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

    void Load(const wxString &filename);

    void StartLevel(int Number);
    void Update();

    void ConnectGates(Gate* outputGate, Gate* inputGate);

    void AddItem(std::shared_ptr<Item> item);
    void AddGate(std::shared_ptr<Gate> gate);

    void HandleMouseClick(int x, int y);
    void HandleMouseMove(int x, int y, bool leftDown);

    std::shared_ptr<Item> HitTest(int x, int y);
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    void Clear();

    void SetVirtualWidth(int width) {mVirtualWidth = width;}
    void SetVirtualHeight(int height) {mVirtualHeight = height;}

private:
    double mVirtualWidth;
    double mVirtualHeight;
    double mScale;
    double mXOffset;
    double mYOffset;

    std::wstring mImagesDirectory;
    std::vector<std::shared_ptr<Item>> mItems;
    std::vector<std::shared_ptr<Gate>> mGates;
    std::shared_ptr<Item> mGrabbedItem = nullptr; ///< Item grabbed by the mouse
};

#endif //GAME_H
