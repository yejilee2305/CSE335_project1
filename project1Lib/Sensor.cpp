/**
  * @file Sensor.cpp
  * @author zhi lin
  */
#include "pch.h"
#include "Sensor.h"

/// The image file for the sensor cable
const std::wstring SensorCableImage = L"sensor-cable.png";

/// The image file for the sensor camera
const std::wstring SensorCameraImage = L"sensor-camera.png";

/// How far below Y location of the sensor system is the panel top?
const int PanelOffsetY = 87;

/// How much space for each property
const wxSize PropertySize(100, 40);

/// Size of a shape as a property in virtual pixels
const double PropertyShapeSize = 32;

/// Range where a product is viewed by the sensor relative
/// to the Y coordinate of the sensor.
const int SensorRange[] = {-40, 15};

/// The background color to draw the sensor panel
const wxColour PanelBackgroundColor(128, 128, 128);


/**
 * Constructor
 * @param x X location of the sensor
 * @param y Y location of the sensor
 */
Sensor::Sensor(double x, double y) : Item(SensorCameraImage)
{
    Item::SetLocation(x, y); // this is using item's default setlocation
    mCableImage = std::make_unique<wxImage>(SensorCableImage);
}


/**
 * Destructor
 */
Sensor::~Sensor()
{
}

/**
 * check if the product is in range of the sensor
 * @param product the product to check
 * @return true if in range, else false
 */
// bool Sensor::IsProductInRange(const Product* product)
// {
//     // add logic here
//     return false;
// }

/**
 *
 * @param property
 */
// void Sensor::AddOutputPin(Product::Properties property)
// {
//  mOutputPins.push_back(property);
// }
//
