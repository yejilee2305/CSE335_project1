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
    int mX; ///< x location
    int mY; ///< y location
    int mSenderOffset; ///< x sender offset
    bool mBroken = false; ///< state of beam

    std::unique_ptr<wxImage> mRedImage; ///< red image
    std::unique_ptr<wxImage> mGreenImage; ///< green image

public:
    /// default constructor (disabled)
    Beam() = delete;

    /// copy consturctor (disabled)
    Beam(const Beam&) = delete;

    /// asignment operator (disabled)
    void operator=(const Beam&) = delete;

    Beam(int x, int y, int senderOffset);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Update(double elpased) override;

    bool HitTest(int x, int y) override;

    bool IsBroken() const { return mBroken; }

    void SetBroken(bool broken) { mBroken = broken; }

    /**
     * getter for x location
     * @return x location
     */
    int GetX() const { return mX; }

    /**
     * getter for y location
     * @return y location
     */
    int GetY() const { return mY; }
};


#endif //BEAM_H
