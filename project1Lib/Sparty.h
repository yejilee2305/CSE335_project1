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
#include "PinInput.h"

/**
 * class sparty
 * represents a character who performs a kicking action to move products off a conveyor
 *
 * the sparty class manages its graphical representation, input pin, and kicking mechanics
 * updates based on game conditions and triggers animations and sound when performing a kick
 */
class Sparty : public Item
{
public:
    /**
     * constructs a new sparty object with specified properties
     * @param game pointer to the game insatnce
     * @param x coordinate of sparty position
     * @param y coordinate of sparty position
     * @param height height of sparty
     * @param pin pin location of the input pin as a wxpoint2ddouble
     * @param kickDuration duration of the kick action in seconds
     * @param kickSpeed kickspeed speed of the kick action in pixels per seconds
     */
    Sparty(Game* game, int x, int y, int height, wxPoint2DDouble pin, double kickDuration, double kickSpeed);

    /**
     * accept visitor allowing operation specific to sparty
     * @param visitor pointer to the itemvisitor instance
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitSparty(this); }

    /**
     * draw sparty with its layered graphical representation
     * @param graphics shared pointer to the graphics context used for drawing
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * triggers the kicking logic without graphicscontext
     */
    void Kick(); // for logic only

    /**
     * updates sparty state including kicking progress and sound duration
     * @param elapsed time elapsed since the last update in seconds
     */
    void Update(double elapsed);

    /**
     * triggers the kick action rendering kicking motion
     * @param graphics graphics context for rendering the kick
     */
    void Kick(wxGraphicsContext* graphics);

    /**
     * sets sparty kicking state
     * @param kicking boolean value indicating if sparty is kicking
     */
    void SetKicking(bool kicking) { mIsKicking = kicking; }

    /**
     * checks if sparty is currently in the kicking state
     * @return true if sparty is kicking
     */
    bool IsKicking() const { return mIsKicking; }

    /**
     * progress of the kick animation
     */
    double mKickProgress = 0.0;
    /**
     * retrieves the input pin associated with sparty
     * @return pointer to the input pin
     */
    PinInput* GetInputPin() const {return mInputPin.get();}

private:
 /**
  * position (coordinate)
  */
    int mX;
    /**
     * position (coordinate)
     */
    int mY;
    /**
     * height of sparty
     */
    int mHeight;
    /**
     * width of sparty
     */
    int mWidth;
    /**
     * location of input pin
     */
    wxPoint2DDouble mPin; // Location of input pin
    /**
     * duration of kick animation in seconds
     */
    double mKickDuration; // Duration of kick animation in seconds
    /**
     * speed of kick in pixels per seconds
     */
    double mKickSpeed; // Speed of kick in pixels per second
    /**
     * boot rotation state for animation
     */
    double mRotation = 0; // Boot rotation state for animation

    // Bitmaps for layered images
    /**
     * bitmaps for layered image
     * background layer
     */
    wxGraphicsBitmap mBackBitmap; // Background layer
    /**
     * boot layer for kicking
     */
    wxGraphicsBitmap mBootBitmap; // Boot layer for kicking
    /**
     * foreground layer
     */
    wxGraphicsBitmap mFrontBitmap; // Foreground layer

    // Dimensions of the scaled back image
    /**
     * dimension of the scaled back image
     */
    double mBackWidth = 0.0;
    /**
     * dimension of the scaled back image
     */
    double mBackHeight = 0.0;

    /**
     * kicking state
     */
    bool mIsKicking = false;

    // Constants for Sparty's appearance and kicking motion
    /**
     * ratio
     */
    static constexpr double AspectRatio = 1.2;
    /**
     * sparty boot percentage
     */
    static constexpr double SpartyBootPercentage = 0.80;
    /**
     * spartybootmaxrotation
     */
    static constexpr double SpartyBootMaxRotation = 0.8; // Max rotation for kick
    /**
     * input pin
     */
    std::unique_ptr<PinInput> mInputPin;

    /**
     * team feature
     */
    std::string mCurrentNoise;
    /**
     * duratoin of team ferature
     */
    double mNoiseDuration = 1.0;
    /**
     * noise timer
     */
    double mNoiseTimer = 0.0;
};

#endif //SPARTY_H
