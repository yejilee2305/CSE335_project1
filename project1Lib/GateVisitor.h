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
    void VisitORGate(ORGate* orgate) override
    {
        orgate->ComputeOutput();
    }

    void VisitANDGate(ANDGate* andgate) override
    {
        andgate->ComputeOutput();
    }

    void VisitNOTGate(NOTGate* notgate) override
    {
        notgate->ComputeOutput();
    }

    void VisitSRFlipFlopGate(SRFlipFlopGate* srflip) override
    {
        srflip->ComputeOutput();
    }

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
    GateHitTestVisitor(double x, double y)
        : mX(x), mY(y), mHitGate(nullptr)
    {
    }

    void VisitORGate(ORGate* orgate) override
    {
        if (orgate->HitTest(mX, mY))
        {
            mHitGate = orgate;
        }
    }

    void VisitANDGate(ANDGate* andgate) override
    {
        if (andgate->HitTest(mX, mY))
        {
            mHitGate = andgate;
        }
    }

    void VisitNOTGate(NOTGate* notgate) override
    {
        if (notgate->HitTest(mX, mY))
        {
            mHitGate = notgate;
        }
    }

    void VisitSRFlipFlopGate(SRFlipFlopGate* srflip) override
    {
        if (srflip->HitTest(mX, mY))
        {
            mHitGate = srflip;
        }
    }

    void VisitDFlipFlopGate(DFlipFlopGate* dflip) override
    {
        if (dflip->HitTest(mX, mY))
        {
            mHitGate = dflip;
        }
    }

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

    void VisitBeam(Beam* beam) override
    {
        if (beam->GetOutputPin()->HitTest(mX, mY))
        {
            mSelectedOutputPin = beam->GetOutputPin();
        }
    }

    void VisitSparty(Sparty* sparty) override
    {
        if (sparty->GetInputPin()->HitTest(mX, mY))
        {
            mSelectedInputPin = sparty->GetInputPin();
        }
    }


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
    GateGrabVisitor(double x, double y)
        : mX(x), mY(y), mGrabbedGate(nullptr)
    {
    }

    void VisitORGate(ORGate* orgate) override
    {
        if (orgate->HitTest(mX, mY))
        {
            mGrabbedGate = orgate;
        }
    }

    void VisitANDGate(ANDGate* andgate) override
    {
        if (andgate->HitTest(mX, mY))
        {
            mGrabbedGate = andgate;
        }
    }

    void VisitNOTGate(NOTGate* notgate) override
    {
        if (notgate->HitTest(mX, mY))
        {
            mGrabbedGate = notgate;
        }
    }

    void VisitSRFlipFlopGate(SRFlipFlopGate* srflip) override
    {
        if (srflip->HitTest(mX, mY))
        {
            mGrabbedGate = srflip;
        }
    }

    void VisitDFlipFlopGate(DFlipFlopGate* dflip) override
    {
        if (dflip->HitTest(mX, mY))
        {
            mGrabbedGate = dflip;
        }
    }

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
    GateInputPinHitTestVisitor(double x, double y)
        : mX(x), mY(y), mInputPin(nullptr)
    {
    }

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

    PinInput* GetInputPin() const
    {
        return mInputPin;
    }
};

#endif // GATEVISITOR_H
