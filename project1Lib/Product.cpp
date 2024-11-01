/**
 * @file Product.cpp
 * @author Yeji Lee
 *
 */

#include "pch.h"
#include "Product.h"

#include "BeamVisitor.h"
#include "Conveyor.h"
#include "Game.h"


/**
 *  @return Ohio State Red
 */
const wxColour OhioStateRed(187, 0, 0);

/**
 *  @return MSU Green
 */
const wxColour MSUGreen(24, 69, 59);

/**
 * @return U of M Blue
 */
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


/**
 * contructor
 * 
 * @param game the game this item is in
 * @param placement the placement of the product on the conveyor
 * @param shape the shape of the product
 * @param color the color of the product
 * @param content the content inside the product
 * @param kick whether the product should be kicked
 */
Product::Product(Game* game, int placement, Properties shape, Properties color, Properties content, bool kick)
    : Item(game, L""), mPlacement(placement), mShape(shape), mColor(color), mContent(content), mKick(kick), mX(0), mY(0)
{
    mWidth = ProductDefaultSize;
}


/**
 * draw the product
 * 
 * @param graphics the graphics context to draw on
 */
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

/**
 * update the product
 * 
 * @param elapsed the time since the last update
 */
void Product::Update(double elapsed)
{
    if (mKick)
    {
        mX -= mKickSpeed * elapsed;
    }

    if (mIsOnConveyor && mConveyor != nullptr && mConveyor->IsRunning())
        MoveDown(mConveyor->GetSpeed() * elapsed);

    BeamVisitor beamVisitor;
    for (const auto& item : GetGame()->GetItems())
    {
        item->Accept(&beamVisitor);
    }

    for (auto beam : beamVisitor.GetBeams())
    {
        if (beam->IsIntersecting(this))
        {
            SetPassedBeam(true);
            HasPassedBeam();
            break;
        }
    }

    if (mLastProductDelay > 0)
    {
        mLastProductDelay -= elapsed;
        if (mLastProductDelay <= 0)
        {
            mLastProductDelay = 0;
            GetGame()->SetState(Game::GameState::Ending);
        }
    }
}

/**
 * set the product to be kicked
 * 
 * @param kicked whether the product should be kicked
 * @param kickSpeed the speed at which the product should be kicked
 */
void Product::SetKicked(bool kicked, double kickSpeed)
{
    mKick = kicked;
    mKickSpeed = kickSpeed;
}

/**
 * set the product to be on the conveyor
 * 
 * @param onConveyor whether the product is on the conveyor
 * @param conveyorSpeed the speed of the conveyor
 */
void Product::SetOnConveyor(bool onConveyor, double conveyorSpeed)
{
    mIsOnConveyor = onConveyor;
    mConveyorSpeed = conveyorSpeed;
}


/**
 * get the placement of the product
 * 
 * @return int the placement of the product
 */
int Product::GetPlacement() const
{
    return mPlacement;
}

/**
 * get the shape of the product
 * 
 * @return Product::Properties the shape of the product
 */
Product::Properties Product::GetShape() const
{
    return mShape;
}

/**
 * get the color of the product
 * 
 * @return Product::Properties the color of the product
 */
Product::Properties Product::GetColor() const
{
    return mColor;
}

/**
 * check if the product should be kicked
 * 
 * @return bool whether the product should be kicked
 */
bool Product::ShouldKick() const
{
    return mKick;
}

/**
 * set the location of the product
 * 
 * @param x the x location
 * @param y the y location
 */
void Product::SetLocation(int x, int y)
{
    mInitialX = x;
    mInitialY = y;
    mX = x;
    mY = y;
}

/**
 * reset the position of the product
 */
void Product::ResetPosition()
{
    mX = mInitialX;
    mY = mInitialY;
}

/**
 * Logic for after the product passes the beam
 */
void Product::HasPassedBeam()
{
    if (mLast)
    {
        mLastProductDelay = LastProductDelay;
    }
    // Scoring
}

