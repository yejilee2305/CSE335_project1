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

#include "Game.h"

/// Image for the sparty background, what is behind the boot
const std::wstring SpartyBackImage = L"images/sparty-back.png";

/// Image for the Sparty boot
const std::wstring SpartyBootImage = L"images/sparty-boot.png";

/// Image for the Sparty front, what is in front of the boot
const std::wstring SpartyFrontImage = L"images/sparty-front.png";

/// Pivot point for the Sparty boot image as a fraction of
/// the width and height.
wxPoint2DDouble SpartyBootPivot = wxPoint2DDouble(0.5, 0.55);

/// X offset for the Sparty pin in pixels
/// This is medium size to barely poke out of Sparty
const int SpartyPinFirstOffset = 80;

/// Y offset for the Sparty pin in pixels
/// This is large size to reach above scoreboard
const int SpartyPinSecondOffset = 320;

/// X offset for the Sparty pin in pixels
/// This is small size to connect to the pin
const int SpartyPinThirdOffset = 20;

/// for drawing the line towards the input pin
const int LineThickness = 3;

Sparty::Sparty(Game* game, int x, int y, int height, wxPoint2DDouble pin, double kickDuration, double kickSpeed)
    : Item(game, SpartyFrontImage), mX(x), mY(y), mHeight(height), mPin(pin),
      mKickDuration(kickDuration), mKickSpeed(kickSpeed)
{
    // Calculate width to maintain aspect ratio
    mWidth = round(mHeight * AspectRatio);

    // Initialize other properties if needed
    mRotation = 0; // Initial boot rotation state
    mInputPin = std::make_unique<PinInput>();
    mInputPin->SetPosition(mPin.m_x, mPin.m_y);
}


// Method to trigger the kick
// void Sparty::Kick(wxGraphicsContext* graphics) {
//     int bootY = int(mHeight * SpartyBootPercentage);  // Y location for boot
//     wxPen bootablePen(*wxGREEN, 3);
//     graphics->SetPen(bootablePen);
//     graphics->StrokeLine(mX - mWidth / 2, mY - mHeight / 2 + bootY,
//         mX + mWidth / 2, mY - mHeight / 2 + bootY);
//     Team team;
//     team.TriggerNoise();
// }

void Sparty::Kick()
{
    mIsKicking = true;
    mKickProgress = 0.0; // Reset kick progress if applicable

    mCurrentNoise = GetGame()->GetTeam().TriggerNoise();
    mNoiseTimer = 0.0;
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


void Sparty::Update(double elapsed)
{
    if (!mCurrentNoise.empty())
    {
        mNoiseTimer += elapsed;
        if (mNoiseTimer >= mKickDuration)
        {
            mCurrentNoise.clear();
            mNoiseTimer = 0.0;
        }
    }
}


void Sparty::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Scaling factor for Sparty's size
    double scaleFactor = 0.3;


    // Kick parameters
    double kickOffsetX = 20 * mKickProgress; // Horizontal offset
    double kickOffsetY = -10 * mKickProgress; // Upward offset
    double kickRotation = SpartyBootMaxRotation * mKickProgress; // Rotation for kick

    // Initialize bitmaps if they are not yet created
    if (mBackBitmap.IsNull())
    {
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

    // Draw the back layer
    graphics->DrawBitmap(mBackBitmap, centerX, centerY, mBackWidth, mBackHeight);

    // Draw the connecting lines
    graphics->SetPen(wxPen(*wxBLACK, LineThickness));
    graphics->StrokeLine(mX, mY, mX + SpartyPinFirstOffset, mY);
    graphics->StrokeLine(mX + SpartyPinFirstOffset, mY, mX + SpartyPinFirstOffset, mY - SpartyPinSecondOffset);
    graphics->StrokeLine(mX + SpartyPinFirstOffset, mY - SpartyPinSecondOffset, mPin.m_x + SpartyPinThirdOffset,
                         mY - SpartyPinSecondOffset);
    graphics->StrokeLine(mPin.m_x + SpartyPinThirdOffset, mY - SpartyPinSecondOffset, mPin.m_x + SpartyPinThirdOffset,
                         mPin.m_y);
    graphics->StrokeLine(mPin.m_x + SpartyPinThirdOffset, mPin.m_y, mPin.m_x, mPin.m_y);
    mInputPin->Draw(graphics);

    // Draw the boot layer with kicking offsets and rotation
    graphics->PushState();
    graphics->Translate(mX + kickOffsetX, mY + kickOffsetY); // Apply kick offsets
    graphics->Rotate(kickRotation); // Rotate boot for kicking animation
    graphics->DrawBitmap(mBootBitmap, -mBackWidth / 2, -mBackHeight / 2, mBackWidth, mBackHeight);
    graphics->PopState();

    // Draw the front layer (aligned with back and boot)
    graphics->DrawBitmap(mFrontBitmap, centerX, centerY, mBackWidth, mBackHeight);

    if (!mCurrentNoise.empty())
    {
        wxFont noiseFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        graphics->SetFont(noiseFont, *wxRED);

        double textWidth, textHeight;
        graphics->GetTextExtent(mCurrentNoise, &textWidth, &textHeight, nullptr, nullptr);

        double textX = mX - textWidth / 2;
        double textY = mY - mHeight / 2 - textHeight - 10; // 10 pixels above sparty

        graphics->SetBrush(*wxWHITE_BRUSH);
        graphics->SetPen(*wxTRANSPARENT_PEN);
        graphics->DrawRectangle(textX - 5, textY - 5, textWidth + 10, textHeight + 10);

        graphics->DrawText(mCurrentNoise, textX, textY);
    }
}
