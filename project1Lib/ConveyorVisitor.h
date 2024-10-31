/**
 * @file ConveyorVisitor.h
 * @author zhi lin
 *
 *
 */

#ifndef CONVEYORVISITOR_H
#define CONVEYORVISITOR_H
#include "ItemVisitor.h"
#include "Conveyor.h"


class ConveyorVisitor : public ItemVisitor
{
private:
    bool mIsConveyor = false;
    Conveyor* mConveyor = nullptr;

public:
    void VisitConveyor(Conveyor* conveyor) override
    {
        mIsConveyor = true;
        mConveyor = conveyor;
    }

    bool IsConveyor() const { return mIsConveyor; }

    Conveyor* GetConveyor() const { return mConveyor; }

    void VisitProduct(Product* product) override
    {
    }

    void VisitBeam(Beam* beam) override
    {
    }

    void VisitSensor(Sensor* sensor) override
    {
    }

    void VisitScoreBoard(Scoreboard* scoreboard) override
    {
    }

    void VisitSparty(Sparty* sparty) override
    {
    }
};


#endif //CONVEYORVISITOR_H
