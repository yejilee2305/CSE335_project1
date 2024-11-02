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
 * @class SpartyVisitor
 * @brief Visitor class for gathering `Sparty` objects.
 *
 * @details The `SpartyVisitor` class implements the `VisitSparty` function
 * from the `ItemVisitor` base class to collect instances of `Sparty`.
 */
class SpartyVisitor : public ItemVisitor
{
private:
 std::vector<Sparty*> mSpartys; ///< Collection of `Sparty` instances visited.


public:
 /**
 * @brief Visits a `Sparty` object and stores it in the collection.
 *
 * @param sparty Pointer to the `Sparty` instance to visit.
 */
 void VisitSparty(Sparty* sparty) override
 {
  mSpartys.push_back(sparty);
 }
 /**
  * @brief Retrieves the collection of visited `Sparty` objects.
  *
  * @return A const reference to the vector of pointers to `Sparty` objects.
  */
 const std::vector<Sparty*>& GetSpartys() const { return mSpartys; }
};

#endif //SPARTYVISITOR_H
