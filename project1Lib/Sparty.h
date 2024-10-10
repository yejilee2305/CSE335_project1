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
#include <Product.h>
#include <Item.h>

class Product;

class Sparty {
public:
    // Constructor
    Sparty(int x, int y, int height, wxPoint2DDouble pin, double kickDuration, double kickSpeed);

    // Method to trigger the kick
    void Kick(wxGraphicsContext* graphics);

    // Method to check if a product is in the correct position to be kicked
    bool CheckProductLocation(Product* product);

private:
    int mX, mY;                 // position (center of Sparty)
    int mHeight, mWidth;         // height and calculated width of Sparty
    wxPoint2DDouble mPin;        // location of input pin
    double mKickDuration;        // duration of kick animation in seconds
    double mKickSpeed;           // speed of kick in pixels per second
    double mRotation = 0;        // boot rotation state

    // Constants
    const double AspectRatio;
    const double SpartyBootPercentage; // Percentage of the way down Sparty for the boot
    const double SpartyBootMaxRotation;      // Maximum boot rotation

    // Images
    const std::wstring SpartyBackImage;
    const std::wstring SpartyBootImage;
    const std::wstring SpartyFrontImage;
};

#endif //SPARTY_H
