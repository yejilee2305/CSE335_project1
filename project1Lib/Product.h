#pragma once
#include <wx/wx.h>
#include <map>
#include <string>

class Product{
    public:
        /// given 
        /// The possible product properties.
        /// The None properties allows us to indicate that
        /// the product has no content.
        enum class Properties {None, Red, Green, Blue, White, Square, Circle, Diamond,
            Izzo, Smith, Football, Basketball};

        /// The property types
        enum class Types {Color, Shape, Content};

        Product(Properties shape, Properties color, Properties content, double placement, bool kick)


    private:
        /// given
        /// Mapping from the XML strings for properties to
        /// the Properties enum and the type of the property.
        static const std::map<std::wstring, Properties> NamesToProperties;

        /// Mapping from a property to it's type
        static const std::map<Properties, Types> PropertiesToTypes;

        /// Mapping from content properties to their associated image
        static const std::map<Product::Properties, std::wstring> PropertiesToContentImages;
}