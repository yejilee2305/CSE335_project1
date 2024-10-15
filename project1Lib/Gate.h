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

#endif //GATE_H
