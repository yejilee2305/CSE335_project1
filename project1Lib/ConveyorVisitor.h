/**
 * @file ConveyorVisitor.h
 * @author pach
 *
 *
 */

#ifndef CONVEYORVISITOR_H
#define CONVEYORVISITOR_H
#include "ItemVisitor.h"

class ConveyorVisitor : public ItemVisitor
{
private:
    bool mIsConveyor = false;
    Conveyor* mConveyor = nullptr;

public:
    void VisitConveyor(Conveyor* conveyor) override;
    bool IsConveyor() { return mIsConveyor; }

    void VisitProduct(Product* product) override
    {
    }

    void VisitBeam(Beam* beam) override
    {
    }

    void VisitSensor(Sensor* sensor) override
    {
    }
};
#endif //CONVEYORVISITOR_H
