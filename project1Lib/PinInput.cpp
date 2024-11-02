/**
 * @file PinInput.cpp
 * @author Praseedha Vinukonda
 */

// PinInput.cpp
#include "pch.h"
#include "PinInput.h"
#include "PinOutput.h"

/**
 * Draw functionality
 */
void PinInput::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxBLACK_BRUSH);

    // Draw the line to the right (towards the gate)
    graphics->StrokeLine(mX, mY, mX + DefaultLineLength, mY);

    // Draw the pin circle at the left end of the line
    graphics->DrawEllipse(mX - PinSize/2, mY - PinSize/2, PinSize, PinSize);
}
/**
 * connect to functions
 */
void PinInput::ConnectToOutput(PinOutput* pin)
{
    if (pin && std::find(mConnectedPins.begin(), mConnectedPins.end(), pin) == mConnectedPins.end())
    {
        mConnectedPins.push_back(pin);
        mConnectedPin = pin; // Ensure mConnectedPin is set here
    }
}

/**
 * get connected gate
 */
Gate* PinInput::GetConnectedGate() const {
    return mConnectedPin ? mConnectedPin->GetParentGate() : nullptr;
}
/**
 * set connection function
 */
void PinInput::SetConnection(PinOutput* outputPin) {
    mConnectedPin = outputPin;
}

/**
 * Set location
 */
void PinInput::SetLocation(double x, double y) {
    mX = x; // Set the x coordinate
    mY = y; // Set the y coordinate
}