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


/**
 * visitor for the conveyor
 */
class ConveyorVisitor : public ItemVisitor
{
private:
    bool mIsConveyor = false; ///< if the item is a conveyor
    Conveyor* mConveyor = nullptr; ///< the conveyor

public:
    /**
     * visit the conveyor
     * 
     * @param conveyor the conveyor
     */
    void VisitConveyor(Conveyor* conveyor) override
    {
        mIsConveyor = true;
        mConveyor = conveyor;
    }

    /**
     * check if the item is a conveyor
     * 
     * @return true if the item is a conveyor
     */
    bool IsConveyor() const { return mIsConveyor; }


    /**
     * get the conveyor
     * 
     * @return the conveyor
     */
    Conveyor* GetConveyor() const { return mConveyor; }


    /**
     * visit the product
     * 
     * @param product the product
     */
    void VisitProduct(Product* product) override
    {
    }

    /**
     * visit the beam
     * 
     * @param beam the beam
     */
    void VisitBeam(Beam* beam) override
    {
    }

    /**
     * visit the sensor
     * 
     * @param sensor the sensor
     */
    void VisitSensor(Sensor* sensor) override
    {
    }

    /**
     * visit the scoreboard
     * 
     * @param scoreboard the scoreboard
     */
    void VisitScoreBoard(Scoreboard* scoreboard) override
    {
    }

    /**
     * visit the sparty
     * 
     * @param sparty the sparty
     */

    void VisitSparty(Sparty* sparty) override
    {
    }
};


#endif //CONVEYORVISITOR_H
