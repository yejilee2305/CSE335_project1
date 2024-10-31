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
class PinInput;  // Forward declaration

class PinOutput : public Pins
{
private:
 /// The input pins this output is connected to
 std::vector<PinInput*> mConnectedPins;

 /// Maximum offset of Bezier control points relative to line ends
 static constexpr double BezierMaxOffset = 200;

 /// Line width for drawing lines between pins
 static const int LineWidth = 3;
 std::vector<PinInput*> mConnections;
 bool mDragging = false;
 Gate* mParentGate; // Pointer to the parent gate

public:
 /// Constructor
 PinOutput() = default;

 /// Destructor
 virtual ~PinOutput() = default;

 /// Draw the output pin
 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
 void OnDrag(double x, double y) override;

 /// Connect this output to an input pin
 void ConnectTo(PinInput* pin);

 /// Disconnect from an input pin
 void DisconnectFrom(PinInput* pin);

 /// Draw the connection between this output and an input pin
 void DrawConnection(std::shared_ptr<wxGraphicsContext> graphics, PinInput* inputPin);
 void AddConnection(PinInput* connection) { mConnections.push_back(connection); }
 bool HitTest(double x, double y) const override;
 void SetLocation(double x, double y) override;
 void SetParentGate(Gate* gate) { mParentGate = gate; }
 Gate* GetParentGate() const { return mParentGate; }
 States GetCurrentState() const { return mCurrentState; }
 void SetCurrentState(States state) { mCurrentState = state; }
 static const wxColour& GetConnectionColorZero() { return ConnectionColorZero; }
 static const wxColour& GetConnectionColorOne() { return ConnectionColorOne; }
 static const wxColour& GetConnectionColorUnknown() { return ConnectionColorUnknown; }
 void UpdateState();
 static const wxColour ConnectionColorZero; // Black
 static const wxColour ConnectionColorOne;  // Red
 static const wxColour ConnectionColorUnknown;
 States mCurrentState = States::Unknown;
};

#endif // PINOUTPUT_H