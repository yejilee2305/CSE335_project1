/**
 * @file Sparty.cpp
 * @author Yeji Lee
 *
 * implement the constructor, getter methods, and kick method
 * kick: contains logic for kicking products off conveyor
 */

#include "pch.h"
#include "Sparty.h"
#include <wx/graphics.h>
#include <wx/wx.h>
#include <Team.h>
#include <cmath>

/// Image for the sparty background, what is behind the boot
const std::wstring SpartyBackImage = L"images/sparty-back.png";

/// Image for the Sparty boot
const std::wstring SpartyBootImage = L"images/sparty-boot.png";

/// Image for the Sparty front, what is in front of the boot
const std::wstring SpartyFrontImage = L"images/sparty-front.png";

/// Pivot point for the Sparty boot image as a fraction of
/// the width and height.
wxPoint2DDouble SpartyBootPivot = wxPoint2DDouble(0.5, 0.55);

Sparty::Sparty(Game* game, int x, int y, int height, wxPoint2DDouble pin, double kickDuration, double kickSpeed)
    : Item(game, SpartyFrontImage), mX(x), mY(y), mHeight(height), mPin(pin),
      mKickDuration(kickDuration), mKickSpeed(kickSpeed)
{
    // Calculate width to maintain aspect ratio
    mWidth = round(mHeight * AspectRatio);

    // Initialize other properties if needed
    mRotation = 0;  // Initial boot rotation state
}


// Method to trigger the kick
void Sparty::Kick(wxGraphicsContext* graphics) {
    int bootY = int(mHeight * SpartyBootPercentage);  // Y location for boot
    wxPen bootablePen(*wxGREEN, 3);
    graphics->SetPen(bootablePen);
    graphics->StrokeLine(mX - mWidth / 2, mY - mHeight / 2 + bootY,
        mX + mWidth / 2, mY - mHeight / 2 + bootY);
    Team team;
    team.TriggerNoise();
}

// Method to check if a product is in the correct position to be kicked
/**
bool Sparty::CheckProductLocation(Product* product) {
    int bootY = int(mHeight * SpartyBootPercentage);
    if (product->GetPlacement() == bootY && product->ShouldKick()) {
        return true;  // Product is in kickable position
    }
    return false;
}
*/

void Sparty::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    // Scaling factor for Sparty's size
    double scaleFactor = 0.3;

    // Kick parameters (adjust as needed)
    double kickOffsetX = 20 * mKickProgress; // Horizontal offset
    double kickOffsetY = -10 * mKickProgress; // Upward offset
    double kickRotation = SpartyBootMaxRotation * mKickProgress; // Rotation for kick

    // Initialize bitmaps if they are not yet created
    if (mBackBitmap.IsNull()) {
        wxImage backImage(SpartyBackImage);
        wxImage bootImage(SpartyBootImage);
        wxImage frontImage(SpartyFrontImage);

        // Create bitmaps from images
        mBackBitmap = graphics->CreateBitmapFromImage(backImage);
        mBootBitmap = graphics->CreateBitmapFromImage(bootImage);
        mFrontBitmap = graphics->CreateBitmapFromImage(frontImage);

        // Store scaled dimensions
        mBackWidth = backImage.GetWidth() * scaleFactor;
        mBackHeight = backImage.GetHeight() * scaleFactor;
    }

    // Common center point for all layers (back, boot, front)
    double centerX = mX - mBackWidth / 2;
    double centerY = mY - mBackHeight / 2;

    // Draw the back layer (aligned with boot and front)
    graphics->DrawBitmap(mBackBitmap, centerX, centerY, mBackWidth, mBackHeight);

    // Draw the boot layer with kicking offsets and rotation
    graphics->PushState();
    graphics->Translate(mX + kickOffsetX, mY + kickOffsetY);  // Apply kick offsets
    graphics->Rotate(kickRotation);  // Rotate boot for kicking animation
    graphics->DrawBitmap(mBootBitmap, -mBackWidth / 2, -mBackHeight / 2, mBackWidth, mBackHeight);
    graphics->PopState();

    // Draw the front layer (aligned with back and boot)
    graphics->DrawBitmap(mFrontBitmap, centerX, centerY, mBackWidth, mBackHeight);
}
