/**
 * @file PinInput.h
 * @author Praseedha Vinukonda
 *
 *
 */

// PinInput.h
#ifndef PININPUT_H
#define PININPUT_H

#include "Pins.h"
#include "PinOutput.h"
#include "Gate.h"
#include "States.h"

class Pin;  // Forward declaration
class PinOutput; // Forward declaration
class Gate;      // Forward declaration

class PinInput : public Pins
{
private:
    /// The pin this input is connected to
    PinOutput* mConnectedPin = nullptr;
    PinOutput* mConnection = nullptr;
    std::vector<PinOutput*> mConnectedPins; // Connected output pins
    States mCurrentState = States::Unknown;

public:
    /// Constructor
    PinInput() = default;
    /// Destructor
    virtual ~PinInput() = default;
    /// Draw the input pin
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    /// Get the connected pin
    PinOutput* GetConnectedPin() const { return mConnectedPin; }
    void ConnectTo(PinOutput* pin);
    // void SetConnection(PinOutput* connection) { mConnectedPin = connection;}
    static const int DefaultLineLength = 20;
    void SetLocation(double x, double y) override;
    void OnDrag(double x, double y) override{}
    Gate* GetConnectedGate() const;
    void SetConnection(PinOutput* outputPin);
    bool HasConnection() const { return mConnectedPin != nullptr; }
    States GetCurrentState() const { return mCurrentState; }

    // Declaration of SetCurrentState
    void SetCurrentState(States state) { mCurrentState = state; }
};

#endif // PININPUT_H