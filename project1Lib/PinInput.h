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

class Pin;  // Forward declaration

class PinInput : public Pins
{
private:
    /// The pin this input is connected to
    PinOutput* mConnectedPin = nullptr;
    PinOutput* mConnection = nullptr;

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
    void SetConnection(PinOutput* connection) { mConnection = connection; }
    PinOutput* GetConnection() const { return mConnection; }
    static const int DefaultLineLength = 20;
};

#endif // PININPUT_H