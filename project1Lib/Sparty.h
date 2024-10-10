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
    int mX, mY;                 // Position (center of Sparty)
    int mHeight, mWidth;         // Height and calculated width of Sparty
    wxPoint2DDouble mPin;        // Location of input pin
    double mKickDuration;        // Duration of kick animation in seconds
    double mKickSpeed;           // Speed of kick in pixels per second
    double mRotation = 0;        // Boot rotation state

    // Constants
    const double AspectRatio = 1.2;  // Example aspect ratio
    const double SpartyBootPercentage = 0.80;  // Percentage of the way down Sparty for the boot
    const double MaxBootRotation = 0.8;        // Maximum boot rotation

    // Images
    const std::wstring SpartyBackImage = L"sparty-back.png";
    const std::wstring SpartyBootImage = L"sparty-boot.png";
    const std::wstring SpartyFrontImage = L"sparty-front.png";
};

#endif //SPARTY_H
