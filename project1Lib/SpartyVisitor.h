/**
 * @file SpartyVisitor.h
 * @author Yeji Lee
 *
 *
 */
 
#ifndef SPARTYVISITOR_H
#define SPARTYVISITOR_H

#include "ItemVisitor.h"

/**
 * visitor for the sparty class
 * 
 */
class SpartyVisitor : public ItemVisitor
{
private:
 /**
  * collection of sparty instances
  */
 std::vector<Sparty*> mSpartys;

public:
 /**
  * visits a sparty instance adding it to the collection
  * @param sparty pointer to the sparty object being visited
  */
 void VisitSparty(Sparty* sparty) override
 {
  mSpartys.push_back(sparty);
 }

 /**
  * retrieves the collection of visited sparty instances
  * @return a constant reference to the vector of sparty pointers
  */
 const std::vector<Sparty*>& GetSpartys() const { return mSpartys; }
};

#endif //SPARTYVISITOR_H
