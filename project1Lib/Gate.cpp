/**
 * @file Gate.cpp
 * @author Praseedha Vinukonda
 */

#include "pch.h"
#include "Gate.h"
#include <wx/graphics.h>
#include <wx/dcclient.h>  // For wxPaintDC
#include <wx/dcbuffer.h>  // For wxAutoBufferedPaintDC
#include <wx/app.h>
#include <wx/event.h>

#include "PinInput.h"

// Define constant sizes for gates (kept in Gate.h)
/**
 * Tests if a point is within the gate's bounding box.
 *
 */
bool Gate::HitTest(double x, double y) const
{
    double left = GetX() - GetWidth() / 2;
    double right = GetX() + GetWidth() / 2;
    double top = GetY() - GetHeight() / 2;
    double bottom = GetY() + GetHeight() / 2;

    return (x >= left && x <= right && y >= top && y <= bottom);
}
// Setter functions to update the gate position
/**
 * Sets the position of the gate and updates pin positions accordingly.
 *
 */
void Gate::SetPosition(double x, double y) {
    mX = x;
    mY = y;
    UpdatePinPositions();
}
/**
 * Handles mouse click events by determining if a gate is clicked.
 *
 */
void Gate::OnMouseClick(double x, double y) {
    for (const auto& gate : gates) {
        if (gate->HitTest(x, y)) {
            // Store the grabbed gate for dragging
            mGrabbedGate = gate;
            break;  // Exit after the first gate is found
        }
    }
}
/**
 * Updates the positions of the input and output pins based on the gate's location and size.
 */
void Gate::UpdatePinPositions() {
    double x = GetX();
    double y = GetY();
    double w = GetWidth();
    double h = GetHeight();

    // Position input pins
    for (size_t i = 0; i < mInputPins.size(); ++i) {
        double yOffset = h * (i + 1) / (mInputPins.size() + 1) - h / 2;
        mInputPins[i].SetPosition(x - w / 2, y + yOffset);
    }

    // Position output pins
    for (size_t i = 0; i < mOutputPins.size(); ++i) {
        double yOffset = h * (i + 1) / (mOutputPins.size() + 1) - h / 2;
        mOutputPins[i].SetPosition(x + w / 2, y + yOffset);
    }
}
/**
 * Initializes the positions of pins on the gate.
 */
void Gate::InitializePins() {
    UpdatePinPositions();
}
/**
 * Constructor for the OR gate.
 *
 */
ORGate::ORGate(Game* game) : Gate(game, L""),
    inputA(States::Unknown), inputB(States::Unknown)
{
    mInputPins.emplace_back(PinInput());
    mInputPins.emplace_back(PinInput());
    mOutputPins.emplace_back(PinOutput());
    UpdatePinPositions();
}
/**
 * Sets the state of input pin A.
 *
 */
void ORGate::SetInputA(States state) {
    inputA = state;
}
/**
 * Sets the state of input pin B.
 *
 */
void ORGate::SetInputB(States state) {
    inputB = state;
}
/**
 * Sets the position of the OR gate and updates pin positions accordingly.
 */
void ORGate::SetPosition(double x, double y) {
    Gate::SetPosition(x, y);
    UpdatePinPositions();
}
/**
 * Gets a pointer to the specified input pin.
 */
PinInput* ORGate::GetInputPin(int index) {
    if (index >= 0 && index < mInputPins.size()) {
        return &mInputPins[index];
    }
    return nullptr;
}

/**
 * Gets a pointer to the output pin.
 */
PinOutput* ORGate::GetOutputPin() {
    if (!mOutputPins.empty()) {
        return &mOutputPins[0];
    }
    return nullptr;
}
/**
 * Connects an input pin of this gate to an output pin of another gate.
 */
void ORGate::ConnectInput(int inputIndex, PinOutput* outputPin) {
    if (inputIndex >= 0 && inputIndex < mInputPins.size()) {
        mInputPins[inputIndex].SetConnection(outputPin);
        outputPin->AddConnection(&mInputPins[inputIndex]);
    }
}
/**
 * Computes the output of the OR gate based on the states of its inputs.
 */
