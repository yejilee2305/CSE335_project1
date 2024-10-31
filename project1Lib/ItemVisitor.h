/**
 * @file ItemVisitor.h
 * @author zhi lin
 *
 *
 */

#ifndef ITEMVISITOR_H
#define ITEMVISITOR_H


class Product;
class Conveyor;
class Beam;
class Sensor;
class Scoreboard;
class Sparty;
class Gate;
class ORGate;
class ANDGate;
class NOTGate;
class SRFlipFlopGate;
class DFlipFlopGate;

class ItemVisitor
{
protected:
    ItemVisitor()
    {
    }

public:
    virtual ~ItemVisitor()
    {
    }

    virtual void VisitProduct(Product* product)
    {
    }

    virtual void VisitConveyor(Conveyor* conveyor)
    {
    }

    virtual void VisitBeam(Beam* beam)
    {
    }

    virtual void VisitSensor(Sensor* sensor)
    {
    }

    virtual void VisitScoreBoard(Scoreboard* scoreboard)
    {
    }

    virtual void VisitSparty(Sparty* sparty)
    {
    }

    virtual void VisitGate(Gate* gate)
    {
    }

    virtual void VisitORGate(ORGate* orgate)
    {
    }

    virtual void VisitANDGate(ANDGate* andgate)
    {
    }

    virtual void VisitNOTGate(NOTGate* notgate)
    {
    }

    virtual void VisitSRFlipFlopGate(SRFlipFlopGate* srflip)
    {
    }

    virtual void VisitDFlipFlopGate(DFlipFlopGate* dflip)
    {
    }
};
#endif //ITEMVISITOR_H
