/**
 * @file Gate.cpp
 * @author Praseedha Vinukonda
 */

#include "pch.h"
#include "Gate.h"
#include <wx/graphics.h>

// Define constant sizes for gates (kept in Gate.h)
bool Gate::HitTest(int x, int y)
{
    return mPath.Contains(x,y);

}
void Gate::OnMouseClick(double x, double y) {
    for (const auto& gate : gates) {
        if (gate->HitTest(x, y)) {
            // Store the grabbed gate for dragging
            mGrabbedGate = gate;
            break;  // Exit after the first gate is found
        }
    }
}

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

    // Key points for the rectangle and semicircle
    wxPoint2DDouble p1(x - w / 2, y + h / 2);   // Bottom left of the rectangle
    wxPoint2DDouble p2(x + w / 4, y + h / 2);   // Bottom right (before the arc)
    wxPoint2DDouble p3(x + w / 4, y - h / 2);   // Top right (before the arc)
    wxPoint2DDouble p4(x - w / 2, y - h / 2);   // Top left of the rectangle

    // Create the path for the AND gate (rectangle + arc for the right side)
    path.MoveToPoint(p1);  // Move to bottom left
    path.AddLineToPoint(p2);  // Draw a line to the bottom right corner (before the arc)
    path.AddArc(x + w / 4, y, h / 2, M_PI / 2, -M_PI / 2, false);  // Semicircle arc from bottom to top
    path.AddLineToPoint(p3);  // Line from the top of the arc to the top right corner
    path.AddLineToPoint(p4);  // Line back to top left
    path.CloseSubpath();      // Close the rectangle

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

    // The location and size
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();  // Width of the NOT gate
    auto h = GetHeight(); // Height of the NOT gate

    // Key points for the triangle and circle
    wxPoint2DDouble p1(x - w / 2, y + h / 2);   // Bottom left of the triangle
    wxPoint2DDouble p2(x - w / 2, y - h / 2);   // Top left of the triangle
    wxPoint2DDouble p3(x + w / 2, y);            // Point of the triangle (right)

    // Create the path for the NOT gate (triangle)
    path.MoveToPoint(p1);                          // Move to bottom left of triangle
    path.AddLineToPoint(p2);                       // Draw line to top left of triangle
    path.AddLineToPoint(p3);                       // Draw line to the point of the triangle
    path.CloseSubpath();                           // Close the triangle

    // Draw the triangle part of the NOT gate
    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->DrawPath(path);

    // Draw the inversion circle at the point of the triangle using DrawEllipse
    graphics->DrawEllipse(x + w / 2 - h / 4, y - h / 4, h / 2, h / 2); // Adjust to draw a circle
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

    // The location and size
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();  // Width of the SR flip-flop gate
    auto h = GetHeight(); // Height of the SR flip-flop gate

    // Draw the body of the SR flip-flop (rectangle)
    path.AddRectangle(x - w / 2, y - h / 2, w, h);

    // Draw the input and output connections using a path
    wxPoint2DDouble p1(x - w / 2, y - h / 2 + 10);   // Input S
    wxPoint2DDouble p2(x - w / 2 - 20, y - h / 2 + 10); // Input S connection point
    wxPoint2DDouble p3(x - w / 2, y + h / 2 - 10);   // Output Q
    wxPoint2DDouble p4(x + w / 2 + 20, y + h / 2 - 10); // Output Q connection point
    wxPoint2DDouble p5(x + w / 2, y + h / 2 - 10);   // Output Q'

    // Create path for the input and output lines
    path.MoveToPoint(p1); // Move to Input S
    path.AddLineToPoint(p2); // Draw line for Input S connection
    path.MoveToPoint(p3); // Move to Output Q
    path.AddLineToPoint(p4); // Draw line for Output Q connection
    path.MoveToPoint(p5); // Move to Output Q'

    // Draw the SR flip-flop gate
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
