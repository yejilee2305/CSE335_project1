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
/**
 * @class Sensor
 * @brief Represents a sensor component in the game, displaying outputs and interacting with products.
 *
 * The Sensor class manages the positions and visual representation of its camera, cable,
 * and output pins. It allows for checking if specific products are in range and supports
 * customizable positions for the camera and cable.
 */
class Sensor : public Item
{
public:
    /**
     * @brief Constructs a Sensor object with specified game reference and positions for camera and cable.
     * @param game Pointer to the Game instance.
     * @param cameraX X-coordinate of the camera.
     * @param cameraY Y-coordinate of the camera.
     * @param cableX X-coordinate of the cable.
     * @param cableY Y-coordinate of the cable.
     * @param sensorOutputs String specifying the types of output pins.
     */
    Sensor(Game* game, double cameraX, double cameraY, double cableX, double cableY, wxString sensorOutputs);
    void Accept(ItemVisitor* visitor) override { visitor->VisitSensor(this); }

    // Default constructor and copy operations are disabled
    Sensor() = delete;
    Sensor(const Sensor&) = delete;
    Sensor& operator=(const Sensor&) = delete;

    // Destructor
    virtual ~Sensor();

    // Draw method to render the camera and cable
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void DrawOutputPin(std::shared_ptr<wxGraphicsContext> graphics, const wxColour& color, const std::unique_ptr<PinOutput>& pin, double& currentY);

    // Set individual positions for camera and cable
    void SetCameraPosition(double x, double y);
    void SetCablePosition(double x, double y);

    void GetOutputPins(wxString sensorOutputs);

    void AddOutputPin(std::unique_ptr<PinOutput>& pin);

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

    // String to store the active pins
    wxString mOutputPins;

    int mSensorCount = 0;
    // Pin outputs for sensor
    std::unique_ptr<PinOutput> mRedOutput;
    std::unique_ptr<PinOutput> mGreenOutput;
    std::unique_ptr<PinOutput> mBlueOutput;
    std::unique_ptr<PinOutput> mWhiteOutput;
    std::unique_ptr<PinOutput> mSquareOutput;
    std::unique_ptr<PinOutput> mCircleOutput;
    std::unique_ptr<PinOutput> mDiamondOutput;
    std::unique_ptr<PinOutput> mIzzoOutput;
    std::unique_ptr<PinOutput> mSmithOutput;
    std::unique_ptr<PinOutput> mFootballOutput;
    std::unique_ptr<PinOutput> mBasketballOutput;

};

#endif // SENSOR_H
