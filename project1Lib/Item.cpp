/**
 * @file Item.cpp
 * @author Zhi Lin
 */
#include "pch.h"
#include "Item.h"

#include <wx/graphics.h>

/**
 * constructor
 * 
 * @param game the game this item is in 
 * @param filename the image file for the item
 */
Item::Item(Game* game, const std::wstring& filename) : mGame(game)
{
    if (!filename.empty())
    {
        mItemImage = std::make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    }
    //
    // if (!mItemImage->IsOk())
    // {
    //     wxMessageBox(filename, "Failed to load image");
    // }
    // else
    // {
    //     wxMessageBox(filename, "Successfully loaded image!");
    //
    // }
}

/**
 * handles a click on item
 * 
 * @param x X location clicked on
 * @param y Y location clicked on
 * @return true if the item was clicked on
 */
bool Item::HitTest(double x, double y)
{
    if (!mItemImage)
    {
        return false;
    }
    double width = mItemImage->GetSize().x;
    double height = mItemImage->GetSize().y;

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to theimage top corner
    double testX = x - GetX() + width / 2;
    double testY = y - GetY() + height / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= width || testY >= height)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    // If the location is transparent, we are not in the drawn
    // part of the image
    return !mItemImage->IsTransparent((int)testX, (int)testY);
}

/**
 * draws the item
 * @param graphics graphic object
 */
void Item::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mItemBitmap.IsNull())
    {
        mItemBitmap = graphics->CreateBitmapFromImage(*mItemImage);
    }

    graphics->DrawBitmap(mItemBitmap,
                         GetX() - mItemImage->GetWidth() / 2,
                         GetY() - mItemImage->GetHeight() / 2,
                         mItemImage->GetWidth(),
                         mItemImage->GetHeight());
}

/**
 * destructor
 */
Item::~Item()
{
}

/**
 * load the attributes for an item node.
 * @param node the xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode* node)
{
    auto position = node->GetAttribute("p", "0,0");
    position.BeforeFirst(',').ToDouble(&mX);
    position.AfterFirst(',').ToDouble(&mY);
}
