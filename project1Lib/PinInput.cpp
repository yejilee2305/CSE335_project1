/**
 * @file PinInput.cpp
 * @author Praseedha Vinukonda
 */

#include "pch.h"
#include "PinInput.h"

void PinInput::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxBLACK_BRUSH);
    graphics->DrawEllipse(mX - PinSize/2, mY - PinSize/2, PinSize, PinSize);
}

void PinInput::ConnectTo(PinOutput* pin)
{
    mConnectedPin = pin;
}
