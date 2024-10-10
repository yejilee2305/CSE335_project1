/**
 * @file Product.h
 * @author Yeji Lee
 *
 * defines the properties and types of products moving down the conveyor.
 * provides constructor and getters to retrieve attributes
 */
 
#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <map>
#include <wx/colour.h>

class Product {
private:
    int mPlacement;
    Properties mShape;
    Properties mColor;
    Properties mContent;
    bool mKick;

public:
    enum class Properties {None, Red, Green, Blue, White, Square, Circle, Diamond, Izzo, Smith, Football, Basketball};

    // property types
    enum class Types {Color, Shape, Content};

    // constructor
    Product(int placement, Properties shape, Properties color, Properties content = Properties::None, bool kick = false);

    // getters
    int GetPlacement() const;

    Properties GetShape() const;

    Properties GetColor() const;

    Properties GetContent() const;

    bool ShouldKick() const;

    // Sstatic map - properties
    static const std::map<std::wstring, Properties> NamesToProperties;
    static const std::map<Properties, Types> PropertiesToTypes;
    static const std::map<Properties, std::wstring> PropertiesToContentImages;

};



#endif //PRODUCT_H
