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
    // Constructor to initialize the sensor with camera and cable positions
    Sensor(Game* game, double cameraX, double cameraY, double cableX, double cableY, wxString sensorOutputs);
   /**
 * @brief Accepts a visitor for this sensor.
 * @param visitor Pointer to the ItemVisitor.
 */
    void Accept(ItemVisitor* visitor) override { visitor->VisitSensor(this); }

    /**
 * @brief Default constructor, deleted to avoid unintended instantiation.
 */
    Sensor() = delete;
    /**
 * @brief Copy constructor, deleted to avoid copying of Sensor objects.
 */
    Sensor(const Sensor&) = delete;
    /**
 * @brief Copy assignment operator, deleted to avoid copying of Sensor objects.
 */
    Sensor& operator=(const Sensor&) = delete;

   /**
    * @brief Destructor for Sensor.
    */
    virtual ~Sensor();

   /**
* @brief Draws the Sensor, including the camera, cable, and output pins.
* @param graphics Shared pointer to the wxGraphicsContext used for drawing.
*/
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
   /**
    * @brief Draws a single output pin on the sensor.
    * @param graphics Graphics context for rendering.
    * @param color Color of the output pin.
    * @param pin Pointer to the PinOutput to draw.
    * @param currentY Current Y-coordinate for pin placement.
    */
    void DrawOutputPin(std::shared_ptr<wxGraphicsContext> graphics, const wxColour& color, const std::unique_ptr<PinOutput>& pin, double& currentY);

    /**
     * @brief Sets the camera position.
     * @param x The new X-coordinate of the camera.
     * @param y The new Y-coordinate of the camera.
     */
    void SetCameraPosition(double x, double y);
    /**
 * @brief Sets the cable position.
 * @param x The new X-coordinate of the cable.
 * @param y The new Y-coordinate of the cable.
 */
    void SetCablePosition(double x, double y);
    /**
     * @brief Populates output pins based on sensor outputs string.
     * @param sensorOutputs String of output pin types.
     */
    void GetOutputPins(wxString sensorOutputs);
    /**
     * @brief Adds an output pin at a calculated location on the cable.
     * @param pin Pointer to the unique output pin.
     */
    void AddOutputPin(std::unique_ptr<PinOutput>& pin);

    /**
     * @brief Checks if a given product is within the sensor's range.
     * @param product Pointer to the product to check.
     * @return True if the product is in range, false otherwise.
     */
    bool IsProductInRange(const Product* product);

    /**
     * @brief Gets the X-coordinate of the sensor.
     * @return X-coordinate as a double.
     */
    double GetX() const { return mX; }
 /**
 * @brief Gets the Y-coordinate of the sensor.
 * @return Y-coordinate as a double.
 */
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

    int mSensorCount = 0; ///< Count of output pins added to the sensor

    std::unique_ptr<PinOutput> mRedOutput; ///< Output pin for red signal
    std::unique_ptr<PinOutput> mGreenOutput; ///< Output pin for green signal
    std::unique_ptr<PinOutput> mBlueOutput; ///< Output pin for blue signal
    std::unique_ptr<PinOutput> mWhiteOutput; ///< Output pin for white signal
    std::unique_ptr<PinOutput> mSquareOutput; ///< Output pin for square shape
    std::unique_ptr<PinOutput> mCircleOutput; ///< Output pin for circle shape
    std::unique_ptr<PinOutput> mDiamondOutput; ///< Output pin for diamond shape
    std::unique_ptr<PinOutput> mIzzoOutput; ///< Output pin for Izzo image
    std::unique_ptr<PinOutput> mSmithOutput; ///< Output pin for Smith image
    std::unique_ptr<PinOutput> mFootballOutput; ///< Output pin for football image
    std::unique_ptr<PinOutput> mBasketballOutput; ///< Output pin for basketball image

};

#endif // SENSOR_H
