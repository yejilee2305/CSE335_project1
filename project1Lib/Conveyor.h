/**
* @file Conveyor.h
 * @author Martin Sattam
 */

#ifndef CONVEYOR_H
#define CONVEYOR_H

#include <wx/wx.h>
#include <string>
#include "Item.h"
#include "Product.h"

/// Height of the conveyor
const int ConveyorHeight = 800;

/**
 * represents a conveyor belt in the game.
 * 
 * the conveyor belt moves products from one end to the other.
 */
class Conveyor : public Item
{
private:
    int mX; ///< X position of the conveyor
    int mY; ///< Y position of the conveyor
    int mHeight; ///< Height of the conveyor
    int mWidth = 800; ///< Width of the conveyor

    /// Speed of the conveyor
    double mSpeed;

    /// Panel location based on conveyor position
    wxPoint mPanelLocation;

    /// If the conveyor is running
    bool mIsRunning;

    /// Define button rectangles for the start and stop buttons
    static const wxRect StartButtonRect;

    /// Define button rectangles for the start and stop buttons
    static const wxRect StopButtonRect;

    /// offset of the belt
    double mBeltOffset = 0;

public:
    Conveyor(Game* game, int x, int y, double speed, int height, const wxPoint& panelLocation);


    /**
     * accepts a visitor
     *
     * @param visitor
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitConveyor(this); }

    /**
     * adds a product to the conveyor
     *
     * @param product the product to add
     */
    void AddProduct(std::shared_ptr<Product> product);

    void Update(double elapsed);

    void MoveProducts(double elapsed);

    // Starts the conveyor and resets the products' positions
    void Start();

    // Stops the conveyor
    void Stop();

    // Resets product positions based on their initial locations
    void ResetProducts();

    // Draws the conveyor and its panel
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    // Checks if the Start button or Stop button is clicked
    bool CheckStartButtonClick(int mouseX, int mouseY) const;
    bool CheckStopButtonClick(int mouseX, int mouseY) const;

    // Getters for conveyor position
    int GetX() const;
    int GetY() const;
    double GetSpeed() const;
    bool IsRunning() const;
};

#endif // CONVEYOR_H
