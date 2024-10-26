/**
 * @file Sparty.h
 * @author Yeji Lee
 *
 * defines Sparty class
 * responsible for kicking products off the conveuor when triggered
 * contains position, height, kick speed, and kick duration
 */

#ifndef SPARTY_H
#define SPARTY_H

#include <wx/graphics.h>
#include <wx/wx.h>
#include <memory>
#include "Item.h"
#include "Product.h"

class Sparty : public Item {
public:
    // Constructor
    Sparty(Game* game, int x, int y, int height, wxPoint2DDouble pin, double kickDuration, double kickSpeed);

    // Draw function to render Sparty with layers
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    // Method to trigger the kick action
    void Kick(wxGraphicsContext* graphics);

    // Check if a product is in the correct position to be kicked
    //bool CheckProductLocation(Product* product);

    // Set and check kicking state
    void SetKicking(bool kicking) { mIsKicking = kicking; }
    bool IsKicking() const { return mIsKicking; }

    // Progress of the kick (0 to 1)

    double mKickProgress = 0.0;

private:
    int mX, mY;                    // Position (center of Sparty)
    int mHeight, mWidth;           // Height and calculated width of Sparty
    wxPoint2DDouble mPin;          // Location of input pin
    double mKickDuration;          // Duration of kick animation in seconds
    double mKickSpeed;             // Speed of kick in pixels per second
    double mRotation = 0;          // Boot rotation state for animation

    // Bitmaps for layered images
    wxGraphicsBitmap mBackBitmap;  // Background layer
    wxGraphicsBitmap mBootBitmap;  // Boot layer for kicking
    wxGraphicsBitmap mFrontBitmap; // Foreground layer

    // Dimensions of the scaled back image
    double mBackWidth = 0.0;
    double mBackHeight = 0.0;

    // Kicking state
    bool mIsKicking = false;

    // Constants for Sparty's appearance and kicking motion
    static constexpr double AspectRatio = 1.2;
    static constexpr double SpartyBootPercentage = 0.80;
    static constexpr double SpartyBootMaxRotation = 0.8; // Max rotation for kick
};

#endif //SPARTY_H