States ORGate::ComputeOutput() {
    if (inputA == States::Unknown || inputB == States::Unknown) {
        return States::Unknown;
    }
    return (inputA == States::One || inputB == States::One) ? States::One : States::Zero;
}
/**
 * Draws orgate
 */
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

    // Draw input and output lines
    graphics->SetPen(*wxBLACK_PEN);
    double curveOffset = w * 0.2; // Adjust this value to match the curve of your gate
    // Draw pins
    graphics->StrokeLine(x + w/2, y, x + w/2 + 20, y);
    for (auto& pin : mInputPins) {
        pin.Draw(graphics);
    }
    for (auto& pin : mOutputPins) {
        pin.Draw(graphics);
    }
}
/**
 *Upating the ORgate pins position
 */
void ORGate::UpdatePinPositions()
{
    double x = GetX();
    double y = GetY();
    double w = GetWidth();
    double h = GetHeight();
    double curveOffset = w * 0.2;

    // Position input pins so that the lines touch the gate's edge
    mInputPins[0].SetPosition(x - w/2 + curveOffset - PinInput::DefaultLineLength, y - h/4);
    mInputPins[1].SetPosition(x - w/2 + curveOffset - PinInput::DefaultLineLength, y + h/4);

    // Position output pin
    mOutputPins[0].SetPosition(x + w/2 + 20, y);
}
/**
 * Constructor for the AND gate.
 */
ANDGate::ANDGate(Game* game) : Gate(game, L""),
    inputA(States::Unknown), inputB(States::Unknown)
{
    mInputPins.emplace_back(PinInput());
    mInputPins.emplace_back(PinInput());
    mOutputPins.emplace_back(PinOutput());
    InitializePins();
}
/**
 * Sets the state of input pin A.
 */
void ANDGate::SetInputA(States state) {
    inputA = state;
}
/**
 * Sets the state of input pin B.
 */
void ANDGate::SetInputB(States state) {
    inputB = state;
}

/**
 * computes the output based on the states of the input pins
 * 
 * @return States
 */
States ANDGate::ComputeOutput() {
    if (inputA == States::Unknown || inputB == States::Unknown) {
        return States::Unknown;
    }
    return (inputA == States::One && inputB == States::One) ? States::One : States::Zero;
}
/**
 * Set positon of AND gate
 */
void ANDGate::SetPosition(double x, double y) {
    Gate::SetPosition(x, y);
    UpdatePinPositions();
}
/**
 * updating pin positions
 */
void ANDGate::UpdatePinPositions()
{
    double x = GetX();
    double y = GetY();
    double w = GetWidth();
    double h = GetHeight();

    // Position input pins at the left end of the input lines
    mInputPins[0].SetPosition(x - w/2 - 20, y - h/4);
    mInputPins[1].SetPosition(x - w/2 - 20, y + h/4);

    // Position output pin at the right end of the output line
    mOutputPins[0].SetPosition(x + w/2 + 20, y);
}
/**
 * drawing of the AND gate
 */
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
    path.MoveToPoint(p1);
    path.AddLineToPoint(p2);
    path.AddArc(x + w / 4, y, h / 2, M_PI / 2, -M_PI / 2, false);
    path.AddLineToPoint(p3);
    path.AddLineToPoint(p4);
    path.CloseSubpath();

    // Draw the path
    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->DrawPath(path);

    // Draw input lines
    graphics->StrokeLine(x - w/2, y - h/4, x - w/2 - 20, y - h/4);
    graphics->StrokeLine(x - w/2, y + h/4, x - w/2 - 20, y + h/4);

    // Draw output line
    graphics->StrokeLine(x + w/2, y, x + w/2 + 20, y);

    // Draw the pins
    for (auto& pin : mInputPins) {
        pin.Draw(graphics);
    }
    for (auto& pin : mOutputPins) {
        pin.Draw(graphics);
    }
}

/**
 * Constructor for the NOT gate.
 */
