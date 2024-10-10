/**
 * @file Sparty.cpp
 * @author Yeji Lee
 *
 * implement the constructor, getter methods, and kick method
 * kick: contains logic for kicking products off conveyot
 */
 
#include "pch.h"
#include "Sparty.h"
#include "item.h"

Sparty::Sparty(int x, int y, int height, wxPoint2DDouble pin, double kickDuration, double kickSpeed)
    : mX(x), mY(y), mHeight(height), mPin(pin), mKickDuration(kickDuration), mKickSpeed(kickSpeed) {
}

int Sparty::GetX() const { return mX; }
int Sparty::GetY() const { return mY; }
double Sparty::GetKickSpeed() const { return mKickSpeed; }
double Sparty::GetKickDuration() const { return mKickDuration; }

void Sparty::Kick()
{

}