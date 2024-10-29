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

// Initialize static button rectangles
const wxRect Conveyor::StartButtonRect(35, 29, 95, 36);
const wxRect Conveyor::StopButtonRect(35, 87, 95, 36);

// Define XML level path as a constant (adjust based on user level)
const std::wstring LevelXMLFile = L"levels/level1.xml";  // Example level file

const std::wstring conveyorBackImage = L"images/conveyor-back.png";


Conveyor::Conveyor(Game* game, int x, int y, int speed, int height, const wxPoint& panelLocation)
    : Item(game, conveyorBackImage),
      mX(x), mY(y), mSpeed(speed), mHeight(height), mPanelLocation(panelLocation), mIsRunning(false) {  // Set mIsRunning to false initially
    // Other initialization code...
}


void Conveyor::Update(double elapsed) {
    //mIsRunning = true;  // Temporary hardcoding for testing
    if (mIsRunning) {
        mBeltOffset += mSpeed;
        //wxLogMessage("Updating mBeltOffset: %d", mBeltOffset);
        if (mBeltOffset >= mHeight) {
            mBeltOffset -= mHeight;
        }
        MoveProducts(elapsed);
    }
}

void Conveyor::MoveProducts(double elapsed) {
    ProductVisitor visitor;
    for (const auto& item : GetGame()->GetItems()) {
        item->Accept(&visitor);
    }

    for (const auto& product : visitor.GetProducts()) {
        if (product->IsOnConveyor(this)) {
            product->MoveDown(mSpeed * elapsed);
        }
    }
}

void Conveyor::Start() {
    mIsRunning = true;
    ResetProducts();
    //wxLogMessage("Conveyor started, mIsRunning=%d", mIsRunning);  // Confirm mIsRunning is set to true
}

void Conveyor::Stop() {
    mIsRunning = false;
    //wxLogMessage("Conveyor stopped, mIsRunning=%d", mIsRunning);  // Confirm mIsRunning is set to false
}


void Conveyor::ResetProducts() {
    ProductVisitor visitor;
    for (const auto& item : GetGame()->GetItems()) {
        item->Accept(&visitor);
    }

    for (auto& product : visitor.GetProducts()) {
        if (product->IsOnConveyor(this)) {
            product->ResetPosition();
        }
    }
}
void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    if (!graphics) return;
    //wxLogMessage("Drawing conveyor with mBeltOffset: %d", mBeltOffset);
    // Draw conveyor background
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
    wxBitmap panelBitmap = mIsRunning ? wxBitmap(L"images/conveyor-switch-start.png", wxBITMAP_TYPE_PNG)
                                      : wxBitmap(L"images/conveyor-switch-stop.png", wxBITMAP_TYPE_PNG);
    graphics->DrawBitmap(panelBitmap, mX + mPanelLocation.x, mY + mPanelLocation.y,
                         panelBitmap.GetWidth(), panelBitmap.GetHeight());

}


bool Conveyor::CheckStartButtonClick(int mouseX, int mouseY) const {
    wxRect startRect(mX + mPanelLocation.x + StartButtonRect.GetX(),
                     mY + mPanelLocation.y + StartButtonRect.GetY(),
                     StartButtonRect.GetWidth(), StartButtonRect.GetHeight());
    return startRect.Contains(wxPoint(mouseX, mouseY));
}

bool Conveyor::CheckStopButtonClick(int mouseX, int mouseY) const {
    wxRect stopRect(mX + mPanelLocation.x + StopButtonRect.GetX(),
                    mY + mPanelLocation.y + StopButtonRect.GetY(),
                    StopButtonRect.GetWidth(), StopButtonRect.GetHeight());
    return stopRect.Contains(wxPoint(mouseX, mouseY));
}

int Conveyor::GetX() const {
    return mX;
}

int Conveyor::GetY() const {
    return mY;
}

int Conveyor::GetSpeed() const {
    return mSpeed;
}

bool Conveyor::IsRunning() const {
    return mIsRunning;
}




