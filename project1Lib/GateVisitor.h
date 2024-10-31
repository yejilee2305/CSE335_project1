/**
 * @file GateVisitor.h
 * @author Praseedha Vinukonda
 *
 *
 */
 
#ifndef GATEVISITOR_H
#define GATEVISITOR_H

#include "Gate.h"
#include "ItemVisitor.h"

class GateVisitor : public ItemVisitor
{
private:
 double mX, mY;
 Gate *mGates = nullptr;
 public:
 GateVisitor(double x, double y):mX(x),mY(y){}
 void VisitGate(Gate *gate) override
 {
  if (gate->HitTest(mX, mY))
  {
   mGates = gate;
  }
 }
 Gate* GetGates() { return mGates; }
 void VisitORGate(ORGate* orgate) override;
 void VisitSRFlipFlopGate(SRFlipFlopGate* srflip) override;
 void VisitANDGate(ANDGate* andgate) override;
 void VisitDFlipFlopGate(DFlipFlopGate* dflip) override;
 void VisitNOTGate(NOTGate* notgate) override;
};

#endif //GATEVISITOR_H
