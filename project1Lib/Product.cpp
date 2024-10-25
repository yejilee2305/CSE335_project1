/**
 * @file Product.cpp
 * @author Yeji Lee
 *
 * implement constructor and getter method
 */

#include "pch.h"
#include "Product.h"

/// Default product size in pixels
std::wstring ProductDefaultSize = L"80";

/// Size to draw content relative to the product size
double ContentScale = 0.8;

/// Color to use for "red"
const wxColour OhioStateRed(187, 0, 0);

/// Color to use for "green"
const wxColour MSUGreen(24, 69, 59);

/// Color to use for "blue"
const wxColor UofMBlue(0, 39, 76);

/// Delay after last product has left beam or
/// been kicked before we end the level.
const double LastProductDelay = 3;

const std::map<std::wstring, Product::Properties> Product::NamesToProperties = {
    {L"red", Product::Properties::Red},
    {L"green", Product::Properties::Green},
    {L"blue", Product::Properties::Blue},
    {L"white", Product::Properties::White},
    {L"square", Product::Properties::Square},
    {L"circle", Product::Properties::Circle},
    {L"diamond", Product::Properties::Diamond},
    {L"izzo", Product::Properties::Izzo},
    {L"smith", Product::Properties::Smith},
    {L"basketball", Product::Properties::Basketball},
    {L"football", Product::Properties::Football},
    {L"none", Product::Properties::None},
};

const std::map<Product::Properties, Product::Types> Product::PropertiesToTypes = {
    {Product::Properties::Red, Product::Types::Color},
    {Product::Properties::Green, Product::Types::Color},
    {Product::Properties::Blue, Product::Types::Color},
    {Product::Properties::White, Product::Types::Color},
    {Product::Properties::Square, Product::Types::Shape},
    {Product::Properties::Circle, Product::Types::Shape},
    {Product::Properties::Diamond, Product::Types::Shape},
    {Product::Properties::Izzo, Product::Types::Content},
    {Product::Properties::Smith, Product::Types::Content},
    {Product::Properties::Football, Product::Types::Content},
    {Product::Properties::Basketball, Product::Types::Content},
    {Product::Properties::None, Product::Types::Content}
};

const std::map<Product::Properties, std::wstring> Product::PropertiesToContentImages = {
    {Product::Properties::Izzo, L"izzo.png"},
    {Product::Properties::Smith, L"smith.png"},
    {Product::Properties::Football, L"football.png"},
    {Product::Properties::Basketball, L"basketball.png"}
};


// Constructor
Product::Product(int placement, Properties shape, Properties color, Properties content, bool kick)
    : mPlacement(placement), mShape(shape), mColor(color), mContent(content), mKick(kick), mX(0), mY(0)
{
}

// Method to move product based on the conveyor speed
void Product::Move(int conveyorSpeed)
{
    mX -= conveyorSpeed; // Update X position
}

// Getters
int Product::GetPlacement() const
{
    return mPlacement;
}

Product::Properties Product::GetShape() const
{
    return mShape;
}

Product::Properties Product::GetColor() const
{
    return mColor;
}

bool Product::ShouldKick() const
{
    return mKick;
}
