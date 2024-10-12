/**
 * @file Beam.cpp
 * @author zhi lin
 */

#include "Beam.h"
/// Image for the beam sender and receiver when red
const std::wstring BeamRedImage = L"beam-red.png";

/// Image for the beam sender and receiver when green
const std::wstring BeamGreenImage = L"beam-green.png";

/// X offset for the beam pin in pixels
/// This is larger than normal to get it past Sparty's feet
const int BeamPinOffset = 80;

/**
 * constructor
 * @param x x location
 * @param y y location
 * @param senderOffset offset for the beam sender
 */
Beam::Beam(int x, int y, int senderOffset) : Item(BeamGreenImage)
{
    mX = x;
    mY = y;
    mSenderOffset = senderOffset;

    mRedImage = std::make_unique<wxImage>(BeamRedImage, wxBITMAP_TYPE_ANY);
    mGreenImage = std::make_unique<wxImage>(BeamGreenImage, wxBITMAP_TYPE_ANY);
}

/**
 * draw the beam
 * @param graphics graphic context
 */
void Beam::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    wxPen laser1(wxColour(255, 200, 200, 100), 8);
    wxPen laser2(wxColour(255, 0, 0, 175), 4);
    // implement later
}

/**
 * update the beam state
 * @param elpased time
 */
void Beam::Update(double elpased)
{
    // implement later
}

/**
 * test if the point hits the beam
 * @param x x location
 * @param y y location
 * @return true if hit, else false
 */
bool Beam::HitTest(int x, int y)
{
    //implement later
    return false;
}
