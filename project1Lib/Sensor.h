/**
  * @file Sensor.h
  * @author zhi lin
  *
  *
  */

#ifndef SENSOR_H
#define SENSOR_H

#include "pch.h"
#include "Item.h"
#include <memory.h>
#include "Product.h"

class Sensor : public Item
{
private:
    /// x location of the sensor
    double mX = 0;

    /// y location of the sensor
    double mY = 0;

    /// vector to store the active pins
    std::vector<Product::Properties> mOutputPins;

    /// camera image
    std::unique_ptr<wxImage> mCameraImage;

    /// cable image
    std::unique_ptr<wxImage> mCableImage;

protected:

public:
    /**
    * constructor
    */
    Sensor(Game* game, double x, double y);
    /// default constructor (disabled)
    Sensor() = delete;

    /// copy constructor (disabled)
    Sensor(const Sensor&) = delete;

    /// assignment operator (disabled)
    Sensor& operator=(const Sensor&) = delete;



    /**
     * destructor
     */
    virtual ~Sensor();

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void AddOutputPin(Product::Properties property);
    bool IsProductInRange(const Product* product);

    /**
     * updates the sensor state
     * @param elpased
     */
    void Update(double elpased) override;

    /**
     * getter for X
     * @return mX
     */
    double GetX() const { return mX; }

    /**
     * getter for Y
     * @return mY
     */
    double GetY() const { return mY; }
};


#endif //SENSOR_H
