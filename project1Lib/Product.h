/**
 * @file Product.h
 * @author Yeji Lee
 *
 * defines the properties and types of products moving down the conveyor.
 * provides constructor and getters to retrieve attributes
 */

#ifndef PRODUCT_H
#define PRODUCT_H

#include <map>
#include <string>
#include <Sparty.h>
#include "Item.h"

class Conveyor;

/// Default product size in pixels
const double ProductDefaultSize = 80.0;

/// Size to draw content relative to the product size
const double ContentScale = 0.8;

/**
 * class for the product
 * 
 */
class Product : public Item
{
public:
    /**
     * possible product properties
     * None property allows to indicate that the product has no content
     */
    enum class Properties
    {
        None, Red, Green, Blue, White, Square, Circle, Diamond,
        Izzo, Smith, Football, Basketball
    };

    /**
     * property types
     */
    enum class Types { Color, Shape, Content };

    /// maps for product properties
    static const std::map<Properties, Types> PropertiesToTypes;

    static const std::map<std::wstring, Properties> NamesToProperties; ///< Map of names to properties
    static const std::map<Properties, std::wstring> PropertiesToContentImages; ///< Map of properties to content images

    Product(Game* game, int placement, Properties shape, Properties color, Properties content, bool kick);

    /**
     * get the placement of the product on the conveyor
     *
     * @return the placement as an integer
     */
    int GetPlacement() const;

    /**
     * get the shape of the product
     *
     * @return the shape property
     */
    Properties GetShape() const;

    /**
     * get the color of the product
     *
     * @return the color property
     */
    Properties GetColor() const;

    /**
     * check if the procut should be kicked
     *
     * @return Trye if the product should be kicked
     */
    bool ShouldKick() const;

    void Update(double elapsed) override;
    void SetKicked(bool kicked, double kickSpeed);
    void SetOnConveyor(bool onConveyor, double conveyorSpeed);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * get the width of the product
     * 
     * @return double the width of the product 
     */
    double GetWidth() const { return mWidth; }

    /**
     * get the content of the product
     * 
     * @param conveyor the conveyor the product is on
     */
    void SetConveyor(Conveyor* conveyor) { mConveyor = conveyor; }

    /**
     * check if the product is on the conveyor
     * 
     * @param conveyor the conveyor to check
     * @return true if the product is on the conveyor
     */
    bool IsOnConveyor(const Conveyor* conveyor) const { return mConveyor == conveyor; }

    /**
     * moves the product down
     * 
     * @param distance the distance to move the product 
     */
    void MoveDown(double distance) { mY += distance; }


    void SetLocation(int x, int y) override;


    /**
     * getter of x location
     *
     * @return int
     */
    int GetX() const { return mX; }

    /**
     * getter of y location
     * 
     * @return int 
     */
    int GetY() const { return mY; }

    /**
     * setter of x location
     * 
     * @param x x location
     */
    void SetX(int x) { mX = x; }

    /**
     * setter of y location
     * 
     * @param y y location
     */
    void SetY(int y) { mY = y; }

    /**
     * accept a visitor
     * 
     * @param visitor 
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitProduct(this); }

    void ResetPosition();

    /**
     * check if the product has passed the beam
     * @return true if the product has passed the beam
     */
    bool GetPassedBeam() const { return mPassedBeam; }

    /**
     * set if the product has passed the beam
     * 
     * @param passed true if the product has passed the beam
     */
    void SetPassedBeam(bool passed) { mPassedBeam = passed; }

    void SetLast(bool isLast) { mLast = isLast; }

    void HasPassedBeam();

private:
    int mPlacement = 0; ///< Placement on conveyor
    Properties mShape; ///< Shape of the product
    Properties mColor; ///< Color of the product
    Properties mContent; ///< Content inside the product
    bool mKick; ///< Should the product be kicked?
    double mWidth = ProductDefaultSize; ///< Default width in pixels
    double mContentScale = 0.8; ///< Scale of content relative to the product size
    int mX; ///< x location
    int mY; ///< y location
    double mKickSpeed = 0; ///< Speed of the kick
    bool mIsOnConveyor = true; ///< Is the product on the conveyor?
    double mConveyorSpeed = 0; ///< Speed of the conveyor
    std::unique_ptr<wxImage> mContentImage; ///< Image of the content
    wxGraphicsBitmap mContentBitmap; ///< Bitmap of the content
    bool mPassedBeam = false; ///< Has the product passed the beam?

    int mInitialX = 0; ///< Initial x location
    int mInitialY = 0; ///< Initial y location


    Conveyor* mConveyor = nullptr; ///< The conveyor the product is on
    bool mLast = false; ///< Is the product the last one?
    double mLastProductDelay = 0; ///< Delay for the last product
};

#endif //PRODUCT_H
