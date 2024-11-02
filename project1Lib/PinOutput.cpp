/**
 * @file PinOutput.cpp
 * @author Praseedha Vinukonda
 */

// PinOutput.cpp
#include "pch.h"
#include "PinOutput.h"
#include "PinInput.h"
#include "States.h"

///< Color for zero (low) state: black
const wxColour PinOutput::ConnectionColorZero = *wxBLACK; // Black
///< Color for one (high) state: red
const wxColour PinOutput::ConnectionColorOne = *wxRED; // Red
///< Color for unknown state: grey
const wxColour PinOutput::ConnectionColorUnknown = wxColour(128, 128, 128); // Grey

/**
 * Draws the output pin and its connections.
 */
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
/**
 * Update State
 */
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
/**
 * OnDrag functionality
 */
void PinOutput::OnDrag(double x, double y)
{
    if (mDragging)
    {
        // Check for connections to input pins after dragging
        for (auto inputPin : mConnectedPins)
        {
            if (inputPin->HitTest(x, y)) // Assuming HitTest checks if the pin is in range
            {
                ConnectToInput(inputPin); // Connect if the input pin is hit
            }
        }
    }

    mDragging = false; // Reset dragging state
}
/**
 * Connection
 */
void PinOutput::ConnectToInput(PinInput* pin)
{
    // checks pin is not nullptr and checks if pin is already in mConnectedPins
    // ensure pin is valid and not connected already
    if (pin && std::find(mConnectedPins.begin(), mConnectedPins.end(), pin) == mConnectedPins.end())
    {
        // add pin to mConnectedPins vector, PinOutput is now conected to pin
        mConnectedPins.push_back(pin);
        // add line to mConectedPins
        pin->ConnectToOutput(this);
    }
}
/**
 * Hittest function
 */
bool PinOutput::HitTest(double x, double y) const
{
    // Calculate the distance from the click point to the center of the pin
    double distance = std::sqrt(std::pow(x - mX, 2) + std::pow(y - mY, 2));
    return distance <= (PinSize / 2.0);
}
/**
 * Disconnect from function for pins
 */
void PinOutput::DisconnectFrom(PinInput* pin)
{
    auto it = std::find(mConnectedPins.begin(), mConnectedPins.end(), pin);
    if (it != mConnectedPins.end())
    {
        mConnectedPins.erase(it);
        pin->ConnectToOutput(nullptr);
    }
}
/**
 * Set location for pin output
 */
void PinOutput::SetLocation(double x, double y)
{
    // Assuming you have a member variable `mDragging` to indicate the dragging state
    mDragging = true; // Set dragging to true
    mX = x; // Update the X position
    mY = y; // Update the Y position
    // Reset any connections or states if necessary
    // For example, if you have a member variable for current connections, you might want to clear it
}
/**
 * Draw connection pin output
 */
void PinOutput::DrawConnection(std::shared_ptr<wxGraphicsContext> graphics, PinInput* inputPin)
{
    // start and end poinrts
    wxPoint2DDouble p1(GetX(), GetY());
    wxPoint2DDouble p4(inputPin->GetX(), inputPin->GetY());

    double distance = std::abs(p4.m_x - p1.m_x);
    double offset = std::min(BezierMaxOffset, distance);

    // control points
    wxPoint2DDouble p2(p1.m_x + offset, p1.m_y);
    wxPoint2DDouble p3(p4.m_x - offset, p4.m_y);

    wxColour colorToUse;
    States state = GetCurrentState();

    if (state == States::One)
    {
        colorToUse = ConnectionColorOne; // Red
    }
    else if (state == States::Zero)
    {
        colorToUse = ConnectionColorZero; // Black
    }
    else
    {
        colorToUse = ConnectionColorUnknown; // Grey
    }

    // draws the curve
    wxGraphicsPath path = graphics->CreatePath();
    path.MoveToPoint(p1);
    path.AddCurveToPoint(p2.m_x, p2.m_y, p3.m_x, p3.m_y, p4.m_x, p4.m_y);
    graphics->SetPen(wxPen(colorToUse, LineWidth));
    graphics->StrokePath(path);
}
