/**
 * @file PinInput.cpp
 * @author Praseedha Vinukonda
 */

// PinInput.cpp
#include "pch.h"
#include "PinInput.h"

void PinInput::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxBLACK_BRUSH);

    // Draw the pin circle
    graphics->DrawEllipse(mX - PinSize/2, mY - PinSize/2, PinSize, PinSize);

    // Draw the line to the right
    graphics->StrokeLine(mX, mY, mX + DefaultLineLength, mY);
}

void PinInput::ConnectTo(PinOutput* pin)
{
    mConnectedPin = pin;
}