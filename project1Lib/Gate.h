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

enum class States { One, Zero, Unknown };

class Gate {
private:

public:
    virtual void Draw(wxGraphicsContext* graphics) = 0;  // Pure virtual function to draw the gate
    virtual States ComputeOutput() = 0;  // Pure virtual function to compute the output
    virtual ~Gate() = default;
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
    States ComputeOutput() override;
    void Draw(wxGraphicsContext* graphics) override;

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
    void Draw(wxGraphicsContext* graphics) override;

};
class NOTGate : public Gate {
private:
    States inputA;

public:
    NOTGate();
    void SetInputA(States state);
    States ComputeOutput() override;
    void Draw(wxGraphicsContext* graphics) override;
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
    void Draw(wxGraphicsContext* graphics) override;
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
    void Draw(wxGraphicsContext* graphics) override;
};

#endif //GATE_H
