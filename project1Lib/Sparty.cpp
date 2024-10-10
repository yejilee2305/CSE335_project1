/**
 * @file Sparty.cpp
 * @author Yeji Lee
 *
 * implement the constructor, getter methods, and kick method
 * kick: contains logic for kicking products off conveyot
 */
 
#include "pch.h"
#include "Sparty.h"
#include "Product.h"
#include <wx/graphics.h>
#include <wx/wx.h>

// Constructor
Sparty::Sparty(int x, int y, int height, wxPoint2DDouble pin, double kickDuration, double kickSpeed)
    : mX(x), mY(y), mHeight(height), mPin(pin), mKickDuration(kickDuration), mKickSpeed(kickSpeed) {
    // Maintain aspect ratio for width
    mWidth = (mHeight * AspectRatio);
}

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