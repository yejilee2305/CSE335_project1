/**
 * @file Sparty.h
 * @author Yeji Lee
 *
 * defines Sparty class
 * responsible for kicking products off the conveuor when triggered
 * contains position, height, kick speed, and kick duration
 */
 
#ifndef SPARTY_H
#define SPARTY_H

#include <string>
#include <wx/point.h>

class Sparty {
private:
 int mX;
 int mY;
 int mHeight;
 wxPoint2DDouble mPin;
 double mKickDuration;
 double mKickSpeed;

public:

 Sparty(int x, int y, int height, wxPoint2DDouble pin, double kickDuration, double kickSpeed);

 int GetX() const;
 int GetY() const;
 double GetKickSpeed() const;
 double GetKickDuration() const;

 void Kick();

};



#endif //SPARTY_H
