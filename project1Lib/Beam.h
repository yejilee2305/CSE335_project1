/**
 * @file Beam.h
 * @author zhi lin
 *
 *
 */

#ifndef BEAM_H
#define BEAM_H
#include "Item.h"
#include "Product.h"
#include "PinOutput.h"

class Beam : public Item
{
private:
    int mX; ///< x location
    int mY; ///< y location
    int mSenderOffset; ///< x sender offset
    bool mBroken = false; ///< state of beam

    wxGraphicsBitmap mRedBitmap;
    wxGraphicsBitmap mGreenBitmap;
    std::unique_ptr<wxImage> mRedImage; ///< red image
    std::unique_ptr<wxImage> mGreenImage; ///< green image
    std::unique_ptr<PinOutput> mOutputPin; // Use a smart pointer

public:
    /// default constructor (disabled)
    Beam() = delete;

    void Accept(ItemVisitor* visitor) override { visitor->VisitBeam(this); }

    /// copy consturctor (disabled)
    Beam(const Beam&) = delete;

    /// asignment operator (disabled)
    void operator=(const Beam&) = delete;

    Beam(Game* game, int x, int y, int senderOffset);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Update(double elpased) override;

    bool IsBroken() const { return mBroken; }

    void SetBroken(bool broken) { mBroken = broken; }

    bool IsIntersecting(const Product* product);

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
