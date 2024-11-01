/**
 * @file Item.h
 * @author Zhi Lin
 *
 *
 */

#ifndef ITEM_H
#define ITEM_H

#include <vector>

#include "ItemVisitor.h"

class Game;


/**
 * the base class for all items in the game
 */
class Item
{
protected:
    /**
     * constructor
     *
     * @param game the game this item is in
     * @param filename the image file for the item
     */
    Item(Game* game, const std::wstring& filename);

    /**
     * getter for the game
     * @return the game
     */
    Game* GetGame() const { return mGame; }

private:
    /// The game this item is contained in
    Game* mGame;

    /// path of the image file
    std::wstring mPath;

    double mX = 0; ///< X location
    double mY = 0; ///< Y location

    /// the item image
    std::unique_ptr<wxImage> mItemImage;
    /// the bitmap we can display
    wxGraphicsBitmap mItemBitmap;

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
    ~Item();


    /**
     * accepts a visitor
     *
     * @param visitor the visitor to accept
     */
    virtual void Accept(ItemVisitor* visitor) = 0;

    /**
     * getter for x of item
     * @return x location
     */
    int GetX() const { return mX; }
    /**
     * getter for y of item
     * @return y location
     */
    int GetY() const { return mY; }

    /**
     * set the item location
     * @param x x location
     * @param y y location
     */
    virtual void SetLocation(int x, int y)
    {
        mX = x;
        mY = y;
    }


    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * update the item
     *
     * @param elapsed elapsed time
     */
    virtual void Update(double elapsed)
    {
    }

    virtual bool HitTest(double x, double y);

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

    void XmlLoad(wxXmlNode* node);
};


#endif //ITEM_H
