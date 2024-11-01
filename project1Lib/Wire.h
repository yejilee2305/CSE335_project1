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
class PinInput;

/**
 * @class Wire
 * @brief Represents a wire connecting an output pin to an input pin in a circuit.
 *
 * The Wire class manages the visual representation and control points of a Bezier
 * curve that connects two pins, allowing flexibility in the wire’s shape.
 */
class Wire
{
private:
    ///< The output pin that this wire is connected to
    PinOutput* mOutputPin;
    ///< The input pin that this wire is connected to
    PinInput* mInputPin;
    ///< First control point for the Bezier curve
    wxPoint2DDouble mControlPoint1;
    ///< Second control point for the Bezier curve
    wxPoint2DDouble mControlPoint2;
    /// The maximum offset for control points in the Bezier curve.
    static constexpr double BezierMaxOffset = 200;

public:
    /**
     * @brief Constructs a Wire between a specified output pin and input pin.
     *
     * @param outputPin The PinOutput object that serves as the wire’s starting point.
     * @param inputPin The PinInput object that serves as the wire’s endpoint.
     */
    Wire(PinOutput* outputPin, PinInput* inputPin);
    /**
     * @brief Draws the wire as a Bezier curve on the specified graphics context.
     *
     * @param gc A pointer to the wxGraphicsContext object used for drawing.
     * @param showControlPoints If true, control points for the Bezier curve will be shown.
     */
    void Draw(wxGraphicsContext* gc, bool showControlPoints);
 /**
     * @brief Updates the control points of the Bezier curve.
     *
     * This function adjusts the position of the control points to modify the curve’s shape.
     *
     * @param x The new X coordinate for updating control points.
     * @param y The new Y coordinate for updating control points.
     */
    void UpdateControlPoints(double x, double y);
 /**
     * @brief Gets the output pin to which this wire is connected.
     *
     * @return A pointer to the connected PinOutput object.
     */
    PinOutput* GetOutputPin() const { return mOutputPin; }
 /**
     * @brief Gets the input pin to which this wire is connected.
     *
     * @return A pointer to the connected PinInput object.
     */
    PinInput* GetInputPin() const { return mInputPin; }
};

#endif // WIRE_H
