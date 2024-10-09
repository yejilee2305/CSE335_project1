/**
 * @file Gate.cpp
 * @author Praseedha Vinukonda
 */

#include "Gate.h"
#include "Item.h"

States ORGate::ComputeOutput() {
    if (inputA == States::Unknown || inputB == States::Unknown) {
        return States::Unknown;
    }
    if (inputA == States::One || inputB == States::One) {
        return States::One;
    }
    return States::Zero;
}

void ORGate::Draw(wxGraphicsContext* graphics) {
    auto path = graphics->CreatePath();

    double x = 100, y = 100, w = 75, h = 50;
    wxPoint2DDouble p1(x - w / 2, y + h / 2);
    wxPoint2DDouble p2(x + w / 2, y);
    wxPoint2DDouble p3(x - w / 2, y - h / 2);

    auto controlPointOffset1 = wxPoint2DDouble(w * 0.5, 0);
    auto controlPointOffset2 = wxPoint2DDouble(w * 0.75, 0);
    auto controlPointOffset3 = wxPoint2DDouble(w * 0.2, 0);

    path.MoveToPoint(p1);
    path.AddCurveToPoint(p1 + controlPointOffset1, p1 + controlPointOffset2, p2);
    path.AddCurveToPoint(p3 + controlPointOffset2, p3 + controlPointOffset1, p3);
    path.AddCurveToPoint(p3 + controlPointOffset3, p1 + controlPointOffset3, p1);
    path.CloseSubpath();

    // Drawing the gate
    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->DrawPath(path);
}

States ANDGate::ComputeOutput() {
    if (inputA == States::Unknown || inputB == States::Unknown) {
        return States::Unknown;
    }
    if (inputA == States::One && inputB == States::One) {
        return States::One;
    }
    return States::Zero;
}

void ANDGate::Draw(wxGraphicsContext* graphics) {
    auto path = graphics->CreatePath();

    double x = 200, y = 100, w = 75, h = 50;
    wxPoint2DDouble p1(x - w / 2, y + h / 2);
    wxPoint2DDouble p2(x + w / 2, y);
    wxPoint2DDouble p3(x - w / 2, y - h / 2);

    auto controlPointOffset1 = wxPoint2DDouble(w * 0.75, 0);

    path.MoveToPoint(p1);
    path.AddCurveToPoint(p1 + controlPointOffset1, p2, p2);
    path.AddLineToPoint(p3);
    path.AddCurveToPoint(p3 + controlPointOffset1, p1, p1);
    path.CloseSubpath();

    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->DrawPath(path);
}