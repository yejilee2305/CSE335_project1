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

class Product {
public:
    /// The possible product properties.
    /// The None properties allows us to indicate that
    /// the product has no content.
    enum class Properties {None, Red, Green, Blue, White, Square, Circle, Diamond,
        Izzo, Smith, Football, Basketball};

    /// The property types
    enum class Types {Color, Shape, Content};

    // Constructor
    Product(int placement, Properties shape, Properties color, Properties content, bool kick);

    // Getters
    int GetPlacement() const;
    Properties GetShape() const;
    Properties GetColor() const;
    bool ShouldKick() const;

    // Moves the product based on the conveyor's speed
    void Move(int conveyorSpeed);

private:
    int mPlacement;               // Placement on conveyor
    Properties mShape;             // Shape of the product
    Properties mColor;             // Color of the product
    Properties mContent;           // Content inside the product
    bool mKick;                    // Should the product be kicked?
    double mWidth = 80;            // Default width in pixels
    double mContentScale = 0.8;    // Scale of content relative to the product size
    int mX, mY;                    // Position on conveyor

    // Maps for product properties
    static const std::map<std::wstring, Properties> NamesToProperties;
    static const std::map<Properties, std::wstring> PropertiesToContentImages;
};

#endif //PRODUCT_H
