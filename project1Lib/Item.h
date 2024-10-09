/**
 * @file Item.h
 * @author Zhi Lin
 *
 *
 */

#ifndef ITEM_H
#define ITEM_H

#include "pch.h"
#include <vector>

class Item
{
protected:
    Item(const std::wstring& filename); // probably need to add the "Aquarium" class equivalent 🚧🚧🚧🚧🚧

private:
    /// path of the image file
    std::wstring mPath;

    int mX = 0; ///< X location
    int mY = 0; ///< Y location

    /// the item image
    std::unique_ptr<wxImage> mItemImage;
    /// the bitmap we can display
    std::unique_ptr<wxBitmap> mItemBitmap;

    /// item width
    double mWidth = 0;

    /// item height
    double mHeight = 0;

public:
    /// default constructor (disabled)
    Item() = delete;

    /// copy operator (disabled)
    Item(const Item&) = delete;

    /**
     * destructor
     */
    virtual ~Item()
    {
    };

    /**
     *  getter for x of item
     * @return x location
     */
    int GetX() const { return mX; }
    /**
     *  getter for y of item
     * @return y location
     */
    int GetY() const { return mY; }

    /**
     * set the item location
     * @param x x location
     * @param y y location
     */
    virtual void SetLocation(int x, int y) { mX = x; mY = y; }

    /**
     * draw this item
     * @param graphics graphic object to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * update the class in time
     * @param elpased elapsed time in ms
     */
    virtual void Update(double elpased)
    {
    }

    /**
     * handles a click on item
     * @param x X location clicked on
     * @param y Y location clicked on
     * @return true if clicked on item
     */
    virtual bool HitTest(int x, int y);

    /**
     * getter for width
     * @return width
     */
    double GetWidth() { return mWidth; }
    /**
     * getter for height
     * @return height
     */
    double GetHeight() { return mHeight; }
};


#endif //ITEM_H
