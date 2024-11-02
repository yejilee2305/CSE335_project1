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
 * @class AddWireVisitor
 * @brief Visitor class that adds Wire connections to the Game.
 *
 * @details This visitor takes Wire objects and connects the output and input pins.
 * It adds the Wire connection to the Game's management system.
 */
class AddWireVisitor : public ItemVisitor
{
private:
    Game* mGame;

public:
    AddWireVisitor() = default;
    /**
 * @brief Constructor that initializes the Game instance.
 * @param game Pointer to the Game instance.
 */
    AddWireVisitor(Game* game) : mGame(game)
    {
    }
    /**
 * @brief Visits a Wire and adds its connection to the Game.
 * @param wire Pointer to the Wire object.
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
 * @class ClearWireVisitor
 * @brief Visitor class that clears Wire connections.
 *
 * @details This visitor is used to clear or reset connections associated with Wire objects.
 */
class ClearWireVisitor : public ItemVisitor
{
private:
    Game* mGame; ///< Pointer to the Game instance for managing wire connections.

public:
    /// Default constructor
    ClearWireVisitor() = default;
    /**
     * @brief Visits a Wire and clears its connection (implementation not shown).
     * @param wire Pointer to the Wire object.
     */
    void VisitWire(Wire* wire) override
    {
    }
};
/**
 * @class WireDrawingVisitor
 * @brief Visitor class for drawing Wire connections with optional control points.
 *
 * @details This visitor takes Wire objects and uses wxGraphicsContext to draw
 * Bezier curves representing the wires. Control points can be optionally displayed.
 */
class WireDrawingVisitor : public ItemVisitor
{
private:
    wxGraphicsContext* mGraphics; ///< Pointer to the graphics context for drawing wires.
    bool mShowControlPoints; ///< Flag to indicate if control points should be drawn.

public:
    /**
 * @brief Constructor that initializes the graphics context and control point display option.
 * @param graphics Pointer to the wxGraphicsContext for drawing.
 * @param showControlPoints Boolean indicating whether to show control points.
 */
    WireDrawingVisitor(wxGraphicsContext* graphics, bool showControlPoints)
        : mGraphics(graphics), mShowControlPoints(showControlPoints)
    {
    }
    /**
     * @brief Visits a Gate and draws connections to each connected input pin.
     * @param gate Pointer to the Gate object.
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
    /**
     * @brief Visits a Beam and draws connections to each connected input pin.
     * @param beam Pointer to the Beam object.
     */
    void VisitBeam(Beam* beam) override
    {
        PinOutput* outputPin = beam->GetOutputPin();
        for (auto inputPin : outputPin->GetConnectedPins())
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
