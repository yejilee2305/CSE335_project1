/**
 * @file WireVisitor.h
 * @author Praseedha Vinukonda
 *
 *
 */

#ifndef WIREVISITOR_H
#define WIREVISITOR_H

#include "ItemVisitor.h"
#include "Wire.h"
#include "Game.h"
#include <memory>




/**
 * visitor for adding wires
 * 
 */
class AddWireVisitor : public ItemVisitor
{
private:
    Game* mGame;

public:
    AddWireVisitor() = default;

    AddWireVisitor(Game* game) : mGame(game)
    {
    }

    void VisitWire(Wire* wire) override
    {
        PinOutput* outputPin = wire->GetOutputPin();
        PinInput* inputPin = wire->GetInputPin();
        if (outputPin && inputPin)
        {
            mGame->AddWire(outputPin, inputPin);
        }
    }
};


/**
 * clear wire visitor
 * 
 */
class ClearWireVisitor : public ItemVisitor
{
private:
    Game* mGame;

public:
    ClearWireVisitor() = default;

    void VisitWire(Wire* wire) override
    {
    }
};

/**
 * drawing visitor
 * 
 */
class WireDrawingVisitor : public ItemVisitor
{
private:
    wxGraphicsContext* mGraphics;
    bool mShowControlPoints;

public:
    WireDrawingVisitor(wxGraphicsContext* graphics, bool showControlPoints)
        : mGraphics(graphics), mShowControlPoints(showControlPoints)
    {
    }

    void VisitGate(Gate* gate) override
    {
        for (auto& outputPin : gate->GetOutputPins())
        {
            for (auto inputPin : outputPin.GetConnectedPins())
            {
                Wire wire(&outputPin, inputPin);
                wire.Draw(mGraphics, mShowControlPoints);
            }
        }
    }

    void VisitBeam(Beam* beam) override
    {
        PinOutput* outputPin = beam->GetOutputPin();
        for (auto& inputPin : outputPin->GetConnectedPins())
        {
            if (inputPin)
            {
                Wire wire(outputPin, inputPin);
                wire.Draw(mGraphics, mShowControlPoints);
            }
        }
    }


};
#endif //WIREVISITOR_H
