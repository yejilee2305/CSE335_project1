/**
 * @file Wire.cpp
 * @author Praseedha Vinukonda
 */
 
// Wire.cpp
#include "pch.h"
#include "Wire.h"

Wire::Wire(PinOutput* outputPin, PinInput* inputPin)
    : mOutputPin(outputPin), mInputPin(inputPin)
{
    UpdateControlPoints();
}

void Wire::UpdateControlPoints()
{
    double startX = mOutputPin->GetX();
    double startY = mOutputPin->GetY();
    double endX = mInputPin->GetX();
    double endY = mInputPin->GetY();

    double offset = std::min(BezierMaxOffset, std::abs(endX - startX));

    mControlPoint1 = wxPoint2DDouble(startX + offset, startY);
    mControlPoint2 = wxPoint2DDouble(endX - offset, endY);
}


void Wire::Draw(wxGraphicsContext* gc, bool showControlPoints)
{
    wxPoint2DDouble startPoint(mOutputPin->GetX(), mOutputPin->GetY());
    wxPoint2DDouble endPoint(mInputPin->GetX(), mInputPin->GetY());

    gc->SetPen(wxPen(*wxBLACK, 2));
    wxGraphicsPath path = gc->CreatePath();
    path.MoveToPoint(startPoint);
    path.AddCurveToPoint(mControlPoint1, mControlPoint2, endPoint);
    gc->StrokePath(path);

    if (showControlPoints) {
        gc->SetPen(*wxRED_PEN);
        gc->SetBrush(*wxRED_BRUSH);
        gc->DrawEllipse(mControlPoint1.m_x - 3, mControlPoint1.m_y - 3, 6, 6);
        gc->DrawEllipse(mControlPoint2.m_x - 3, mControlPoint2.m_y - 3, 6, 6);
    }
}
