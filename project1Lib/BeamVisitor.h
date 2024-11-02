/**
 * @file BeamVisitor.h
 * @author zhi lin
 *
 *
 */

#ifndef BEAMVISITOR_H
#define BEAMVISITOR_H
#include "ItemVisitor.h"

/**
 * visitor for the beam class
 * 
 */
class BeamVisitor : public ItemVisitor
{
private:
    std::vector<Beam*> mBeams; ///< vector of beams

public:
/**
 * visit the beam
 * 
 * @param beam 
 */
    void VisitBeam(Beam* beam) override
    {
        mBeams.push_back(beam);
    }

/**
 * get the beams
 * 
 * @return const std::vector<Beam*>& 
 */
    const std::vector<Beam*>& GetBeams() const { return mBeams; }
};

#endif //BEAMVISITOR_H
