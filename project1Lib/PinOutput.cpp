/**
 * @file PinOutput.cpp
 * @author Praseedha Vinukonda
 */

// PinOutput.cpp
#include "pch.h"
#include "PinOutput.h"
#include "PinInput.h"
#include "States.h"

const wxColour PinOutput::ConnectionColorZero = *wxBLACK; // Black
const wxColour PinOutput::ConnectionColorOne = *wxRED; // Red
const wxColour PinOutput::ConnectionColorUnknown = wxColour(128, 128, 128); // Grey

void PinOutput::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    wxColour colorToUse;
    if (mConnectedPins.empty())
    {
        colorToUse = ConnectionColorUnknown; // No connection
    }
    else
    {
        // Use the current state to determine the color
        if (mCurrentState == States::One)
        {
            colorToUse = ConnectionColorOne; // Red
        }
        else if (mCurrentState == States::Zero)
        {
            colorToUse = ConnectionColorZero; // Black
        }
        else
        {
            colorToUse = ConnectionColorUnknown; // Grey
        }
    }
    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxBLACK_BRUSH);

    // Draw the pin circle
    graphics->DrawEllipse(mX - PinSize, mY - PinSize / 2, PinSize, PinSize);

    // Draw the line to the left
    graphics->StrokeLine(mX, mY, mX, mY);

    // Draw connections to input pins
    for (auto inputPin : mConnectedPins)
    {
        DrawConnection(graphics, inputPin);
    }
}

void PinOutput::UpdateState()
{
    // Check the states of the connected input pins
    States newState = States::Unknown;
    for (auto inputPin : mConnectedPins)
    {
        States inputState = inputPin->GetCurrentState();
        if (inputState == States::One)
        {
            newState = States::One; // If any input is 1, output is 1
            break;
        }
        else if (inputState == States::Zero)
        {
            newState = States::Zero; // If all inputs are 0, output is 0
        }
    }

    // Update the current state of the output pin
    mCurrentState = newState;
}

void PinOutput::OnDrag(double x, double y)
{
    if (mDragging)
    {
        // Check for connections to input pins after dragging
        for (auto inputPin : mConnectedPins)
        {
            if (inputPin->HitTest(x, y)) // Assuming HitTest checks if the pin is in range
            {
                ConnectTo(inputPin); // Connect if the input pin is hit
            }
        }
    }

    mDragging = false; // Reset dragging state
}

void PinOutput::ConnectTo(PinInput* pin)
{
    if (pin && std::find(mConnectedPins.begin(), mConnectedPins.end(), pin) == mConnectedPins.end())
    {
        mConnectedPins.push_back(pin);
        pin->ConnectTo(this);
    }
}

bool PinOutput::HitTest(double x, double y) const
{
    // Calculate the distance from the click point to the center of the pin
    double distance = std::sqrt(std::pow(x - mX, 2) + std::pow(y - mY, 2));
    return distance <= (PinSize / 2.0);
}

void PinOutput::DisconnectFrom(PinInput* pin)
{
    auto it = std::find(mConnectedPins.begin(), mConnectedPins.end(), pin);
    if (it != mConnectedPins.end())
    {
        mConnectedPins.erase(it);
        pin->ConnectTo(nullptr);
    }
}

void PinOutput::SetLocation(double x, double y)
{
    // Assuming you have a member variable `mDragging` to indicate the dragging state
    mDragging = true; // Set dragging to true
    mX = x; // Update the X position
    mY = y; // Update the Y position
    // Reset any connections or states if necessary
    // For example, if you have a member variable for current connections, you might want to clear it
}

void PinOutput::DrawConnection(std::shared_ptr<wxGraphicsContext> graphics, PinInput* inputPin)
{
    double startX = GetX();
    double startY = GetY();
    double endX = inputPin->GetX();
    double endY = inputPin->GetY();

    double offset = std::min(BezierMaxOffset, std::abs(endX - startX));

    wxPoint2DDouble p1(startX, startY);
    wxPoint2DDouble p2(startX + offset, startY);
    wxPoint2DDouble p3(endX - offset, endY);
    wxPoint2DDouble p4(endX, endY);

    graphics->SetPen(wxPen(*wxBLACK, LineWidth));
    graphics->StrokeLine(p1.m_x, p1.m_y, p2.m_x, p2.m_y);
    graphics->StrokeLine(p3.m_x, p3.m_y, p4.m_x, p4.m_y);

    wxGraphicsPath path = graphics->CreatePath();
    path.MoveToPoint(p2);
    path.AddCurveToPoint(p2.m_x + offset / 2, p2.m_y, p3.m_x - offset / 2, p3.m_y, p3.m_x, p3.m_y);
    graphics->StrokePath(path);
}