NOTGate::NOTGate(Game* game) : Gate(game, L""),
    inputA(States::Unknown)
{
    mInputPins.emplace_back(PinInput());
    mOutputPins.emplace_back(PinOutput());
    InitializePins();
    UpdatePinPositions();
}
/**
 * Set input of A
 */
void NOTGate::SetInputA(States state) {
    inputA = state;
}

/**
 * Compute output for NOT gate
 */
States NOTGate::ComputeOutput() {
    if (inputA == States::Unknown) {
        return States::Unknown;
    }
    return (inputA == States::One) ? States::Zero : States::One;
}
/**
 * Set positon of NOT gate
 */
void NOTGate::SetPosition(double x, double y) {
    Gate::SetPosition(x, y);
    UpdatePinPositions();
}
/**
 * updating pin positions
 */
void NOTGate::UpdatePinPositions()
{
    double x = GetX();
    double y = GetY();
    double w = GetWidth();
    double h = GetHeight();
    mInputPins[0].SetPosition(x - w/2 - 20, y);  // Input pin
    mOutputPins[0].SetPosition(x + w/2 + h/4 + 20, y);  // Output pin after
}
/**
 * Drawing NOT gate
 */
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

    // Draw the inversion circle at the point of the triangle
    graphics->DrawEllipse(x + w / 2 - h / 4, y - h / 4, h / 2, h / 2);

    graphics->StrokeLine(x - w/2, y, x - w/2 - 20, y);

    // Draw output line (after the inversion circle)
    graphics->StrokeLine(x + w/2 + h/4, y, x + w/2 + h/4 + 20, y);

    // Draw the pins
    for (auto& pin : mInputPins) {
        pin.Draw(graphics);
    }
    for (auto& pin : mOutputPins) {
        pin.Draw(graphics);
    }
}


/**
 * Constructor for the SR gate.
 */
SRFlipFlopGate::SRFlipFlopGate(Game* game) : Gate(game, L""),
    inputS(States::Unknown), inputR(States::Unknown)
{
    mInputPins.emplace_back(PinInput());  // S input
    mInputPins.emplace_back(PinInput());  // R input
    mOutputPins.emplace_back(PinOutput());  // Q output
    mOutputPins.emplace_back(PinOutput());  // Q' output
    InitializePins();
    UpdatePinPositions();
}
/**
 * Set input S
 */
void SRFlipFlopGate::SetInputS(States state)
{
    inputS = state;
}
/**
 * Set input R
 */
void SRFlipFlopGate::SetInputR(States state)
{
    inputR = state;
}
/**
 * compute output
 */
States SRFlipFlopGate::ComputeOutput() {
    if (inputS == States::One && inputR == States::One) {
        outputQ = States::Unknown;
        outputQPrime = States::Unknown;
    } else if (inputS == States::One) {
        outputQ = States::One;
        outputQPrime = States::Zero;
    } else if (inputR== States::One) {
        outputQ = States::Zero;
        outputQPrime = States::One;
    }
    return outputQ;
}
/**
 * Set position
 */
void SRFlipFlopGate::SetPosition(double x, double y) {
    Gate::SetPosition(x, y);
    UpdatePinPositions();
}
/**
 * Update pin positions
 */
void SRFlipFlopGate::UpdatePinPositions()
{
    double x = GetX();
    double y = GetY();
    double w = GetWidth();
    double h = GetHeight();

    mInputPins[0].SetPosition(x - w/2 - 20, y - h/4);  // S input
    mInputPins[1].SetPosition(x - w/2 - 20, y + h/4);  // R input
    mOutputPins[0].SetPosition(x + w/2 + 20, y - h/4);  // Q output
    mOutputPins[1].SetPosition(x + w/2 + 20, y + h/4);  // Q' output
}
/**
 * Draw SR gate
 */
