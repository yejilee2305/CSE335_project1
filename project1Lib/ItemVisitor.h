
/**
 * @file ItemVisitor.h
 * @author zhi lin
 *
 *
 */
#include "Pch.h"

class Product;
class Conveyor;
class Beam;
class Sensor;
class Scoreboard;
class Sparty;

#ifndef ITEMVISITOR_H
#define ITEMVISITOR_H


class ItemVisitor
{
protected:
    ItemVisitor()
    {
    }

public:
    ~ItemVisitor()
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
};

#endif //ITEMVISITOR_H
