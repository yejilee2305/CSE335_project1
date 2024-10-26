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
#include "Wire.h"

class Game
{
public:
    Game();

    void Load(const wxString& filename);

    void StartLevel(int Number);
    void Update(double elapsed);

    void ConnectGates(Gate* outputGate, Gate* inputGate);

    void AddItem(std::shared_ptr<Item> item);
    void AddGate(std::shared_ptr<Gate> gate);

    void HandleMouseClick(int x, int y);
    void HandleMouseMove(int x, int y, wxMouseEvent& event);

    std::shared_ptr<Item> HitTest(int x, int y);
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void AddProduct(std::shared_ptr<Product> product);

    void Clear();

    void SetVirtualWidth(int width) { mVirtualWidth = width; }
    void SetVirtualHeight(int height) { mVirtualHeight = height; }
    std::shared_ptr<Gate> HitTestGate(double x, double y);

    /**
     * Get size of mItems
     * @return size of mItems
     */
    size_t GetItemSize() const { return mItems.size(); }


    std::vector<std::shared_ptr<Product>> GetProducts() const { return mProducts; }
    const std::vector<std::shared_ptr<Gate>>& GetGates() const { return mGates; }
    void AddWire(PinOutput* outputPin, PinInput* inputPin);
    void DrawWires(std::shared_ptr<wxGraphicsContext> graphics);
    void SetShowControlPoints(bool show) { mShowControlPoints = show; }
    bool GetShowControlPoints() const { return mShowControlPoints; }
    const std::vector<std::shared_ptr<Wire>>& GetWires() const { return mWires; }

private:
    int mVirtualWidth;
    int mVirtualHeight;
    double mScale;
    double mXOffset;
    double mYOffset;
    std::wstring mImagesDirectory;
    std::vector<std::shared_ptr<Item>> mItems;
    std::vector<std::shared_ptr<Gate>> mGates;
    std::shared_ptr<Item> mGrabbedItem = nullptr; ///< Item grabbed by the mouse
    std::vector<std::shared_ptr<Product>> mProducts;
    std::vector<std::shared_ptr<Wire>> mWires;
    bool mShowControlPoints = false;
};

#endif //GAME_H
