/**
 * @file PinOutput.h
 * @author Praseedha Vinukonda
 *
 *
 */

// PinOutput.h
#ifndef PINOUTPUT_H
#define PINOUTPUT_H


#include "Pins.h"
#include <vector>
#include "Gate.h"
#include <wx/colour.h>
#include "States.h"

class Gate;
class PinInput;

/**
 * Pin output class
 *
 */
class PinOutput : public Pins
{
private:
    /// The input pins this output is connected to
    std::vector<PinInput*> mConnectedPins;
    /// Maximum offset of Bezier control points relative to line ends
    static constexpr double BezierMaxOffset = 200;
    /// Line width for drawing lines between pins
    static const int LineWidth = 3;
    /// The connections for pin input
    std::vector<PinInput*> mConnections;
    /// The variable for dragging wire
    bool mDragging = false;
    /// parent gate variable
    Gate* mParentGate = nullptr;

public:
    /**
     * Pin Output class constructor default
     */
    PinOutput() = default;
    /**
     * Pin Output class constructor default
     */
    virtual ~PinOutput() = default;
    /**
     * Draws the output pin on the provided graphics context.
     * @param graphics A shared pointer to the wxGraphicsContext for drawing.
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
     /**
     * Handles dragging operations for the pin.
     * @param x The x-coordinate of the drag position.
     * @param y The y-coordinate of the drag position.
     */
    void OnDrag(double x, double y) override;
     /**
     * Connects this output pin to an input pin.
     * @param pin Pointer to the input pin to connect.
     */
    void ConnectTo(PinInput* pin);
    /**
     * Disconnects this output pin from an input pin.
     * @param pin Pointer to the input pin to disconnect from.
     */
    void DisconnectFrom(PinInput* pin);
    /**
    * Draws the connection between this output pin and an input pin.
    * @param graphics A shared pointer to the wxGraphicsContext for drawing the connection.
    * @param inputPin Pointer to the input pin to which the connection is drawn.
    */
    void DrawConnection(std::shared_ptr<wxGraphicsContext> graphics, PinInput* inputPin);
    /**
    * Adds a connection to an input pin.
    * @param connection Pointer to the input pin to add to the connection list.
    */
    void AddConnection(PinInput* connection) { mConnectedPins.push_back(connection); }
    /**
    * Tests if a given point is within the area of the pin.
    * @param x The x-coordinate of the point to test.
    * @param y The y-coordinate of the point to test.
    * @return True if the point is within the pin area, false otherwise.
    */
    bool HitTest(double x, double y) const override;
    /**
    * Sets the location of the pin.
    * @param x The new x-coordinate of the pin.
    * @param y The new y-coordinate of the pin.
    */
    void SetLocation(double x, double y) override;
     /**
     * Sets the parent gate of this output pin.
     * @param gate Pointer to the gate that is the parent of this pin.
     */
    void SetParentGate(Gate* gate) { mParentGate = gate; }
    /**
     * Gets the parent gate of this output pin.
     * @return Pointer to the gate that is the parent of this pin.
     */
    Gate* GetParentGate() const { return mParentGate; }
     /**
     * Gets the current state of this output pin.
     * @return The current state as a States enumeration value.
     */
    States GetCurrentState() const { return mCurrentState; }
     /**
     * Sets the current state of this output pin.
     * @param state The state to set, as a States enumeration value.
     */
    void SetCurrentState(States state) { mCurrentState = state; }
     /**
     * Gets the color associated with a state of zero (low) for connections.
     * @return The wxColour representing the zero state.
     */
    static const wxColour& GetConnectionColorZero() { return ConnectionColorZero; }
    /**
     * Gets the color associated with a state of one (high) for connections.
     * @return The wxColour representing the one state.
     */
    static const wxColour& GetConnectionColorOne() { return ConnectionColorOne; }
     /**
     * Gets the color associated with an unknown state for connections.
     * @return The wxColour representing the unknown state.
     */
    static const wxColour& GetConnectionColorUnknown() { return ConnectionColorUnknown; }
     /**
     * Updates the state of this output pin and propagates the change to connected pins.
     */
    void UpdateState();
 /// Static color representing a zero (low) connection state.
    static const wxColour ConnectionColorZero; // Black
 /// Static color representing a one
    static const wxColour ConnectionColorOne; // Red
 /// Static color representing a unkown
    static const wxColour ConnectionColorUnknown;
 /// Static color representing unkown state
    States mCurrentState = States::Unknown;
    /**
     * Gets a list of input pins connected to this output pin.
     * @return A constant reference to a vector of pointers to connected PinInput objects.
     */
    const std::vector<PinInput*>& GetConnectedPins() const { return mConnectedPins; }
};

#endif // PINOUTPUT_H
