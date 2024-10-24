/**
* @file Gate.h
 * @author Praseedha Vinukonda
 *
 *
 */

#ifndef GATE_H
#define GATE_H
#include "Item.h"
#include <wx/graphics.h>
#include <wx/pen.h>
#include <wx/brush.h>
#include "ids.h"
#include "Pins.h"

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
    std::vector<Pin> pins;

    void AddPin(PinType type, wxPoint relativePosition);
    Pin* GetClosestPin(wxPoint point);
    virtual void SetInputA(States state) = 0;
    virtual void SetInputB(States state) = 0;
    // virtual void SetInputS(States state) = 0;
    // virtual void SetInputR(States state) = 0;
    // virtual void SetInputD(States state) = 0;
    // virtual void SetClock(States state) = 0;


};

class ORGate : public Gate
{
private:
    States inputA;
    States inputB;

public:
    ORGate();
    void SetInputA(States state) override;
    void SetInputB(States state) override;
    States ComputeOutput() override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
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
    void SetInputA(States state) override;
    void SetInputB(States state) override;
    States ComputeOutput() override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    double GetWidth() const override { return AndGateSize.GetWidth(); }
    double GetHeight() const override { return AndGateSize.GetHeight(); }

};
class NOTGate : public Gate {
private:
    States inputA;
    States inputB;

public:
    NOTGate();
    void SetInputA(States state) override;
    void SetInputB(States state) override;
    States ComputeOutput() override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    double GetWidth() const override { return NotGateSize.GetWidth(); }
    double GetHeight() const override { return NotGateSize.GetHeight(); }

};

class SRFlipFlopGate : public Gate {
private:
    States inputA;
    States inputB;
    States outputQ;
    States outputQPrime;

public:
    SRFlipFlopGate();
    void SetInputA(States state) override;
    void SetInputB(States state) override;
    States ComputeOutput() override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    double GetWidth() const override { return AndGateSize.GetWidth(); }
    double GetHeight() const override { return AndGateSize.GetHeight(); }

};

// D Flip-Flop Gate
class DFlipFlopGate : public Gate {
private:
    States inputA;
    States inputB;
    States outputQ;
    States outputQPrime;

public:
    DFlipFlopGate();
    void SetInputA(States state) override;
    void SetInputB(States state) override;
    States ComputeOutput() override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    double GetWidth() const override { return AndGateSize.GetWidth(); }
    double GetHeight() const override { return AndGateSize.GetHeight(); }
};

#endif //GATE_H
