/**
 * @file Pins.cpp
 * @author Praseedha Vinukonda
 */
// Pins.cpp
#include "pch.h"
#include "Pins.h"
/**
 * @brief Determines if a given point is within the pin's area.
 *
 * This function checks if the specified (x, y) coordinates are within the hit area
 * of the pin by calculating the distance from the pin's center.
 *
 * @param x X-coordinate of the point to check.
 * @param y Y-coordinate of the point to check.
 * @return True if the point is within the hit area, false otherwise.
 */
bool Pins::HitTest(double x, double y) const
{
    double dx = x - mX;
    double dy = y - mY;
    return (dx * dx + dy * dy) <= (PinSize * PinSize / 4);
}
/**
 * @brief Sets the pin's position.
 *
 * This method updates the pin's internal coordinates to the specified (x, y) location.
 *
 * @param x The new X-coordinate for the pin.
 * @param y The new Y-coordinate for the pin.
 */
void Pins::SetPosition(double x, double y)
{
    mX = x;
    mY = y;
}