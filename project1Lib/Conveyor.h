/**
* @file Conveyor.h
 * @author Martin Sattam
 */

#ifndef CONVEYOR_H
#define CONVEYOR_H

#include <wx/wx.h>
#include <string>

class Conveyor {
private:
 // Positions and dimensions of the conveyor
 int mX;
 int mY;
 int mHeight;
 int mWidth;

 // Speed of the conveyor
 int mSpeed;

 // Panel location based on conveyor position
 wxPoint mPanelLocation;

 // If the conveyor is running
 bool mIsRunning;

 // Define button rectangles for the start and stop buttons
 static const wxRect StartButtonRect;
 static const wxRect StopButtonRect;

public:
 // Constructor
 Conveyor(int x, int y, int speed, int height, const wxPoint& panelLocation);

 // Starts the conveyor and resets the products' positions
 void Start();

 // Stops the conveyor
 void Stop();

 // Resets product positions based on their initial locations
 void ResetProducts();

 // Draws the conveyor and its panel
 void Draw(wxGraphicsContext* graphics);

 // Checks if the Start button or Stop button is clicked
 bool CheckStartButtonClick(int mouseX, int mouseY) const;
 bool CheckStopButtonClick(int mouseX, int mouseY) const;

 // Getters for conveyor position
 int GetX() const;
 int GetY() const;
 int GetSpeed() const;
 bool IsRunning() const;

};

#endif // CONVEYOR_H
