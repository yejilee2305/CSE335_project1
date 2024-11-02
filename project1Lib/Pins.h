/**
 * @file Pins.h
 * @author Praseedha Vinukonda
 *
 *
 */
 
// Pins.h
#ifndef PINS_H
#define PINS_H

#include <wx/graphics.h>
#include "IDraggable.h"
#include <memory>

class Pins;  // Forward declaration

/**
 * @class Pins
 * @brief Abstract base class representing a pin on a 2D plane, capable of being hit-tested and positioned.
 *
 * The Pins class provides basic attributes, such as X and Y coordinates, and
 * an abstract Draw method that must be implemented by derived classes. It
 * includes support for hit-testing to determine if a point is within the
 * pin's area and supports position setting.
 */
class Pins : public IDraggable
{
protected:
 /// The X coordinate of the pin
 double mX = 0;

 /// The Y coordinate of the pin
 double mY = 0;

 /// The diameter of the pin
 static const int PinSize = 10;

 /// The default length of the line from the pin
 static const int DefaultLineLength = 20;

public:
 /// Constructor
 Pins() = default;

 /// Destructor
 virtual ~Pins() = default;

 /**
  * @brief Pure virtual method for drawing the pin.
  *
  * This method must be implemented by derived classes to define specific
  * drawing behavior for the pin.
  *
  * @param graphics Shared pointer to a wxGraphicsContext for drawing operations.
  */
 virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;
 /**
  * @brief Performs a hit test to determine if a point is within the pin's area.
  *
  * Calculates whether the given coordinates (x, y) fall within the pin's
  * circular area.
  *
  * @param x X coordinate of the point to test.
  * @param y Y coordinate of the point to test.
  * @return True if the point is within the pin's area, false otherwise.
  */
 virtual bool HitTest(double x, double y) const;
 /**
 * @brief Sets the position of the pin.
 *
 * Updates the pin's coordinates to a new (x, y) location.
 *
 * @param x New X coordinate for the pin.
 * @param y New Y coordinate for the pin.
 */
 virtual void SetPosition(double x, double y);

 /**
  * @brief Retrieves the X coordinate of the pin.
  * @return X coordinate as a double.
  */
 double GetX() const { return mX; }

 /**
  * @brief Retrieves the Y coordinate of the pin.
  * @return Y coordinate as a double.
  */
 double GetY() const { return mY; }
};

#endif // PINS_H

