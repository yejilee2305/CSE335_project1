/**
 * @file BeamVisitor.h
 * @author zhi lin
 *
 *
 */

#ifndef BEAMVISITOR_H
#define BEAMVISITOR_H
#include "ItemVisitor.h"

class BeamVisitor : public ItemVisitor
{
private:
    std::vector<Beam*> mBeams;

public:
    void VisitBeam(Beam* beam) override
    {
        mBeams.push_back(beam);
    }

    const std::vector<Beam*>& GetBeams() const { return mBeams; }
};

#endif //BEAMVISITOR_H
