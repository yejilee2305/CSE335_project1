/**
 * @file PinOutput.cpp
 * @author Praseedha Vinukonda
 */

// PinOutput.cpp
#include "pch.h"
#include "PinOutput.h"
#include "PinInput.h"

void PinOutput::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxBLACK_BRUSH);

    // Draw the pin circle
    graphics->DrawEllipse(mX - PinSize/2, mY - PinSize/2, PinSize, PinSize);

    // Draw the line to the left
    graphics->StrokeLine(mX - DefaultLineLength, mY, mX, mY);

    // Draw connections to input pins
    for (auto inputPin : mConnectedPins)
    {
        DrawConnection(graphics, inputPin);
    }
}

void PinOutput::ConnectTo(PinInput* pin)
{
    mConnectedPins.push_back(pin);
    pin->ConnectTo(this);
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

void PinOutput::DrawConnection(std::shared_ptr<wxGraphicsContext> graphics, PinInput* inputPin)
{
    double startX = mX;
    double startY = mY;
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
    path.AddCurveToPoint(p2.m_x + offset/2, p2.m_y, p3.m_x - offset/2, p3.m_y, p3.m_x, p3.m_y);
    graphics->StrokePath(path);
}