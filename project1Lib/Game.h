/**
 * @file Game.h
 * @author Yeji Lee
 * @author Nicolas Roberts
 *
 */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "Gate.h"
#include "Conveyor.h"
#include "Wire.h"
#include "Beam.h"

class Game
{
public:
    Game();

    void Load(const wxString& filename);
    void StartLevel(int Number);
    void ComputeGateOutputs();
    void Update(double elapsed);

    void ConnectGates(Gate* outputGate, Gate* inputGate);
    void AddItem(std::shared_ptr<Item> item);
    void AddGate(std::shared_ptr<Gate> gate);

    void HandleMouseClick(wxMouseEvent& event);
    void HandleMouseMove(int x, int y, wxMouseEvent& event);
    std::shared_ptr<Item> HitTest(int x, int y);
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void Clear();

    void SetVirtualWidth(int width) { mVirtualWidth = width; }
    void SetVirtualHeight(int height) { mVirtualHeight = height; }

    std::shared_ptr<Gate> HitTestGate(double x, double y);

    size_t GetItemSize() const { return mItems.size(); }

    const std::vector<std::shared_ptr<Gate>>& GetGates() const { return mGates; }
    void AddWire(PinOutput* outputPin, PinInput* inputPin);
    void DrawWires(std::shared_ptr<wxGraphicsContext> graphics);
    void SetShowControlPoints(bool show) { mShowControlPoints = show; }
    bool GetShowControlPoints() const { return mShowControlPoints; }
    const std::vector<std::shared_ptr<Wire>>& GetWires() const { return mWires; }

    double GetScale() const { return mScale; }
    double GetXOffset() const { return mXOffset; }
    double GetYOffset() const { return mYOffset; }
    double GetWidth() const { return mVirtualWidth; }
    double GetHeight() const { return mVirtualHeight; }
    const std::vector<std::shared_ptr<Item>>& GetItems() const { return mItems; }
    int GetCurrentLevel() const { return mCurrentLevel; }
    void SetCurrentLevel(int level) { mCurrentLevel = level; }

    void SetSparty(std::shared_ptr<Sparty> spartyInstance) { sparty = spartyInstance; }


private:
    double mVirtualWidth;
    double mVirtualHeight;
    double mScale;
    double mXOffset;
    double mYOffset;
    std::wstring mImagesDirectory;
    bool mLastProductPassed = false;
    double mLastProductTimer = 0;
    double mLastProductDelay = 1.0;

    bool mAllProductsPassed = false;
    double mPassTimer = 0.0;

    int mCurrentLevel = 0;


    std::vector<std::shared_ptr<Item>> mItems;
    std::vector<std::shared_ptr<Gate>> mGates;
    std::vector<std::shared_ptr<Wire>> mWires;

    std::shared_ptr<Item> mGrabbedItem = nullptr;

    bool mShowControlPoints = false;

    void StartNextLevel();

    std::shared_ptr<Sparty> sparty;
};

#endif // GAME_H
