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
 * class for the pins
 * 
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

 /// Draw the pin
 virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;

 virtual bool HitTest(double x, double y) const; // Hit test for the pin
 virtual void SetPosition(double x, double y);

 /// Get the X coordinate of the pin
 double GetX() const { return mX; }

 /// Get the Y coordinate of the pin
 double GetY() const { return mY; }
};

#endif // PINS_H

