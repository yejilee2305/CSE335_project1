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

/**
 * class for the game
 * 
 */
class Game
{
public:
    /// Enumeration class for different game states
    enum class GameState {Beginning, Playing, Ending};

    Game();

    void Load(const wxString& filename);
    void StartLevel(int Number);

    /**
     * Compute the outputs of the gates.
     * 
     */
    void ComputeGateOutputs();
    void Update(double elapsed);

    void AddItem(std::shared_ptr<Item> item);
    void AddGate(std::shared_ptr<Gate> gate);

    void HandleMouseClick(wxMouseEvent& event);
    void HandleMouseMove(int x, int y, wxMouseEvent& event);
    std::shared_ptr<Item> HitTest(int x, int y);
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void Clear();


    /**
     * Set the virtual width.
     * 
     * @param width the width
     */
    void SetVirtualWidth(int width) { mVirtualWidth = width; }

    /**
     * Set the virtual height.
     * 
     * @param height the height
     */
    void SetVirtualHeight(int height) { mVirtualHeight = height; }

    /**
     * Get the team object.
     * 
     * @return the team object
     */
    Team& GetTeam() { return mTeam; }

    std::shared_ptr<Item> HitTestGate(double x, double y);


/**
 * Get the number of items in the game.
 * 
 * @return the number of items
 */
    size_t GetItemSize() const { return mItems.size(); }


/**
 * Add a wire to the game.
 * 
 * @param outputPin the output pin
 * @param inputPin the input pin
 */
    void AddWire(PinOutput* outputPin, PinInput* inputPin);

    /**
     * sets the show control points
     * 
     * @param show bool 
     */
    void SetShowControlPoints(bool show) { mShowControlPoints = show; }

    /**
     * gets the show control points
     * 
     * @return bool
     */
    bool GetShowControlPoints() const { return mShowControlPoints; }


    /**
     * gets the scale
     * 
     * @return double 
     */
    double GetScale() const { return mScale; }

    /**
     * gets the x offset
     * 
     * @return double 
     */
    double GetXOffset() const { return mXOffset; }

    /**
     * gets the y offset
     * 
     * @return double 
     */
    double GetYOffset() const { return mYOffset; }

    /**
     * gets the width 
     * 
     * @return double 
     */
    double GetWidth() const { return mVirtualWidth; }

    /**
     * gets the height 
     * 
     * @return double 
     */
    double GetHeight() const { return mVirtualHeight; }

    /**
     * gets the items
     * 
     * @return const std::vector<std::shared_ptr<Item>>& 
     */
    const std::vector<std::shared_ptr<Item>>& GetItems() const { return mItems; }

    /**
     * gets the current level
     * 
     * @return int 
     */
    int GetCurrentLevel() const { return mCurrentLevel; }

    /**
     * sets the current level 
     * 
     * @param level 
     */
    void SetCurrentLevel(int level) { mCurrentLevel = level; }

    /**
     * accepts a visitor
     * 
     * @param visitor 
     */
    void Accept(ItemVisitor* visitor);

    /**
    * @return mState
    */
    GameState GetState() const {return mState;}

    /**
    * Set the game state.
    * @param state New state to set
    */
    void SetState(GameState state) { mState = state; }

/**
 * starts the next level
 * 
 */
    void StartNextLevel();

private:
    double mVirtualWidth; ///< Virtual width
    double mVirtualHeight; ///< Virtual height
    double mScale; ///< Scale
    double mXOffset; ///< X offset
    double mYOffset; ///< Y offset
    std::wstring mImagesDirectory; ///<directory for images

    double mPassTimer = 0; ///< Timer for passing the level

    int mCurrentLevel = 0; ///< current level


    std::vector<std::shared_ptr<Item>> mItems; ///< vector of items

    std::shared_ptr<Item> mGrabbedItem = nullptr; ///< the item that is being moved by the mouse

    bool mShowControlPoints = false; ///< Show control points

    Team mTeam; ///< team object

    /// Ready state
    GameState mState = GameState::Beginning;

};

#endif // GAME_H
