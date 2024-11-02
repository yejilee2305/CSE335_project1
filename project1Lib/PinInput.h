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

class Pin;
class PinOutput;
class Gate;


/**
 * @class PinInput
 * @brief Represents an input pin that can connect to output pins and receive signals.
 */
class PinInput : public Pins
{
private:
    ///< Pointer to the connected output pin, if any
    PinOutput* mConnectedPin = nullptr;
    ///< Pointer to an output pin for direct connection
    PinOutput* mConnection = nullptr;
    ///< List of connected output pins
    std::vector<PinOutput*> mConnectedPins; // Connected output pins
    ///< The current state of the input pin
    States mCurrentState = States::Unknown;

public:
    /**
     * @brief Default constructor for PinInput.
     */
    PinInput() = default;
    /**
     * @brief Default constructor for PinInput.
     */
    virtual ~PinInput() = default;
     /**
     * @brief Draws the input pin on the graphics context.
     *
     * @param graphics A shared pointer to the graphics context for rendering.
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    /**
     * @brief Gets the pin to which this input is currently connected.
     *
     * @return A pointer to the connected PinOutput, or nullptr if no connection exists.
     */
    PinOutput* GetConnectedPin() const { return mConnectedPin; }
    /**
     * @brief Connects this input pin to a specified output pin.
     *
     * @param pin The PinOutput object to connect to this input.
     */
    void ConnectToOutput(PinOutput* pin);
 ///static const int
    static const int DefaultLineLength = 20;
 /**
     * @brief set location
     *
     * @param x
     * @param y
     */
    void SetLocation(double x, double y) override;
 /**
 * @brief drag functions
 *
 * @param x
 * @param y
 */
    void OnDrag(double x, double y) override{}
 /**
     * @brief get connected gate
     */
    Gate* GetConnectedGate() const;
 /**
     * @brief pin output
     */
    void SetConnection(PinOutput* outputPin);
 /**
     * has connection
     */
    bool HasConnection() const { return mConnectedPin != nullptr; }
 /**
     * get current state
     */
    States GetCurrentState() const { return mCurrentState; }

 /**
  * @brief Default constructor for PinInput.
  * @param state
  */
    void SetCurrentState(States state) { mCurrentState = state; }

 const std::vector<PinOutput*>& GetConnectedPins() const {return mConnectedPins;}
};

#endif // PININPUT_H