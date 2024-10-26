/**
 * @file PinInput.h
 * @author Praseedha Vinukonda
 *
 *
 */

#ifndef PININPUT_H
#define PININPUT_H

#include "Pins.h"
#include "PinOutput.h"

class Pin;  // Forward declaration

class PinInput : public Pins
{
private:
    /// The pin this input is connected to
    PinOutput* mConnectedPin = nullptr;

public:
    /// Constructor
    PinInput() = default;

    /// Destructor
    virtual ~PinInput() = default;

    /// Draw the input pin
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /// Connect this input to an output pin
    void ConnectTo(PinOutput* pin);

    /// Get the connected pin
    PinOutput* GetConnectedPin() const { return mConnectedPin; }
};

#endif // PININPUT_H