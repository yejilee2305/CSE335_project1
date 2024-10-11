/**
 * @file Beam.h
 * @author zhi lin
 *
 *
 */

#ifndef BEAM_H
#define BEAM_H
#include "Item.h"


class Beam : public Item
{
private:
    int mX;
    int mY;
    int mSenderOffset;
    bool mBroken = false;

    std::unique_ptr<wxImage> mRedImage;
    std::unique_ptr<wxImage> mGreenImage;

public:
    Beam() = delete;
    Beam(const Beam&) = delete;
    void operator=(const Beam&) = delete;

    Beam(int x, int y, int senderOffset);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Update(double elpased) override;

    bool HitTest(int x, int y) override;

    bool IsBroken() const { return mBroken; }

    void SetBroken(bool broken) { mBroken = broken; }

    int GetX() const { return mX; }
    int GetY() const { return mY; }
};


#endif //BEAM_H
