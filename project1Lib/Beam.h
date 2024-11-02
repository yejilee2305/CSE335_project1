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

/**
 * class for the beam
 * 
 */
class Beam : public Item
{
private:
    int mX; ///< x location
    int mY; ///< y location
    int mSenderOffset; ///< x sender offset
    bool mBroken = false; ///< state of beam

    wxGraphicsBitmap mRedBitmap; ///< red bitmap
    wxGraphicsBitmap mGreenBitmap; ///< green bitmap
    std::unique_ptr<wxImage> mRedImage; ///< red image
    std::unique_ptr<wxImage> mGreenImage; ///< green image
    std::unique_ptr<PinOutput> mOutputPin; ///< Use a smart pointer

public:
    /// default constructor (disabled)
    Beam() = delete;

/**
 * visitor for the beam 
 * 
 * @param visitor
 */
    void Accept(ItemVisitor* visitor) override { visitor->VisitBeam(this); }

    /// copy consturctor (disabled)
    Beam(const Beam&) = delete;

    /// asignment operator (disabled)
    void operator=(const Beam&) = delete;

    Beam(Game* game, int x, int y, int senderOffset);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Update(double elpased) override;


/**
 * check if the beam is broken
 * @return true if the beam is broken
 */
    bool IsBroken() const { return mBroken; }

/**
 * set the beam to broken
 * 
 * @param broken 
 */
    void SetBroken(bool broken) { mBroken = broken; }

/**
 * check if the beam is intersecting with a product
 * 
 * @param product 
 * @return true if the beam is intersecting with the product
 */
    bool IsIntersecting(const Product* product);

    /**
     * getter for the output pin
     * @return the output pin
     */
    PinOutput* GetOutputPin() const { return mOutputPin.get(); }

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
