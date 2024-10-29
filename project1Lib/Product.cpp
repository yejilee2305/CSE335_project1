/**
 * @file Product.cpp
 * @author Yeji Lee
 *
 * implement constructor and getter method
 */

#include "pch.h"
#include "Product.h"

#include "BeamVisitor.h"
#include "Conveyor.h"
#include "Game.h"


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
    {L"images/izzo", Product::Properties::Izzo},
    {L"images/smith", Product::Properties::Smith},
    {L"images/basketball", Product::Properties::Basketball},
    {L"images/football", Product::Properties::Football},
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
    {Product::Properties::Izzo, L"images/izzo.png"},
    {Product::Properties::Smith, L"images/smith.png"},
    {Product::Properties::Football, L"images/football.png"},
    {Product::Properties::Basketball, L"images/basketball.png"}
};


Product::Product(Game* game, int placement, Properties shape, Properties color, Properties content, bool kick)
    : Item(game, L""), mPlacement(placement), mShape(shape), mColor(color), mContent(content), mKick(kick), mX(0), mY(0)
{
    mWidth = ProductDefaultSize;
}


void Product::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (!graphics)
    {
        return;
    }

    double size = mWidth;
    double halfSize = mWidth / 2;

    //color
    wxBrush brush;
    switch (mColor)
    {
    case Properties::Red:
        brush = wxBrush(OhioStateRed);
        break;
    case Properties::Green:
        brush = wxBrush(MSUGreen);
        break;
    case Properties::Blue:
        brush = wxBrush(UofMBlue);
        break;
    default:
        brush = wxBrush(*wxWHITE);
    }

    graphics->SetBrush(brush);
    graphics->SetPen(*wxBLACK_PEN);

    switch (mShape)
    {
    case Properties::Square:
        graphics->DrawRectangle(mX - halfSize, mY - halfSize, size, size);
        break;
    case Properties::Circle:
        graphics->DrawEllipse(mX - halfSize, mY - halfSize, size, size);
        break;
    case Properties::Diamond:
        {
            double diamondHalfSize = halfSize * 1.4;
            auto path = graphics->CreatePath();
            path.MoveToPoint(mX, mY - diamondHalfSize);
            path.AddLineToPoint(mX + diamondHalfSize, mY);
            path.AddLineToPoint(mX, mY + diamondHalfSize);
            path.AddLineToPoint(mX - diamondHalfSize, mY);
            path.CloseSubpath();
            graphics->DrawPath(path);
        }
        break;

    default:
        break;
    }

    if (mContent != Properties::None)
    {
        auto it = Product::PropertiesToContentImages.find(mContent);
        if (it != Product::PropertiesToContentImages.end())
        {
            if (!mContentImage)
            {
                mContentImage = std::make_unique<wxImage>(it->second);
                mContentBitmap = graphics->CreateBitmapFromImage(*mContentImage);
            }
            double contentSize = size * mContentScale;
            double contentOffset = (size - contentSize) / 2;

            graphics->DrawBitmap(mContentBitmap, mX - halfSize + contentOffset, mY - halfSize + contentOffset,
                                 contentSize, contentSize);
        }
    }
}


void Product::Update(double elapsed)
{
    if (mKick)
    {
        mX -= mKickSpeed * elapsed;
    }

    if (mIsOnConveyor && mConveyor != nullptr && mConveyor->IsRunning())
        MoveDown(mConveyor->GetSpeed() * elapsed);

    BeamVisitor beamVisitor;
    for (const auto& item : GetGame()->GetItems()) {
        item->Accept(&beamVisitor);
    }

    for (auto beam : beamVisitor.GetBeams()) {
        if (beam->IsIntersecting(this)) {
            SetPassedBeam(true);
            break;
        }
    }
}

void Product::SetKicked(bool kicked, double kickSpeed)
{
    mKick = kicked;
    mKickSpeed = kickSpeed;
}

void Product::SetOnConveyor(bool onConveyor, double conveyorSpeed)
{
    mIsOnConveyor = onConveyor;
    mConveyorSpeed = conveyorSpeed;
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


void Product::SetLocation(int x, int y)
{
    mInitialX = x;
    mInitialY = y;
    mX = x;
    mY = y;
}

void Product::ResetPosition()
{
    mX = mInitialX;
    mY = mInitialY;
}
