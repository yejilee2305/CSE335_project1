/**
* @file Sensor.h
  * @author zhi lin
  *
  *
  */

#ifndef SENSOR_H
#define SENSOR_H

#include "Item.h"
#include <memory>
#include <vector>
#include "Product.h"

class Sensor : public Item
{
public:
 // Constructor to initialize the sensor with camera and cable positions
 Sensor(Game* game, double cameraX, double cameraY, double cableX, double cableY);

 // Default constructor and copy operations are disabled
 Sensor() = delete;
 Sensor(const Sensor&) = delete;
 Sensor& operator=(const Sensor&) = delete;

 // Destructor
 virtual ~Sensor();

 // Draw method to render the camera and cable
 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

 // Set individual positions for camera and cable
 void SetCameraPosition(double x, double y);
 void SetCablePosition(double x, double y);

 // Add an output pin based on product properties
 void AddOutputPin(Product::Properties property);

 // Check if a product is within range of the sensor
 bool IsProductInRange(const Product* product);

 // Getters for X and Y positions
 double GetX() const { return mX; }
 double GetY() const { return mY; }

private:
 // X and Y positions of the sensor base
 double mX = 0;
 double mY = 0;

 // Separate X and Y positions for the camera and cable
 double mCameraX, mCameraY;
 double mCableX, mCableY;

 // Bitmaps for camera and cable
 wxGraphicsBitmap mCameraBitmap;
 wxGraphicsBitmap mCableBitmap;

 // Vector to store the active pins
 std::vector<Product::Properties> mOutputPins;
};

#endif // SENSOR_H
