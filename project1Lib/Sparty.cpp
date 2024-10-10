/**
 * @file Sparty.cpp
 * @author Yeji Lee
 *
 * implement the constructor, getter methods, and kick method
 * kick: contains logic for kicking products off conveyot
 */
 
#include "pch.h"
#include "Sparty.h"
#include <wx/graphics.h>
#include <wx/wx.h>


/// Image for the sparty background, what is behind the boot
const std::wstring SpartyBackImage = L"sparty-back.png";

/// Image for the Sparty boot
const std::wstring SpartyBootImage = L"sparty-boot.png";

/// Image for the Sparty front, what is in front of the boot
const std::wstring SpartyFrontImage = L"sparty-front.png";

/// Pivot point for the Sparty boot image as a fraction of
/// the width and height.
wxPoint2DDouble SpartyBootPivot = wxPoint2DDouble(0.5, 0.55);

/// The maximum rotation for Sparty's boot in radians
const double SpartyBootMaxRotation = 0.8;

/// The point in the kick animation when the product
/// actually is kicked. If the kick duration is 0.25,
/// we kick when 0.25 * 0.35 seconds have elapsed.
const double SpartyKickPoint = 0.35;

/// What percentage of the way down Sparty do we find the tip of his boot?
/// This means the location of the boot when kicking is 80% of the
/// way from the top of the Sparty image.
const double SpartyBootPercentage = 0.80;
const double AspectRatio = 1.2;

// // Constructor
// Sparty::Sparty(int x, int y, int height, wxPoint2DDouble pin, double kickDuration, double kickSpeed)
//     : mX(x), mY(y), mHeight(height), mPin(pin), mKickDuration(kickDuration), mKickSpeed(kickSpeed) {
//     // Maintain aspect ratio for width
//     mWidth = (mHeight * AspectRatio);
// }

// Method to trigger the kick
void Sparty::Kick(wxGraphicsContext* graphics) {
    int bootY = int(mHeight * SpartyBootPercentage);  // Y location for boot
    wxPen bootablePen(*wxGREEN, 3);
    graphics->SetPen(bootablePen);
    graphics->StrokeLine(mX - mWidth / 2, mY - mHeight / 2 + bootY, mX + mWidth / 2, mY - mHeight / 2 + bootY);
}

// Method to check if a product is in the correct position to be kicked
bool Sparty::CheckProductLocation(Product* product) {
    int bootY = int(mHeight * SpartyBootPercentage);
    if (product->GetPlacement() == bootY && product->ShouldKick()) {
        return true;  // Product is in kickable position
    }
    return false;
}