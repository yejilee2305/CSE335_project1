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

class GateHitTestVisitor : public ItemVisitor
{
private:
    double mX;
    double mY;
    Gate* mHitGate;

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

class GateOutputPinHitTestVisitor : public ItemVisitor
{
private:
    double mX;
    double mY;
    PinOutput* mSelectedOutputPin;
    PinInput* mSelectedInputPin;

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
        // Check if an output pin is already selected
        if (mSelectedOutputPin && sparty->GetInputPin()->HitTest(mX, mY))
        {
            mSelectedInputPin = sparty->GetInputPin();

            // Connect the selected output pin to Sparty's input pin
            mSelectedOutputPin->ConnectToInput(mSelectedInputPin);
        }
    }


    PinOutput* GetSelectedOutputPin() const
    {
        return mSelectedOutputPin;
    }
};

class GateGrabVisitor : public ItemVisitor
{
private:
    double mX;
    double mY;
    Gate* mGrabbedGate;

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

class GateInputPinHitTestVisitor : public ItemVisitor
{
private:
    double mX;
    double mY;
    PinInput* mInputPin;

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
