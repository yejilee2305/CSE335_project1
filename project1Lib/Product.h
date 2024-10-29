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

    static const std::map<Product::Properties, Product::Types> PropertiesToTypes;

    /**
     * Constructor for the product
     *
     * @param placement the placement of the product on the conveyor
     * @param shape shape of the product
     * @param color color of the product
     * @param content  content inside the product
     * @param kick  whether the product should be kicked
     */
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

    double GetWidth() const { return mWidth; }
    void SetConveyor(Conveyor* conveyor) { mConveyor = conveyor; }
    bool IsOnConveyor(const Conveyor* conveyor) const { return mConveyor == conveyor; }
    void MoveDown(double distance) { mY += distance; }


    void SetLocation(int x, int y) override;

    int GetX() const { return mX; }
    int GetY() const { return mY; }

    void SetX(int x) { mX = x; }
    void SetY(int y) { mY = y; }

    void Accept(ItemVisitor* visitor) override { visitor->VisitProduct(this); }

    void ResetPosition();

private:
    int mPlacement = 0; // Placement on conveyor
    Properties mShape; // Shape of the product
    Properties mColor; // Color of the product
    Properties mContent; // Content inside the product
    bool mKick; // Should the product be kicked?
    double mWidth = 80; // Default width in pixels
    double mContentScale = 0.8; // Scale of content relative to the product size
    int mX, mY; // Position on conveyor
    double mKickSpeed = 0;
    bool mIsOnConveyor = true;
    double mConveyorSpeed = 0;
    std::unique_ptr<wxImage> mContentImage;
    wxGraphicsBitmap mContentBitmap;

    int mInitialX = 0;
    int mInitialY = 0;


    // Maps for product properties
    static const std::map<std::wstring, Properties> NamesToProperties;
    static const std::map<Properties, std::wstring> PropertiesToContentImages;
    Conveyor* mConveyor = nullptr;
};

#endif //PRODUCT_H
