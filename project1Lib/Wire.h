/**
 * @file Wire.h
 * @author Praseedha Vinukonda
 *
 *
 */
 
// Wire.h
#ifndef WIRE_H
#define WIRE_H

#include <wx/graphics.h>
#include "PinInput.h"
#include "PinOutput.h"

class PinOutput;
class Wire {
private:
    PinOutput* mOutputPin;
    PinInput* mInputPin;
    wxPoint2DDouble mControlPoint1;
    wxPoint2DDouble mControlPoint2;

    static constexpr double BezierMaxOffset = 200;
public:
    Wire(PinOutput* outputPin, PinInput* inputPin);
    void Draw(wxGraphicsContext* gc, bool showControlPoints);
    void UpdateControlPoints(double x, double y);
};

#endif // WIRE_H
