/**
* @file Conveyor.cpp
 * @author Martin Sattam
 */

#include "pch.h"
#include "Conveyor.h"
#include <wx/graphics.h>
#include <wx/bitmap.h>
#include "Game.h"

#include "ProductVisitor.h"

/// Button rectangles for the start and stop buttons
const wxRect Conveyor::StartButtonRect(35, 29, 95, 36);
const wxRect Conveyor::StopButtonRect(35, 87, 95, 36);

/// Image file for the conveyor background
const std::wstring conveyorBackImage = L"images/conveyor-back.png";


/**
 * consturctor for the conveyor
 * 
 * @param game the game object
 * @param x the x position
 * @param y the y position
 * @param speed the speed of the conveyor
 * @param height the height of the conveyor
 * @param panelLocation the location of the panel
 */
Conveyor::Conveyor(Game* game, int x, int y, double speed, int height, const wxPoint& panelLocation)
    : Item(game, conveyorBackImage),
      mX(x), mY(y), mSpeed(speed), mHeight(height), mPanelLocation(panelLocation), mIsRunning(false)
{
}

/**
 * updates the conveyor and moves the products
 * 
 * @param elapsed the time elapsed
 */
void Conveyor::Update(double elapsed)
{
    if (mIsRunning)
    {
        mBeltOffset += mSpeed * elapsed;

        if (mBeltOffset >= mHeight)
        {
            mBeltOffset -= mHeight;
        }

        MoveProducts(elapsed);
    }
}

/**
 * moves the products on the conveyor
 * 
 * @param elapsed the time elapsed
 */
void Conveyor::MoveProducts(double elapsed)
{
    ProductVisitor visitor;
    for (const auto& item : GetGame()->GetItems())
    {
        item->Accept(&visitor);
    }
}

/**
 * starts the conveyor and resets the products 
 * 
 */
void Conveyor::Start()
{
    mIsRunning = true;
    ResetProducts();
}

/**
 * stops the conveyor 
 * 
 */
void Conveyor::Stop()
{
    mIsRunning = false;
}

/**
 * resets the products on the conveyor
 * 
 */
void Conveyor::ResetProducts()
{
    ProductVisitor visitor;
    for (const auto& item : GetGame()->GetItems())
    {
        item->Accept(&visitor);
    }

    for (auto& product : visitor.GetProducts())
    {
        if (product->IsOnConveyor(this))
        {
            product->ResetPosition();
        }
    }
}

/**
 * draws the conveyor and its panel
 * 
 * @param graphics the graphics context
 */
void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (!graphics) return;
    wxBitmap conveyorBackground(conveyorBackImage, wxBITMAP_TYPE_PNG);
    graphics->DrawBitmap(conveyorBackground, mX - (conveyorBackground.GetWidth() / 2),
                         mY - (mHeight / 2), conveyorBackground.GetWidth(), mHeight);

    // Draw the conveyor belt twice to create a continuous scrolling effect
    wxBitmap conveyorBelt(L"images/conveyor-belt.png", wxBITMAP_TYPE_PNG);
    graphics->DrawBitmap(conveyorBelt, mX - (conveyorBelt.GetWidth() / 2),
                         mY - (mHeight / 2) + mBeltOffset, conveyorBelt.GetWidth(), mHeight);
    graphics->DrawBitmap(conveyorBelt, mX - (conveyorBelt.GetWidth() / 2),
                         mY - (mHeight / 2) + mBeltOffset - mHeight, conveyorBelt.GetWidth(), mHeight);

    // Draw the control panel based on conveyor state
    wxBitmap panelBitmap = mIsRunning
                               ? wxBitmap(L"images/conveyor-switch-start.png", wxBITMAP_TYPE_PNG)
                               : wxBitmap(L"images/conveyor-switch-stop.png", wxBITMAP_TYPE_PNG);
    graphics->DrawBitmap(panelBitmap, mX + mPanelLocation.x, mY + mPanelLocation.y,
                         panelBitmap.GetWidth(), panelBitmap.GetHeight());
}


/**
 * checks if the start button is clicked
 * 
 * @param mouseX  the x position of the mouse
 * @param mouseY  the y position of the mouse
 * @return true if the start button is clicked
 */
bool Conveyor::CheckStartButtonClick(int mouseX, int mouseY) const
{
    wxRect startRect(mX + mPanelLocation.x + StartButtonRect.GetX(),
                     mY + mPanelLocation.y + StartButtonRect.GetY(),
                     StartButtonRect.GetWidth(), StartButtonRect.GetHeight());
    return startRect.Contains(wxPoint(mouseX, mouseY));
}

/**
 * checks if the stop button is clicked
 * 
 * @param mouseX the x position of the mouse
 * @param mouseY  the y position of the mouse
 * @return true if the stop button is clicked
 */
bool Conveyor::CheckStopButtonClick(int mouseX, int mouseY) const
{
    wxRect stopRect(mX + mPanelLocation.x + StopButtonRect.GetX(),
                    mY + mPanelLocation.y + StopButtonRect.GetY(),
                    StopButtonRect.GetWidth(), StopButtonRect.GetHeight());
    return stopRect.Contains(wxPoint(mouseX, mouseY));
}

/**
 * gets the x position of the conveyor
 * 
 * @return int the x position
 */
int Conveyor::GetX() const
{
    return mX;
}

/**
 * gets the y position of the conveyor
 * 
 * @return int the y position
 */
int Conveyor::GetY() const
{
    return mY;
}

/**
 * gets the speed of the conveyor
 * 
 * @return double the speed
 */
double Conveyor::GetSpeed() const
{
    return mSpeed;
}

/**
 * checks if the conveyor is running
 * 
 * @return true if the conveyor is running
 */
bool Conveyor::IsRunning() const
{
    return mIsRunning;
}