void SRFlipFlopGate::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    auto path = graphics->CreatePath();

    // The location and size
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

    // Draw the body of the SR flip-flop (rectangle with rounded corners)
    path.AddRoundedRectangle(x - w / 2, y - h / 2, w, h, 10);

    // Draw the input and output connections
    wxPoint2DDouble p1(x - w / 2, y - h / 4);   // Input S
    wxPoint2DDouble p2(x - w / 2 - 20, y - h / 4); // Input S connection point
    wxPoint2DDouble p3(x - w / 2, y + h / 4);   // Input R
    wxPoint2DDouble p4(x - w / 2 - 20, y + h / 4); // Input R connection point
    wxPoint2DDouble p5(x + w / 2, y - h / 4);   // Output Q
    wxPoint2DDouble p6(x + w / 2 + 20, y - h / 4); // Output Q connection point
    wxPoint2DDouble p7(x + w / 2, y + h / 4);   // Output Q'
    wxPoint2DDouble p8(x + w / 2 + 20, y + h / 4); // Output Q' connection point

    // Create path for the input and output lines
    path.MoveToPoint(p1);
    path.AddLineToPoint(p2);
    path.MoveToPoint(p3);
    path.AddLineToPoint(p4);
    path.MoveToPoint(p5);
    path.AddLineToPoint(p6);
    path.MoveToPoint(p7);
    path.AddLineToPoint(p8);

    // Draw the SR flip-flop gate
    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->DrawPath(path);

    // Set font for labels
    wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxBLACK);

    // Draw labels
    graphics->DrawText("S", x - w / 2 + 5, y - h / 4 - 10);
    graphics->DrawText("R", x - w / 2 + 5, y + h / 4 - 10);
    graphics->DrawText("Q", x + w / 2 - 15, y - h / 4 - 10);
    graphics->DrawText("Q'", x + w / 2 - 15, y + h / 4 - 10);

    graphics->StrokeLine(x - w/2, y - h/4, x - w/2 - 20, y - h/4);  // S input
    graphics->StrokeLine(x - w/2, y + h/4, x - w/2 - 20, y + h/4);  // R input
    graphics->StrokeLine(x + w/2, y - h/4, x + w/2 + 20, y - h/4);  // Q output
    graphics->StrokeLine(x + w/2, y + h/4, x + w/2 + 20, y + h/4);  // Q' output

    // Draw the pins
    for (auto& pin : mInputPins) {
        pin.Draw(graphics);
    }
    for (auto& pin : mOutputPins) {
        pin.Draw(graphics);
    }

}

/**
 * D flip flop constructor
 */
DFlipFlopGate::DFlipFlopGate(Game* game) : Gate(game, L""),
    inputD(States::Unknown), clock(States::Unknown)
{
    mInputPins.emplace_back(PinInput());  // D input
    mInputPins.emplace_back(PinInput());  // Clock input
    mOutputPins.emplace_back(PinOutput());  // Q output
    mOutputPins.emplace_back(PinOutput());  // Q' output
    InitializePins();
    UpdatePinPositions();
}
/**
 * Set input D
 */
void DFlipFlopGate::SetInputD(States state) {
    inputD = state;
}
/**
 * Set input clock
 */
void DFlipFlopGate::SetClock(States state) {
    clock = state;
}
/**
 * computing output to D flip flop
 * @return States
 */
States DFlipFlopGate::ComputeOutput() {
    if (clock == States::One) {
        outputQ = inputD;
        outputQPrime = (inputD == States::One) ? States::Zero : States::One;
    }
    return outputQ;
}
/**
 * Set positon
 */
void DFlipFlopGate::SetPosition(double x, double y) {
    Gate::SetPosition(x, y);
    UpdatePinPositions();
}
/**
 * draw D flip flop gate
 */
