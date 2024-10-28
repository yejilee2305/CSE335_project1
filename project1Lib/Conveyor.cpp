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
        // Adjust the belt offset to create a downward scrolling effect
        mBeltOffset += mSpeed;
        if (mBeltOffset >= mHeight) {
            mBeltOffset -= mHeight;  // Loop the offset to simulate continuous movement
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

void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    if (!graphics) return;

    // Draw conveyor background
    wxBitmap conveyorBackground(conveyorBackImage, wxBITMAP_TYPE_PNG);
    graphics->DrawBitmap(conveyorBackground, mX - (conveyorBackground.GetWidth() / 2),
                         mY - (mHeight / 2), conveyorBackground.GetWidth(), mHeight);

    // Draw the conveyor belt twice for a continuous scrolling effect
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

    // Temporary simulated product placement based on time (for visual effect only)
    if (mIsRunning) {
        // Define initial positions and spacing
        int initialProductY = mY - (mHeight / 2);
        int spacing = 100;

        // Loop to draw several products at regular intervals on the conveyor
        for (int i = 0; i < 4; ++i) {  // Adjust number as needed
            int productY = initialProductY + (mBeltOffset + i * spacing) % mHeight;
            graphics->SetBrush(*wxGREEN_BRUSH);  // Example product color
            graphics->DrawRectangle(mX - 20, productY, 40, 40);  // Draw a square as a product
        }
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
void Conveyor::AddProduct(std::shared_ptr<Product> product) {
    //mProducts.push_back(product);
}




