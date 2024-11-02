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
 std::vector<Sparty*> mSpartys;

public:
 void VisitSparty(Sparty* sparty) override
 {
  mSpartys.push_back(sparty);
 }

 const std::vector<Sparty*>& GetSpartys() const { return mSpartys; }
};

#endif //SPARTYVISITOR_H