void DFlipFlopGate::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    auto path = graphics->CreatePath();

    // The location and size
    auto x = GetX();
    auto y = GetY();
    auto w = GetWidth();
    auto h = GetHeight();

    // Draw the body of the D flip-flop (rectangle with rounded corners)
    path.AddRoundedRectangle(x - w / 2, y - h / 2, w, h, 10);

    // Draw the input and output connections
    wxPoint2DDouble p1(x - w / 2, y - h / 4);   // Input D
    wxPoint2DDouble p2(x - w / 2 - 20, y - h / 4); // Input D connection point
    wxPoint2DDouble p3(x - w / 2, y + h / 4);   // Clock input
    wxPoint2DDouble p4(x - w / 2 - 20, y + h / 4); // Clock input connection point
    wxPoint2DDouble p5(x + w / 2, y - h / 4);   // Output Q
    wxPoint2DDouble p6(x + w / 2 + 20, y - h / 4); // Output Q connection point
    wxPoint2DDouble p7(x + w / 2, y + h / 4);   // Output Q'
    wxPoint2DDouble p8(x + w / 2 + 20, y + h / 4); // Output Q' connection point

    // Create path for the input and output lines
    path.MoveToPoint(p1);
    path.AddLineToPoint(p2);
    path.MoveToPoint(p3);
    path.AddLineToPoint(p4);
    path.MoveToPoint(p5);
    path.AddLineToPoint(p6);
    path.MoveToPoint(p7);
    path.AddLineToPoint(p8);

    // Draw the D flip-flop gate
    graphics->SetPen(*wxBLACK_PEN);
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->DrawPath(path);

    // Draw the clock input triangle
    wxPoint2DDouble trianglePoints[3] = {
        wxPoint2DDouble(x - w / 2, y + h / 4 - 10),
        wxPoint2DDouble(x - w / 2 + 15, y + h / 4),
        wxPoint2DDouble(x - w / 2, y + h / 4 + 10)
    };
    graphics->DrawLines(3, trianglePoints);

    // Set font for labels
    wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxBLACK);

    // Draw labels
    graphics->DrawText("D", x - w / 2 + 5, y - h / 4 - 10);
    graphics->DrawText("Q", x + w / 2 - 15, y - h / 4 - 10);
    graphics->DrawText("Q'", x + w / 2 - 15, y + h / 4 - 10);

    graphics->StrokeLine(x - w/2, y - h/4, x - w/2 - 20, y - h/4);  // D input
    graphics->StrokeLine(x - w/2, y + h/4, x - w/2 - 20, y + h/4);  // Clock input
    graphics->StrokeLine(x + w/2, y - h/4, x + w/2 + 20, y - h/4);  // Q output
    graphics->StrokeLine(x + w/2, y + h/4, x + w/2 + 20, y + h/4);  // Q' output

    // Draw the pins
    for (auto& pin : mInputPins) {
        pin.Draw(graphics);
    }
    for (auto& pin : mOutputPins) {
        pin.Draw(graphics);
    }
}
/**
 * Updating pin positions
 */
void DFlipFlopGate::UpdatePinPositions()
{
    double x = GetX();
    double y = GetY();
    double w = GetWidth();
    double h = GetHeight();

    mInputPins[0].SetPosition(x - w/2 - 20, y - h/4);  // D input
    mInputPins[1].SetPosition(x - w/2 - 20, y + h/4);  // Clock input
    mOutputPins[0].SetPosition(x + w/2 + 20, y - h/4);  // Q output
    mOutputPins[1].SetPosition(x + w/2 + 20, y + h/4);  // Q' output
}
/**
 * Accepting the visitor from Item
 */
void ORGate::Accept(ItemVisitor* visitor)
{
    visitor->VisitORGate(this);
}
/**
 * Accept function for Item visitor
 */
void ANDGate::Accept(ItemVisitor* visitor)
{
    visitor->VisitANDGate(this);
}

// Implement Accept for NOTGate
/**
 * Set NOT gate for accept
 */
void NOTGate::Accept(ItemVisitor* visitor)
{
    visitor->VisitNOTGate(this);
}

// Implement Accept for SRFlipFlopGate
/**
 * accept SR flip flop
 */
void SRFlipFlopGate::Accept(ItemVisitor* visitor)
{
    visitor->VisitSRFlipFlopGate(this);
}

// Implement Accept for DFlipFlopGate
/**
 * Set D flip flop
 */
void DFlipFlopGate::Accept(ItemVisitor* visitor)
{
    visitor->VisitDFlipFlopGate(this);
}
