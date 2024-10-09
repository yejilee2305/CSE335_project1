/**
 * @file Conveyor.cpp
 * @author Martin Sattam
 */

#include "Conveyor.h"

Conveyor::Conveyor(int x, int y, int speed, int height, const wxPoint& panelLocation)
    : mX(x), mY(y), mSpeed(speed), mHeight(height), mPanelLocation(panelLocation), mIsRunning(false) {
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
    // Placeholder for now.
}

void Conveyor::Draw(wxGraphicsContext* graphics) {

}

bool Conveyor::CheckStartButtonClick(int mouseX, int mouseY) const
{
    wxRect startRect(mX + mPanelLocation.x + StartButtonRect.GetX(),
                 mY + mPanelLocation.y + StartButtonRect.GetY(),
                 StartButtonRect.GetWidth(), StartButtonRect.GetHeight());
    return startRect.Contains(wxPoint(mouseX, mouseY));
}

bool Conveyor::CheckStopButtonClick(int mouseX, int mouseY) const
{
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

