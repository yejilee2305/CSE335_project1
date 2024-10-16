/**
 * @file Gate.cpp
 * @author Praseedha Vinukonda
 */

#include "pch.h"
#include "Gate.h"

// Define constant sizes for gates (kept in Gate.h)


ORGate::ORGate() : inputA(States::Unknown), inputB(States::Unknown) {}

void ORGate::SetInputA(States state) {
    inputA = state;
}

void ORGate::SetInputB(States state) {
    inputB = state;
}

States ORGate::ComputeOutput() {
    if (inputA == States::Unknown || inputB == States::Unknown) {
        return States::Unknown;
    }
    return (inputA == States::One || inputB == States::One) ? States::One : States::Zero;
}

void ORGate::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    auto path = graphics->CreatePath();

    // The location and size
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

    // The three corner points of an OR gate
    wxPoint2DDouble p1(x - w / 2, y + h / 2);   // Bottom left
    wxPoint2DDouble p2(x + w / 2, y);            // Center right
    wxPoint2DDouble p3(x - w / 2, y - h / 2);   // Top left

    // Control points used to create the Bezier curves
    auto controlPointOffset1 = wxPoint2DDouble(w * 0.5, 0);
    auto controlPointOffset2 = wxPoint2DDouble(w * 0.75, 0);
    auto controlPointOffset3 = wxPoint2DDouble(w * 0.2, 0);

    // Create the path for the gate
    path.MoveToPoint(p1);
    path.AddCurveToPoint(p1 + controlPointOffset1, p1 + controlPointOffset2, p2);
    path.AddCurveToPoint(p3 + controlPointOffset2, p3 + controlPointOffset1, p3);
    path.AddCurveToPoint(p3 + controlPointOffset3, p1 + controlPointOffset3, p1);
    path.CloseSubpath();

    // Draw the path
    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->DrawPath(path);

}

ANDGate::ANDGate() : inputA(States::Unknown), inputB(States::Unknown) {}

void ANDGate::SetInputA(States state) {
    inputA = state;
}

void ANDGate::SetInputB(States state) {
    inputB = state;
}

States ANDGate::ComputeOutput() {
    if (inputA == States::Unknown || inputB == States::Unknown) {
        return States::Unknown;
    }
    return (inputA == States::One && inputB == States::One) ? States::One : States::Zero;
}

void ANDGate::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    auto path = graphics->CreatePath();

    // The location and size
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

    // The three corner points of an AND gate
    wxPoint2DDouble p1(x - w / 2, y + h / 2);   // Bottom left
    wxPoint2DDouble p2(x + w / 2, y);            // Center right
    wxPoint2DDouble p3(x - w / 2, y - h / 2);   // Top left

    // Control points used to create the Bezier curves
    auto controlPointOffset1 = wxPoint2DDouble(w * 0.75, 0);

    // Create the path for the gate
    path.MoveToPoint(p1);
    path.AddCurveToPoint(p1 + controlPointOffset1, p2, p2);
    path.AddLineToPoint(p3);
    path.AddCurveToPoint(p3 + controlPointOffset1, p1, p1);
    path.CloseSubpath();

    // Draw the path
    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->DrawPath(path);
}

NOTGate::NOTGate() : inputA(States::Unknown) {}

void NOTGate::SetInputA(States state) {
    inputA = state;
}

States NOTGate::ComputeOutput() {
    if (inputA == States::Unknown) {
        return States::Unknown;
    }
    return (inputA == States::One) ? States::Zero : States::One;
}

void NOTGate::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    auto path = graphics->CreatePath();
    path.AddRectangle(GetX() - NotGateSize.GetWidth() / 2, GetY() - NotGateSize.GetHeight() / 2,
                      NotGateSize.GetWidth(), NotGateSize.GetHeight());

    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->DrawPath(path);
}

SRFlipFlopGate::SRFlipFlopGate() : inputS(States::Unknown), inputR(States::Unknown),
                                    outputQ(States::Unknown), outputQPrime(States::Unknown) {}

void SRFlipFlopGate::SetInputS(States state) {
    inputS = state;
}

void SRFlipFlopGate::SetInputR(States state) {
    inputR = state;
}

States SRFlipFlopGate::ComputeOutput() {
    if (inputS == States::One && inputR == States::One) {
        outputQ = States::Unknown;
        outputQPrime = States::Unknown;
    } else if (inputS == States::One) {
        outputQ = States::One;
        outputQPrime = States::Zero;
    } else if (inputR == States::One) {
        outputQ = States::Zero;
        outputQPrime = States::One;
    }
    return outputQ;
}

void SRFlipFlopGate::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    auto path = graphics->CreatePath();
    path.AddRectangle(GetX() - SRFlipFlopSize.GetWidth() / 2, GetY() - SRFlipFlopSize.GetHeight() / 2,
                      SRFlipFlopSize.GetWidth(), SRFlipFlopSize.GetHeight());

    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->DrawPath(path);
}

DFlipFlopGate::DFlipFlopGate() : inputD(States::Unknown), clock(States::Unknown),
                                   outputQ(States::Unknown), outputQPrime(States::Unknown) {}

void DFlipFlopGate::SetInputD(States state) {
    inputD = state;
}

void DFlipFlopGate::SetClock(States state) {
    clock = state;
}

States DFlipFlopGate::ComputeOutput() {
    if (clock == States::One) {
        outputQ = inputD;
        outputQPrime = (inputD == States::One) ? States::Zero : States::One;
    }
    return outputQ;
}

void DFlipFlopGate::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    auto path = graphics->CreatePath();
    path.AddRectangle(GetX() - DFlipFlopSize.GetWidth() / 2, GetY() - DFlipFlopSize.GetHeight() / 2,
                      DFlipFlopSize.GetWidth(), DFlipFlopSize.GetHeight());

    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->DrawPath(path);
}
