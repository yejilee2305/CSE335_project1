/**
 * @file Gate.cpp
 * @author Praseedha Vinukonda
 */

#include "pch.h"
#include "Gate.h"
#include "Item.h"
//including ids
#include "ids.h"

ORGate::ORGate() : inputA(States::Unknown), inputB(States::Unknown) {}

ANDGate::ANDGate() : inputA(States::Unknown), inputB(States::Unknown) {}

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
NOTGate::NOTGate() : inputA(States::Unknown) {}
const wxSize NotGateSize(50, 50);
void NOTGate::SetInputA(States state) {
    inputA = state;
}

States NOTGate::ComputeOutput() {
    if (inputA == States::Unknown) {
        return States::Unknown;
    }
    return (inputA == States::One) ? States::Zero : States::One;
}

void NOTGate::Draw(wxGraphicsContext* graphics) {
    auto path = graphics->CreatePath();
    path.AddRectangle(100, 100, NotGateSize.GetWidth(), NotGateSize.GetHeight());

    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->DrawPath(path);
}

SRFlipFlopGate::SRFlipFlopGate() : inputS(States::Unknown), inputR(States::Unknown), outputQ(States::Unknown), outputQPrime(States::Unknown) {}

const wxSize SRFlipFlopSize(50, 75);
const int SRFlipFlopLabelMargin = 3;

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

void SRFlipFlopGate::Draw(wxGraphicsContext* graphics) {
    auto path = graphics->CreatePath();
    path.AddRectangle(150, 150, SRFlipFlopSize.GetWidth(), SRFlipFlopSize.GetHeight());

    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->DrawPath(path);

    auto font = graphics->CreateFont(15, L"Arial", wxFONTFLAG_BOLD, *wxBLACK);
    graphics->SetFont(font);
    graphics->DrawText(L"S", 150 + SRFlipFlopLabelMargin, 150 + SRFlipFlopLabelMargin);
    graphics->DrawText(L"R", 150 + SRFlipFlopLabelMargin, 150 + SRFlipFlopSize.GetHeight() - SRFlipFlopLabelMargin);
}

DFlipFlopGate::DFlipFlopGate() : inputD(States::Unknown), clock(States::Unknown), outputQ(States::Unknown), outputQPrime(States::Unknown) {}

const wxSize DFlipFlopSize(50, 75);
const int DFlipFlopLabelMargin = 3;
const int DFlipFlopClockSize = 10;

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

void DFlipFlopGate::Draw(wxGraphicsContext* graphics) {
    auto path = graphics->CreatePath();
    path.AddRectangle(200, 200, DFlipFlopSize.GetWidth(), DFlipFlopSize.GetHeight());

    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->DrawPath(path);

    auto font = graphics->CreateFont(15, L"Arial", wxFONTFLAG_BOLD, *wxBLACK);
    graphics->SetFont(font);
    graphics->DrawText(L"D", 200 + DFlipFlopLabelMargin, 200 + DFlipFlopLabelMargin);
}