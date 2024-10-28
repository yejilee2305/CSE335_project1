/**
 * @file ConveyorVisitor.cpp
 * @author zhi lin
 */


#include "ConveyorVisitor.h"


void ConveyorVisitor::VisitConveyor(Conveyor* conveyor)
{
    mIsConveyor = true;
    mConveyor = conveyor;
}
