/**
 * @file GateVisitor.h
 * @author zhi lin
 */

#ifndef GATEVISITOR_H
#define GATEVISITOR_H

#include "ItemVisitor.h"
#include "Gate.h"
#include <memory>
#include "Beam.h"

/**
 * visitor for computing output
 *
 */
class GateComputeOutputVisitor : public ItemVisitor
{
public:
    /**
     * visit the OR gate
     *
     * @param orgate
     */
    void VisitORGate(ORGate* orgate) override
    {
        orgate->ComputeOutput();
    }

    /**
     * visit the AND gate
     *
     * @param andgate
     */
    void VisitANDGate(ANDGate* andgate) override
    {
        andgate->ComputeOutput();
    }

    /**
     * visit the NOT gate
     *
     * @param notgate
     */
    void VisitNOTGate(NOTGate* notgate) override
    {
        notgate->ComputeOutput();
    }

    /**
     * visit the SR flip flop gate
     *
     * @param srflip
     */
    void VisitSRFlipFlopGate(SRFlipFlopGate* srflip) override
    {
        srflip->ComputeOutput();
    }

    /**
     * visit the D flip flop gate
     *
     * @param dflip
     */
    void VisitDFlipFlopGate(DFlipFlopGate* dflip) override
    {
        dflip->ComputeOutput();
    }
};

/**
 * visitor for hit test
 *
 */
class GateHitTestVisitor : public ItemVisitor
{
private:
    double mX; ///< x location
    double mY; ///< y location
    Gate* mHitGate; ///< gate that is hit

public:
    /**
     * constructor
     *
     * @param x
     * @param y
     */
    GateHitTestVisitor(double x, double y)
        : mX(x), mY(y), mHitGate(nullptr)
    {
    }

    /**
     * visit the OR gate
     *
     * @param orgate
     */
    void VisitORGate(ORGate* orgate) override
    {
        if (orgate->HitTest(mX, mY))
        {
            mHitGate = orgate;
        }
    }


    /**
     * visit the AND gate
     *
     * @param andgate
     */
    void VisitANDGate(ANDGate* andgate) override
    {
        if (andgate->HitTest(mX, mY))
        {
            mHitGate = andgate;
        }
    }

    /**
     * visit the NOT gate
     *
     * @param notgate
     */
    void VisitNOTGate(NOTGate* notgate) override
    {
        if (notgate->HitTest(mX, mY))
        {
            mHitGate = notgate;
        }
    }

    /**
     * visit the SR flip flop gate
     *
     * @param srflip
     */
    void VisitSRFlipFlopGate(SRFlipFlopGate* srflip) override
    {
        if (srflip->HitTest(mX, mY))
        {
            mHitGate = srflip;
        }
    }

    /**
     * visit the D flip flop gate
     *
     * @param dflip
     */
    void VisitDFlipFlopGate(DFlipFlopGate* dflip) override
    {
        if (dflip->HitTest(mX, mY))
        {
            mHitGate = dflip;
        }
    }

    /**
     * get the hit gate
     *
     * @return Gate*
     */

    Gate* GetHitGate() const
    {
        return mHitGate;
    }
};

/**
 * visitor for output pin hit test
 *
 */
class GateOutputPinHitTestVisitor : public ItemVisitor
{
private:
    PinInput* mSelectedInputPin;
    double mX; ///< x location
    double mY; ///< y location
    PinOutput* mSelectedOutputPin; ///< selected output pin

public:
    GateOutputPinHitTestVisitor(double x, double y)
        : mX(x), mY(y), mSelectedOutputPin(nullptr)
    {
    }

    /**
     * visit the OR gate
     *
     * @param orgate
     */
    void VisitORGate(ORGate* orgate) override
    {
        for (auto& outputPin : orgate->GetOutputPins())
        {
            if (outputPin.HitTest(mX, mY))
            {
                mSelectedOutputPin = &outputPin;
                break;
            }
        }
    }

    /**
     * visit the AND gate
     *
     * @param andgate
     */
    void VisitANDGate(ANDGate* andgate) override
    {
        for (auto& outputPin : andgate->GetOutputPins())
        {
            if (outputPin.HitTest(mX, mY))
            {
                mSelectedOutputPin = &outputPin;
                break;
            }
        }
    }

    /**
     * visit the NOT gate
     *
     * @param notgate
     */

    void VisitNOTGate(NOTGate* notgate) override
    {
        for (auto& outputPin : notgate->GetOutputPins())
        {
            if (outputPin.HitTest(mX, mY))
            {
                mSelectedOutputPin = &outputPin;
                break;
            }
        }
    }

    /**
     * visit the SR flip flop gate
     *
     * @param srflip
     */
    void VisitSRFlipFlopGate(SRFlipFlopGate* srflip) override
    {
        for (auto& outputPin : srflip->GetOutputPins())
        {
            if (outputPin.HitTest(mX, mY))
            {
                mSelectedOutputPin = &outputPin;
                break;
            }
        }
    }

