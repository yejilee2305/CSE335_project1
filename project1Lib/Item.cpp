/**
 * @file Item.cpp
 * @author Zhi Lin
 */
#include "pch.h"
#include "Item.h"

#include <wx/graphics.h>

/**
 * constructor 🚧🚧🚧 probably need the underlying class like "aquarium"
 * @param filename the name of the file for this item
 */
Item::Item(const std::wstring& filename)
{
    mItemImage = std::make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    mItemBitmap = std::make_unique<wxBitmap>(*mItemImage);
}

/**
 * implementation from Aquarium steps
 * test to see if we hit this orbject with a mouse
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit
 */
bool Item::HitTest(int x, int y)
{
    double width = mItemBitmap->GetSize().x;
    double height = mItemBitmap->GetSize().y;

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
    double width = mItemBitmap->GetWidth();
    double height = mItemBitmap->GetHeight();

    // the x: and y: is calculating the top left
    graphics->DrawBitmap(*mItemBitmap, int(GetX() - width / 2), int(GetY() - height / 2), width, height);
}
