/**
* @file Conveyor.cpp
 * @author Martin Sattam
 */

#include "pch.h"
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

void Conveyor::Update() {
    if (mIsRunning) {
        // Update belt offset for visual scrolling
        mBeltOffset += mSpeed;
        if (mBeltOffset >= mHeight) {
            mBeltOffset = 0;
        }

        // Move each product downwards by conveyor speed
        for (auto& product : mProducts) {
            int newY = product->GetY() + mSpeed;
            product->SetY(newY);  // Ensure Product class has SetY method
        }
    }
}

void Conveyor::Start() {
    mIsRunning = true;
    wxLogMessage("Conveyor started");  // Debug message to confirm start
}

void Conveyor::Stop() {
    mIsRunning = false;
    wxLogMessage("Conveyor stopped");  // Debug message to confirm stop
}

void Conveyor::ResetProducts() {
    // Logic to reset product positions to their initial placement as defined in the XML.
}
/**
void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (!graphics) return;

    // Draw the conveyor background only once
    wxBitmap conveyorBackground(L"images/conveyor-back.png", wxBITMAP_TYPE_PNG);
    graphics->DrawBitmap(conveyorBackground, mX - (conveyorBackground.GetWidth() / 2), mY - (mHeight / 2), conveyorBackground.GetWidth(), mHeight);

    // Draw the conveyor belt
    wxBitmap conveyorBelt(L"images/conveyor-belt.png", wxBITMAP_TYPE_PNG);
    graphics->DrawBitmap(conveyorBelt, mX - (conveyorBelt.GetWidth() / 2), mY - (mHeight / 2), conveyorBelt.GetWidth(), mHeight);

    // Load and draw the appropriate control panel image based on conveyor's running state
    wxBitmap panelBitmap = mIsRunning ? wxBitmap(L"images/conveyor-switch-start.png", wxBITMAP_TYPE_PNG)
                                      : wxBitmap(L"images/conveyor-switch-stop.png", wxBITMAP_TYPE_PNG);
    graphics->DrawBitmap(panelBitmap, mX + mPanelLocation.x, mY + mPanelLocation.y, panelBitmap.GetWidth(), panelBitmap.GetHeight());

    // Draw start/stop button rings for visual feedback if they are clicked
    wxRect startRect(mX + mPanelLocation.x + StartButtonRect.GetX(),
                     mY + mPanelLocation.y + StartButtonRect.GetY(),
                     StartButtonRect.GetWidth(), StartButtonRect.GetHeight());
    wxRect stopRect(mX + mPanelLocation.x + StopButtonRect.GetX(),
                    mY + mPanelLocation.y + StopButtonRect.GetY(),
                    StopButtonRect.GetWidth(), StopButtonRect.GetHeight());

    if (CheckStartButtonClick(mX, mY)) {
        wxPen ringPen(wxColour(0, 255, 0), 3);  // Green ring for Start button
        graphics->SetPen(ringPen);
        graphics->DrawRectangle(startRect.GetX(), startRect.GetY(), startRect.GetWidth(), startRect.GetHeight());
    }

    if (CheckStopButtonClick(mX, mY)) {
        wxPen ringPen(wxColour(255, 0, 0), 3);  // Red ring for Stop button
        graphics->SetPen(ringPen);
        graphics->DrawRectangle(stopRect.GetX(), stopRect.GetY(), stopRect.GetWidth(), stopRect.GetHeight());
    }
}
*/
void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    if (!graphics) return;

    // Draw the conveyor background (stationary part)
    wxBitmap conveyorBackground(L"images/conveyor-back.png", wxBITMAP_TYPE_PNG);
    graphics->DrawBitmap(conveyorBackground, mX - (conveyorBackground.GetWidth() / 2), mY - (mHeight / 2), conveyorBackground.GetWidth(), mHeight);

    // Draw the control panel image based on running state
    wxBitmap panelBitmap = mIsRunning ? wxBitmap(L"images/conveyor-switch-start.png", wxBITMAP_TYPE_PNG)
                                      : wxBitmap(L"images/conveyor-switch-stop.png", wxBITMAP_TYPE_PNG);
    graphics->DrawBitmap(panelBitmap, mX + mPanelLocation.x, mY + mPanelLocation.y, panelBitmap.GetWidth(), panelBitmap.GetHeight());

    // Draw the conveyor belt using mBeltOffset for vertical scrolling
    wxBitmap conveyorBelt(L"images/conveyor-belt.png", wxBITMAP_TYPE_PNG);
    int beltHeight = conveyorBelt.GetHeight();

    // Draw two copies of the belt to create a seamless scrolling effect
    graphics->DrawBitmap(conveyorBelt, mX - (conveyorBelt.GetWidth() / 2), mY - (mHeight / 2) + mBeltOffset - beltHeight, conveyorBelt.GetWidth(), beltHeight);
    graphics->DrawBitmap(conveyorBelt, mX - (conveyorBelt.GetWidth() / 2), mY - (mHeight / 2) + mBeltOffset, conveyorBelt.GetWidth(), beltHeight);
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
void Conveyor::AddProduct(std::shared_ptr<Product> product) {
    mProducts.push_back(product);
}




