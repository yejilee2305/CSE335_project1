/**
 * @file Pins.cpp
 * @author Praseedha Vinukonda
 */
// Pins.cpp
#include "pch.h"
#include "Pins.h"

bool Pins::HitTest(double x, double y) const
{
    double dx = x - mX;
    double dy = y - mY;
    return (dx * dx + dy * dy) <= (PinSize * PinSize / 4);
}

void Pins::SetPosition(double x, double y)
{
    mX = x;
    mY = y;
}