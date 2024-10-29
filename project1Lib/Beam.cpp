/**
 * @file Beam.cpp
 * @author zhi lin
 */

#include "pch.h"
#include "Beam.h"
#include "Game.h"
#include "ProductVisitor.h"
/// Image for the beam sender and receiver when red
const std::wstring BeamRedImage = L"images/beam-red.png";

/// Image for the beam sender and receiver when green
const std::wstring BeamGreenImage = L"images/beam-green.png";

/// X offset for the beam pin in pixels
/// This is larger than normal to get it past Sparty's feet
const int BeamPinOffset = 80;

/// for drawing the line towards the output pin
const int LineThickness = 3;

/**
 * constructor
 * @param x x location
 * @param y y location
 * @param senderOffset offset for the beam sender
 */
Beam::Beam(Game* game, int x, int y, int senderOffset)
    : Item(game, BeamGreenImage), mX(x + senderOffset), mY(y), mSenderOffset(senderOffset)
{
    mRedImage = std::make_unique<wxImage>(BeamRedImage, wxBITMAP_TYPE_PNG);
    mGreenImage = std::make_unique<wxImage>(BeamGreenImage, wxBITMAP_TYPE_PNG);
    mOutputPin = std::make_unique<PinOutput>(); // Initialize the PinOutput
    mOutputPin->SetPosition(mX - senderOffset + BeamPinOffset, mY);
}

/**
 * draw the beam
 * @param graphics graphic context
 */
void Beam::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mRedBitmap.IsNull())
    {
        mRedBitmap = graphics->CreateBitmapFromImage(*mRedImage);
        mGreenBitmap = graphics->CreateBitmapFromImage(*mGreenImage);
    }

    auto bitmap = mBroken ? mRedBitmap : mGreenBitmap;
    int wid = mRedImage->GetWidth();
    int hit = mRedImage->GetHeight();

    // beam
    wxPen laser1(wxColour(255, 200, 200, 100), 8);
    wxPen laser2(wxColour(255, 0, 0, 175), 4);

    // draw the line to the pin
    graphics->SetPen(wxPen(*wxBLACK, LineThickness));
    graphics->StrokeLine(mX, mY, mOutputPin->GetX(), mOutputPin->GetY()); // Use -> to access methods
    mOutputPin->Draw(graphics); // Use -> to access methods

    graphics->SetPen(laser1);
    graphics->StrokeLine(mX - mSenderOffset, mY, mX, mY);
    graphics->SetPen(laser2);
    graphics->StrokeLine(mX - mSenderOffset, mY, mX, mY);

    // receiver
    graphics->DrawBitmap(bitmap, mX - wid / 2, mY - hit / 2, wid, hit);

    // mirrored
    graphics->PushState();
    graphics->Translate(mX - mSenderOffset, mY);
    graphics->Scale(-1, 1);
    graphics->DrawBitmap(bitmap, -wid / 2, -hit / 2, wid, hit);
    graphics->PopState();
}


/**
 * update the beam state
 * @param elpased time
 */
void Beam::Update(double elapsed)
{
    bool wasBroken = mBroken;
    mBroken = false;

    ProductVisitor productVisitor;
    for (const auto& item : GetGame()->GetItems()) {
        item->Accept(&productVisitor);
    }

    for (auto product : productVisitor.GetProducts()) {
        if (IsIntersecting(product)) {
            mBroken = true;
            product->SetPassedBeam(true);
            break;
        }
    }

    if (wasBroken != mBroken) {
        // set the output pin
    }
}

bool Beam::IsIntersecting(const Product* product)
{
    const int Padding = 5;
    double productX = product->GetX();
    double productY = product->GetY();
    double productSize = product->GetWidth();

    double x1 = mX - mSenderOffset;
    double y1 = mY;
    double x2 = mX;
    double y2 = mY;

    if (productY - productSize / 2 > y1 + Padding || // product is below beam
        productY + productSize / 2 < y1 - Padding) // product is above beam
    {
        return false;
    }

    if (productX + productSize / 2 < std::min(x1, x2) ||
        productX - productSize / 2 > std::max(x1, x2))
    {
        return false; // product is to left or right of beam
    }

    return true; // intersects beam
}
