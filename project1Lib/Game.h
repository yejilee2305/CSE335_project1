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
#include "Beam.h"
#include "Team.h"
#include "ItemVisitor.h"

class Game
{
public:
    /// Enumeration class for different game states
    enum class GameState {Beginning, Playing, Ending};

    Game();

    void Load(const wxString& filename);
    void StartLevel(int Number);
    void ComputeGateOutputs();
    void Update(double elapsed);

    void AddItem(std::shared_ptr<Item> item);
    void AddGate(std::shared_ptr<Gate> gate);

    void HandleMouseClick(wxMouseEvent& event);
    void HandleMouseMove(int x, int y, wxMouseEvent& event);
    std::shared_ptr<Item> HitTest(int x, int y);
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void Clear();

    void SetVirtualWidth(int width) { mVirtualWidth = width; }
    void SetVirtualHeight(int height) { mVirtualHeight = height; }
    Team& GetTeam() { return mTeam; }

    std::shared_ptr<Item> HitTestGate(double x, double y);

    size_t GetItemSize() const { return mItems.size(); }

    void AddWire(PinOutput* outputPin, PinInput* inputPin);
    void SetShowControlPoints(bool show) { mShowControlPoints = show; }
    bool GetShowControlPoints() const { return mShowControlPoints; }

    double GetScale() const { return mScale; }
    double GetXOffset() const { return mXOffset; }
    double GetYOffset() const { return mYOffset; }
    double GetWidth() const { return mVirtualWidth; }
    double GetHeight() const { return mVirtualHeight; }
    const std::vector<std::shared_ptr<Item>>& GetItems() const { return mItems; }
    int GetCurrentLevel() const { return mCurrentLevel; }
    void SetCurrentLevel(int level) { mCurrentLevel = level; }

    void SetSparty(std::shared_ptr<Sparty> spartyInstance) { sparty = spartyInstance; }
    void Accept(ItemVisitor* visitor);

    /**
    * @return mState
    */
    GameState GetState() const {return mState;}



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

    std::shared_ptr<Item> mGrabbedItem = nullptr;

    bool mShowControlPoints = false;

    void StartNextLevel();


    std::shared_ptr<Sparty> sparty;

    Team mTeam;

    /// Ready state
    GameState mState = GameState::Beginning;

};

#endif // GAME_H