    /**
     *  visit the D flip flop gate
     *
     * @param dflip
     */
    void VisitDFlipFlopGate(DFlipFlopGate* dflip) override
    {
        for (auto& outputPin : dflip->GetOutputPins())
        {
            if (outputPin.HitTest(mX, mY))
            {
                mSelectedOutputPin = &outputPin;
                break;
            }
        }
    }

    /**
     * visit the beam
     *
     * @param beam
     */
    void VisitBeam(Beam* beam) override
    {
        if (beam->GetOutputPin()->HitTest(mX, mY))
        {
            mSelectedOutputPin = beam->GetOutputPin();
        }
    }

    /**
     * visit the sparty
     *
     * @param sparty
     */

    void VisitSparty(Sparty* sparty) override
    {
        if (sparty->GetInputPin()->HitTest(mX, mY))
        {
            mSelectedInputPin = sparty->GetInputPin();
        }
    }

    /**
     * get the selected output pin
     *
     * @return PinOutput*
     */

    PinOutput* GetSelectedOutputPin() const
    {
        return mSelectedOutputPin;
    }
};

/**
 * visitor for gate grab
 *
 */
class GateGrabVisitor : public ItemVisitor
{
private:
    double mX; ///< x location
    double mY; ///< y location
    Gate* mGrabbedGate; ///< grabbed gate

public:
    /**
     * constructor
     *
     * @param x x location
     * @param y y location
     */
    GateGrabVisitor(double x, double y)
        : mX(x), mY(y), mGrabbedGate(nullptr)
    {
    }


    /**
     * visit the OR gate
     *
     * @param orgate
     */
    void VisitORGate(ORGate* orgate) override
    {
        if (orgate->HitTest(mX, mY))
        {
            mGrabbedGate = orgate;
        }
    }

    /**
     * visit the AND gate
     *
     * @param andgate
     */
    void VisitANDGate(ANDGate* andgate) override
    {
        if (andgate->HitTest(mX, mY))
        {
            mGrabbedGate = andgate;
        }
    }

    /**
     * visit the NOT gate
     *
     * @param notgate
     */
    void VisitNOTGate(NOTGate* notgate) override
    {
        if (notgate->HitTest(mX, mY))
        {
            mGrabbedGate = notgate;
        }
    }

    /**
     * visit the SR flip flop gate
     *
     * @param srflip
     */
    void VisitSRFlipFlopGate(SRFlipFlopGate* srflip) override
    {
        if (srflip->HitTest(mX, mY))
        {
            mGrabbedGate = srflip;
        }
    }

    /**
     * visit the D flip flop gate
     *
     * @param dflip
     */
    void VisitDFlipFlopGate(DFlipFlopGate* dflip) override
    {
        if (dflip->HitTest(mX, mY))
        {
            mGrabbedGate = dflip;
        }
    }

    /**
     * get the grabbed gate
     *
     * @return Gate*
     */
    Gate* GetGrabbedGate() const
    {
        return mGrabbedGate;
    }
};

/**
 * visitor for gate input pin hit test
 *
 */
class GateInputPinHitTestVisitor : public ItemVisitor
{
private:
    double mX; ///< x location
    double mY; ///< y location
    PinInput* mInputPin; ///< input pin

public:
    /**
     * constructor
     *
     * @param x
     * @param y
     */
    GateInputPinHitTestVisitor(double x, double y)
        : mX(x), mY(y), mInputPin(nullptr)
    {
    }

    /**
     * visit the OR gate
     *
     * @param orgate
     */
    void VisitORGate(ORGate* orgate) override
    {
        for (auto& inputPin : orgate->GetInputPins())
        {
            if (inputPin.HitTest(mX, mY))
            {
                mInputPin = &inputPin;
                break;
            }
        }
    }

    /**
     * visit the AND gate
     *
     * @param andgate
     */
    void VisitANDGate(ANDGate* andgate) override
    {
        for (auto& inputPin : andgate->GetInputPins())
        {
            if (inputPin.HitTest(mX, mY))
            {
                mInputPin = &inputPin;
                break;
            }
        }
    }

    /**
     * visit the NOT gate
     *
     * @param notgate
     */
    void VisitNOTGate(NOTGate* notgate) override
    {
        for (auto& inputPin : notgate->GetInputPins())
        {
            if (inputPin.HitTest(mX, mY))
            {
                mInputPin = &inputPin;
                break;
            }
        }
    }

    /**
     * visit the SR flip flop gate
     *
     * @param srflip
     */
    void VisitSRFlipFlopGate(SRFlipFlopGate* srflip) override
    {
        for (auto& inputPin : srflip->GetInputPins())
        {
            if (inputPin.HitTest(mX, mY))
            {
                mInputPin = &inputPin;
                break;
            }
        }
    }

    /**
     * visit the D flip flop gate
     *
     * @param dflip
     */
    void VisitDFlipFlopGate(DFlipFlopGate* dflip) override
    {
        for (auto& inputPin : dflip->GetInputPins())
        {
            if (inputPin.HitTest(mX, mY))
            {
                mInputPin = &inputPin;
                break;
            }
        }
    }

    /**
     * get the input pin
     *
     * @return PinInput*
     */
    PinInput* GetInputPin() const
    {
        return mInputPin;
    }
};

#endif // GATEVISITOR_H
