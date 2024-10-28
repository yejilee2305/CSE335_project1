/**
 * @file ItemVisitor.h
 * @author zhi lin
 *
 *
 */

class Product;
class Conveyor;
class Beam;
class Sensor;


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
};

#endif //ITEMVISITOR_H
