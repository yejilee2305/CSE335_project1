/**
* @file Gate.h
 * @author Praseedha Vinukonda
 *
 *
 */

#ifndef GATE_H
#define GATE_H
#include "Item.h"
#include "PinInput.h"
#include "PinOutput.h"
#include <wx/graphics.h>
#include <wx/pen.h>
#include <wx/brush.h>
#include "ids.h"


enum class States { One, Zero, Unknown };
const wxSize OrGateSize(75, 50);
// Size of the AND gate in pixels
const wxSize AndGateSize(75, 50); // Width: 75 pixels, Height: 50 pixels

// Size of the NOT gate in pixels
const wxSize NotGateSize(50, 50);  // Width: 50 pixels, Height: 50 pixels

// Size of the SR Flip Flop in pixels
const wxSize SRFlipFlopSize(50, 75); // Width: 50 pixels, Height: 75 pixels

// Size of the D Flip Flop in pixels
const wxSize DFlipFlopSize(50, 75); // Width: 50 pixels, Height: 75 pixels
class Gate {
private:
    double mX = 0;  ///< X coordinate of the gate
    double mY = 0;  ///< Y coordinate of the gate
    wxGraphicsPath mPath;
    std::vector<std::shared_ptr<Gate>> gates;  // Collection of logic gates
    std::shared_ptr<Gate> mGrabbedGate;
protected:
    std::vector<PinInput> mInputPins;
    std::vector<PinOutput> mOutputPins;

public:
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;  // Pure virtual function to draw the gate
    virtual States ComputeOutput() = 0;  // Pure virtual function to compute the output
    virtual ~Gate() = default;
    // Getter functions for the position of the gate
    double GetX() const { return mX; }
    double GetY() const { return mY; }

    virtual double GetWidth() const = 0;  // Pure virtual function to get width
    virtual double GetHeight() const = 0; // Pure virtual function to get height
    void OnMouseClick(double x, double y);
    virtual bool HitTest(double x, double y) const;
    void SetPosition(double x, double y);
    std::vector<PinInput>& GetInputPins() { return mInputPins; }
    std::vector<PinOutput>& GetOutputPins() { return mOutputPins; }
    virtual void UpdatePinPositions() = 0;
    void InitializePins();
};

class ORGate : public Gate
{
private:
    States inputA;
    States inputB;

public:
    ORGate();
    void SetInputA(States state);
    void SetInputB(States state);
    void SetPosition(double x, double y);
    States ComputeOutput() override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void UpdatePinPositions() override;
    // Override to return the specific width and height for OR Gate
    double GetWidth() const override { return OrGateSize.GetWidth(); }
    double GetHeight() const override { return OrGateSize.GetHeight(); }

};

class ANDGate : public Gate
{
private:
    States inputA;
    States inputB;

public:
    ANDGate();
    void SetInputA(States state);
    void SetInputB(States state);
    States ComputeOutput() override;
    void SetPosition(double x, double y);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    double GetWidth() const override { return AndGateSize.GetWidth(); }
    double GetHeight() const override { return AndGateSize.GetHeight(); }
    void UpdatePinPositions() override;

};
class NOTGate : public Gate {
private:
    States inputA;

public:
    NOTGate();
    void SetInputA(States state);
    void SetInputB(States state);
    States ComputeOutput() override;
    void SetPosition(double x, double y);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    double GetWidth() const override { return NotGateSize.GetWidth(); }
    double GetHeight() const override { return NotGateSize.GetHeight(); }
    void UpdatePinPositions() override;

};

class SRFlipFlopGate : public Gate {
private:
    States inputS;
    States inputR;
    States outputQ;
    States outputQPrime;

public:
    SRFlipFlopGate();
    void SetInputS(States state);
    void SetInputR(States state);
    States ComputeOutput() override;
    void SetPosition(double x, double y);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    double GetWidth() const override { return AndGateSize.GetWidth(); }
    double GetHeight() const override { return AndGateSize.GetHeight(); }
    void UpdatePinPositions() override;

};

// D Flip-Flop Gate
class DFlipFlopGate : public Gate {
private:
    States inputD;
    States clock;
    States outputQ;
    States outputQPrime;

public:
    DFlipFlopGate();
    void SetInputD(States state);
    void SetClock(States state);
    States ComputeOutput() override;
    void SetPosition(double x, double y);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    double GetWidth() const override { return AndGateSize.GetWidth(); }
    double GetHeight() const override { return AndGateSize.GetHeight(); }
    void UpdatePinPositions() override;
};

#endif //GATE_H
