/**
* @file Conveyor.cpp
 * @author Martin Sattam
 */

#include "Conveyor.h"
#include <wx/graphics.h>
#include <wx/bitmap.h>

// Initialize static button rectangles
const wxRect Conveyor::StartButtonRect(35, 29, 95, 36);
const wxRect Conveyor::StopButtonRect(35, 87, 95, 36);

// Define XML level path as a constant (adjust based on user level)
const std::wstring LevelXMLFile = L"levels/level1.xml";  // Example level file

const std::wstring conveyorBackImage = L"images/conveyor-back.png";


Conveyor::Conveyor(Game* game,int x, int y, int speed, int height, const wxPoint& panelLocation)
    : Item(game, conveyorBackImage),  // Pass the appropriate XML file to the Item constructor
      mX(x), mY(y), mSpeed(speed), mHeight(height), mPanelLocation(panelLocation), mIsRunning(false) {
    // Calculate mWidth here based on the aspect ratio of the conveyor image if needed.
}

void Conveyor::Start() {
    mIsRunning = true;
    ResetProducts();  // Reset products to their initial positions
}

void Conveyor::Stop() {
    mIsRunning = false;
}

void Conveyor::ResetProducts() {
    // Logic to reset product positions to their initial placement as defined in the XML.
}

void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> graphics, int mouseX, int mouseY)
{
        // Load and draw the conveyor background image
    wxBitmap conveyorBackground(L"images/conveyor-back.png", wxBITMAP_TYPE_PNG);
    graphics->DrawBitmap(conveyorBackground, mX - (conveyorBackground.GetWidth() / 2), mY - (mHeight / 2), conveyorBackground.GetWidth(), mHeight);

    // Load and draw the conveyor belt image twice to simulate motion
    wxBitmap conveyorBelt(L"images/conveyor-belt.png", wxBITMAP_TYPE_PNG);
    graphics->DrawBitmap(conveyorBelt, mX - (conveyorBelt.GetWidth() / 2), mY - (mHeight / 2), conveyorBelt.GetWidth(), mHeight);
    // graphics->DrawBitmap(conveyorBelt, mX - (conveyorBelt.GetWidth() / 2) + conveyorBelt.GetWidth(), mY - (mHeight / 2), conveyorBelt.GetWidth(), mHeight);

    // Load and draw the appropriate control panel image (based on whether the conveyor is running)
    wxBitmap panelBitmap = mIsRunning ? wxBitmap(L"images/conveyor-switch-start.png", wxBITMAP_TYPE_PNG)
                                      : wxBitmap(L"images/conveyor-switch-stop.png", wxBITMAP_TYPE_PNG);
    graphics->DrawBitmap(panelBitmap, mX + mPanelLocation.x, mY + mPanelLocation.y, panelBitmap.GetWidth(), panelBitmap.GetHeight());

    // Set up the button rectangles for the start and stop buttons
    wxRect startRect(mX + mPanelLocation.x + StartButtonRect.GetX(),
                     mY + mPanelLocation.y + StartButtonRect.GetY(),
                     StartButtonRect.GetWidth(), StartButtonRect.GetHeight());

    wxRect stopRect(mX + mPanelLocation.x + StopButtonRect.GetX(),
                    mY + mPanelLocation.y + StopButtonRect.GetY(),
                    StopButtonRect.GetWidth(), StopButtonRect.GetHeight());

    // Draw rings around buttons if they are being pressed (for visual feedback)
    if (CheckStartButtonClick(mouseX, mouseY)) {
        wxPen ringPen(*wxGREEN, 3);
        graphics->SetPen(ringPen);
        graphics->SetBrush(wxNullBrush);
        graphics->DrawRectangle(startRect.GetX(), startRect.GetY(), startRect.GetWidth(), startRect.GetHeight());
    }

    if (CheckStopButtonClick(mouseX, mouseY)) {
        wxPen ringPen(*wxRED, 3);
        graphics->SetPen(ringPen);
        graphics->SetBrush(wxNullBrush);
        graphics->DrawRectangle(stopRect.GetX(), stopRect.GetY(), stopRect.GetWidth(), stopRect.GetHeight());
    }
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




