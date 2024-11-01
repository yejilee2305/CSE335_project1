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
class Wire;

/**
 * visitor class for items
 * 
 */
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

    /**
     * visit a product
     * 
     * @param product the product to visit
     */
    virtual void VisitProduct(Product* product)
    {
    }

    /**
     * visit a conveyor
     * 
     * @param conveyor the conveyor to visit
     */
    virtual void VisitConveyor(Conveyor* conveyor)
    {
    }

    /**
     * visit a beam
     * 
     * @param beam the beam to visit
     */
    virtual void VisitBeam(Beam* beam)
    {
    }

    /**
     * visit a sensor
     * 
     * @param sensor the sensor to visit
     */
    virtual void VisitSensor(Sensor* sensor)
    {
    }

    /**
     * visit a scoreboard
     * 
     * @param scoreboard the scoreboard to visit
     */
    virtual void VisitScoreBoard(Scoreboard* scoreboard)
    {
    }

    /**
     * visit a sparty
     * 
     * @param sparty the sparty to visit
     */
    virtual void VisitSparty(Sparty* sparty)
    {
    }


    /**
     * visit a gate
     * 
     * @param gate the gate to visit
     */
    virtual void VisitGate(Gate* gate)
    {
    }


    /**
     * visit an OR gate
     * 
     * @param orgate the OR gate to visit
     */
    virtual void VisitORGate(ORGate* orgate)
    {
    }

    /**
     * visit an AND gate
     * 
     * @param andgate the AND gate to visit
     */
    virtual void VisitANDGate(ANDGate* andgate)
    {
    }

    /**
     * visit a NOT gate
     * 
     * @param notgate the NOT gate to visit
     */
    virtual void VisitNOTGate(NOTGate* notgate)
    {
    }

    /**
     * visit a SR flip flop gate
     * 
     * @param srflip the SR flip flop gate to visit
     */
    virtual void VisitSRFlipFlopGate(SRFlipFlopGate* srflip)
    {
    }

    /**
     * visit a D flip flop gate
     * 
     * @param dflip the D flip flop gate to visit
     */
    virtual void VisitDFlipFlopGate(DFlipFlopGate* dflip)
    {
    }

    /**
     * visit a wire
     * 
     * @param wire the wire to visit
     */
    virtual void VisitWire(Wire* wire)
    {
    }
};
#endif //ITEMVISITOR_H
