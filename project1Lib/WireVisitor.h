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
    /**
     * pointer to the game instance
     */
    Game* mGame; ///< game object

public:
    /**
     * default constructor
     */
    AddWireVisitor() = default;

/**
 * constructor
 * 
 * @param game the game
 */
    AddWireVisitor(Game* game) : mGame(game)
    {
    }

/**
 * visit wire
 * 
 * @param wire 
 */
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
    /**
     * pointer to the game instance
     */
    Game* mGame; ///< game object

public:
    /**
     * default constructor
     */
    ClearWireVisitor() = default;

/**
 * constructor
 * 
 * @param wire 
 */
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
    /**
     * graphics context for drawing
     */
    wxGraphicsContext* mGraphics;
    /**
     * flag to indicate if control points show
     */
    bool mShowControlPoints;

public:
    /**
     * constructor for wiredrawingvisior
     * @param graphics graphics pointer to the exgraphicscontext for drawing
     * @param showControlPoints boolean flag to indicate whether to show
     */
    WireDrawingVisitor(wxGraphicsContext* graphics, bool showControlPoints)
        : mGraphics(graphics), mShowControlPoints(showControlPoints)
    {
    }

    /**
     * visits a gate and draws the wires connecting its output pins
     * @param gate pointer to the gate being visited
     */
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

};
#endif //WIREVISITOR_H
