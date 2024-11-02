/**
 * @file Wire.cpp
 * @author Praseedha Vinukonda
 */
 
// Wire.cpp
#include "pch.h"
#include "Wire.h"
#include "PinOutput.h"

/// Diameter to draw the pin in pixels
const int PinSize = 10;

/// Color to use for drawing a zero connection wire
const wxColour ConnectionColorZero = *wxBLACK;

/// Color to use for drawing a one connection wire
const wxColour ConnectionColorOne = *wxRED;

/// Color to use for drawing an unknown state connection wire
const wxColour ConnectionColorUnknown= wxColour(128, 128, 128);

/// Maximum offset of Bezier control points relative to line ends
static constexpr double BezierMaxOffset = 200;

/// Line with for drawing lines between pins
static const int LineWidth = 3;

/// Default length of line from the pin
static const int DefaultLineLength = 20;

/**
 * @brief Constructs a Wire between the specified output and input pins.
 *
 * @param outputPin The PinOutput object that serves as the wire’s starting point.
 * @param inputPin The PinInput object that serves as the wire’s endpoint.
 *
 * @details This constructor also initializes the control points of the wire based on the output pin's position.
 */
Wire::Wire(PinOutput* outputPin, PinInput* inputPin) : mOutputPin(outputPin), mInputPin(inputPin) {
    UpdateControlPoints(outputPin->GetX(), outputPin->GetY());
}
/**
 * @brief Updates the control points for the Bezier curve that represents the wire.
 *
 * @param x The X coordinate for the new endpoint of the wire.
 * @param y The Y coordinate for the new endpoint of the wire.
 *
 * @details This function calculates the offset based on the distance between the start and end points
 * and updates the control points accordingly.
 */
void Wire::UpdateControlPoints(double x, double y)
{
    double startX = mOutputPin->GetX();
    double startY = mOutputPin->GetY();
    double endX = x;
    double endY = y;

    double offset = std::min(BezierMaxOffset, std::abs(endX - startX));

    mControlPoint1 = wxPoint2DDouble(startX + offset, startY);
    mControlPoint2 = wxPoint2DDouble(endX - offset, endY);
}

/**
 * @brief Draws the wire between output and input pins on a wxGraphicsContext.
 *
 * @param gc A pointer to the wxGraphicsContext object used for drawing the wire.
 * @param showControlPoints If true, control points of the Bezier curve are displayed for debugging purposes.
 *
 * @details This function creates a Bezier curve between the output and input pins. The wire color is determined by
 * the state of the output pin and can vary between a high (red), low (black), or unknown (gray) state.
 */
void Wire::Draw(wxGraphicsContext* gc, bool showControlPoints) {
    // start and end points
    // wxPoint2DDouble p1(mOutputPin->GetX(), mOutputPin->GetY());
    // wxPoint2DDouble p4(mInputPin->GetX(), mInputPin->GetY());
    //
    // double distance = std::abs(p4.m_x - p1.m_x);
    // double offset = std::min(BezierMaxOffset, distance);
    //
    // // control points
    // wxPoint2DDouble p2(p1.m_x + offset, p1.m_y);
    // wxPoint2DDouble p3(p4.m_x - offset, p4.m_y);
    // wxColour colorToUse;
    // States state = mOutputPin->GetCurrentState(); // You need to implement this method
    //
    // if (state == States::One) {
    //     colorToUse = ConnectionColorOne; // Red
    // } else if (state == States::Zero) {
    //     colorToUse = ConnectionColorZero; // Black
    // } else {
    //     colorToUse = ConnectionColorUnknown; // Grey
    // }
    // // draw the Bézier curve
    // wxGraphicsPath path = gc->CreatePath();
    // path.MoveToPoint(p1);
    // path.AddCurveToPoint(p2.m_x, p2.m_y, p3.m_x, p3.m_y, p4.m_x, p4.m_y);
    //
    // gc->SetPen(wxPen(colorToUse, LineWidth));
    // gc->StrokePath(path);
    //
    // if (showControlPoints)
    // {
    //     gc->SetPen(*wxRED_PEN);
    //     gc->SetBrush(*wxRED_BRUSH);
    //     double pointSize = 5;
    //     gc->DrawEllipse(p1.m_x - pointSize/2, p1.m_y - pointSize/2, pointSize, pointSize);
    //     gc->DrawEllipse(p2.m_x - pointSize/2, p2.m_y - pointSize/2, pointSize, pointSize);
    //     gc->DrawEllipse(p3.m_x - pointSize/2, p3.m_y - pointSize/2, pointSize, pointSize);
    //     gc->DrawEllipse(p4.m_x - pointSize/2, p4.m_y - pointSize/2, pointSize, pointSize);
    // }
}
