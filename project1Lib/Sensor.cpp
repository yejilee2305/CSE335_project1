/**
* @file Sensor.cpp
  * @author zhi lin
  */

#include "pch.h"
#include "Sensor.h"
#include "Game.h"

const std::wstring SensorCameraImage = L"images/sensor-camera.png"; ///< Image for the camera
const std::wstring SensorCableImage = L"images/sensor-cable.png"; ///< Image for the cable
const std::wstring IzzoImage = L"images/izzo.png"; ///< Image for the Izzo
const std::wstring SmithImage = L"images/smith.png";  ///< Image for the Smith
const std::wstring FootballImage = L"images/football.png"; ///< Image for the football
const std::wstring BasketballImage = L"images/basketball.png"; ///< Image for the basketball

/**
 * @return the size of the property
 * 
 */
const wxSize PropertySize(100, 40);

/// Size of a shape as a property in virtual pixels
const double PropertyShapeSize = 32;

/// for drawing the line towards the output pin
const int LineThickness = 3;

/**
 * @return the color of the Ohio State Red
 */
const wxColour OhioStateRed(187, 0, 0);

/**
 * @return the color of the MSU Green
 */
const wxColour MSUGreen(24, 69, 59);

/**
 * @return the color of the UofM Blue
 */
const wxColor UofMBlue(0, 39, 76);

/**
 * @return the color of the Panel Background
 */
const wxColour PanelBackgroundColor(128, 128, 128);
/**
 * Constructs a Sensor object with specified positions and output pins.
 *
 * @param game Pointer to the Game instance.
 * @param cameraX X-coordinate of the camera position.
 * @param cameraY Y-coordinate of the camera position.
 * @param cableX X-coordinate of the cable position.
 * @param cableY Y-coordinate of the cable position.
 * @param sensorOutputs String containing sensor output types.
 */
Sensor::Sensor(Game* game, double cameraX, double cameraY, double cableX, double cableY, wxString sensorOutputs)
    : Item(game, L""), mCameraX(cameraX), mCameraY(cameraY), mCableX(cableX), mCableY(cableY)
{
    // Load the camera and cable images into bitmaps
    wxImage cameraImage(SensorCameraImage);
    wxImage cableImage(SensorCableImage);

    auto graphics = wxGraphicsContext::Create();
    mCameraBitmap = graphics->CreateBitmapFromImage(cameraImage);
    mCableBitmap = graphics->CreateBitmapFromImage(cableImage);

    mOutputPins = sensorOutputs;
    GetOutputPins(mOutputPins);
}
/**
 *  Destructor for Sensor.
 */
Sensor::~Sensor() {}
/**
 *  Sets the position of the camera.
 *
 * @param x The new X-coordinate of the camera.
 * @param y The new Y-coordinate of the camera.
 */
void Sensor::SetCameraPosition(double x, double y)
{
    mCameraX = x;
    mCameraY = y;
}
/**
 *  Sets the position of the cable.
 *
 * @param x The new X-coordinate of the cable.
 * @param y The new Y-coordinate of the cable.
 */
void Sensor::SetCablePosition(double x, double y)
{
    mCableX = x;
    mCableY = y;
}
/**
 *  Draws the Sensor, including camera and cable images, and the output pins.
 *
 * @param graphics Shared pointer to the wxGraphicsContext used for drawing.
 */
void Sensor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Dimensions for the camera and cable
    double cameraWidth = 168;
    double cameraHeight = 168;
    double cableWidth = 300;
    double cableHeight = 164;

    // Draw the camera bitmap at its designated position
    graphics->DrawBitmap(mCameraBitmap, mCameraX - 118, mCameraY - 70, cameraWidth, cameraHeight);

    // Draw the cable bitmap at its designated position
    graphics->DrawBitmap(mCableBitmap, mCableX - 140, mCableY -60, cableWidth, cableHeight);

    double boxY = mCableY+(cableHeight/2);
    double currentY = boxY;

    DrawOutputPin(graphics, OhioStateRed, mRedOutput, currentY);
    DrawOutputPin(graphics, MSUGreen, mGreenOutput, currentY);
    DrawOutputPin(graphics, UofMBlue, mBlueOutput, currentY);
    DrawOutputPin(graphics, *wxWHITE, mWhiteOutput, currentY);
    DrawOutputPin(graphics,PanelBackgroundColor, mSquareOutput, currentY);
    DrawOutputPin(graphics, PanelBackgroundColor, mCircleOutput, currentY);
    DrawOutputPin(graphics,PanelBackgroundColor, mDiamondOutput, currentY);
    DrawOutputPin(graphics, PanelBackgroundColor, mIzzoOutput, currentY);
    DrawOutputPin(graphics, PanelBackgroundColor, mSmithOutput, currentY);
    DrawOutputPin(graphics, PanelBackgroundColor, mFootballOutput, currentY);
    DrawOutputPin(graphics, PanelBackgroundColor, mBasketballOutput, currentY);

}
/**
 *  Populates output pins based on sensor outputs string.
 *
 * @param sensorOutputs String of output pin types.
 */
void Sensor::GetOutputPins(wxString sensorOutputs)
{
    while (!sensorOutputs.IsEmpty())
    {
        // Get the first word before the next space
        wxString token = sensorOutputs.BeforeFirst(' ');

        if (token == "red")
        {
            AddOutputPin(mRedOutput);
        }
        else if (token == "green")
        {
            AddOutputPin(mGreenOutput);
        }
        else if (token == "blue")
        {
            AddOutputPin(mBlueOutput);
        }
        else if (token == "white")
        {
            AddOutputPin(mWhiteOutput);
        }
        else if (token == "square")
        {
            AddOutputPin(mSquareOutput);
        }
        else if (token == "circle")
        {
            AddOutputPin(mCircleOutput);
        }
        else if (token == "diamond")
        {
            AddOutputPin(mDiamondOutput);
        }
        else if (token == "izzo")
        {
            AddOutputPin(mIzzoOutput);
        }
        else if (token == "smith")
        {
            AddOutputPin(mSmithOutput);
        }
        else if (token == "football")
        {
            AddOutputPin(mFootballOutput);
        }
        else if (token == "basketball")
        {
            AddOutputPin(mBasketballOutput);
        }

        // Remove the processed word and the leading space
        sensorOutputs = sensorOutputs.AfterFirst(' ');
    }
}
/**
 *  Draws a single output pin on the sensor.
 *
 * @param graphics Graphics context for rendering.
 * @param color Color of the output pin.
 * @param pin Pointer to the PinOutput to draw.
 * @param currentY Current Y-coordinate for pin placement.
 */
void Sensor::DrawOutputPin(std::shared_ptr<wxGraphicsContext> graphics, const wxColour& color, const std::unique_ptr<PinOutput>& pin, double& currentY)
{
    double cableWidth = 300;
    double boxX = mCableX + (cableWidth / 2) + 10;
    bool hasSpecialImage = false;
    wxBitmap specialImage;

    // Load specific images for certain output pins
    if (pin == mIzzoOutput)
    {
        specialImage.LoadFile(IzzoImage, wxBITMAP_TYPE_PNG);
        hasSpecialImage = true;
    }
    else if (pin == mSmithOutput)
    {
        specialImage.LoadFile(SmithImage, wxBITMAP_TYPE_PNG);
        hasSpecialImage = true;
    }
    else if (pin == mFootballOutput)
    {
        specialImage.LoadFile(FootballImage, wxBITMAP_TYPE_PNG);
        hasSpecialImage = true;
    }
    else if (pin == mBasketballOutput)
    {
        specialImage.LoadFile(BasketballImage, wxBITMAP_TYPE_PNG);
        hasSpecialImage = true;
    }

    if (pin)
    {
        graphics->SetBrush(wxBrush(color));
        graphics->SetPen(*wxBLACK_PEN);
        graphics->DrawRectangle(boxX, currentY, PropertySize.GetWidth(), PropertySize.GetHeight());

        if (hasSpecialImage && specialImage.IsOk())
        {
            wxGraphicsBitmap graphicsBitmap = graphics->CreateBitmap(specialImage);

            double imageX = boxX + (PropertySize.GetWidth() / 3);
            double imageY = currentY + (PropertySize.GetHeight() / 8);

            graphics->DrawBitmap(graphicsBitmap, imageX, imageY, PropertyShapeSize, PropertyShapeSize);
        }
        else if (pin == mCircleOutput || pin == mSquareOutput || pin == mDiamondOutput)
        {
            double shapeX = boxX + PropertySize.GetWidth() / 2;
            double shapeY = currentY + PropertySize.GetHeight() / 2;
            double shapeSize = PropertySize.GetHeight() * 0.8;
            graphics->SetBrush(*wxWHITE_BRUSH);

            if (pin == mCircleOutput)
            {
                graphics->DrawEllipse(shapeX - shapeSize / 2, shapeY - shapeSize / 2, PropertyShapeSize, PropertyShapeSize);
            }
            else if (pin == mSquareOutput)
            {
                graphics->DrawRectangle(shapeX - shapeSize / 2, shapeY - shapeSize / 2, PropertyShapeSize, PropertyShapeSize);
            }
            else if (pin == mDiamondOutput)
            {
                wxGraphicsPath path = graphics->CreatePath();
                path.MoveToPoint(shapeX, shapeY - shapeSize / 2);
                path.AddLineToPoint(shapeX + shapeSize / 2, shapeY);
                path.AddLineToPoint(shapeX, shapeY + shapeSize / 2);
                path.AddLineToPoint(shapeX - shapeSize / 2, shapeY);
                path.CloseSubpath();
                graphics->DrawPath(path);
            }
        }

        graphics->SetPen(wxPen(*wxBLACK, LineThickness));
        graphics->StrokeLine(boxX + PropertySize.GetWidth(), currentY + PropertySize.GetHeight() / 2,
                             boxX + PropertySize.GetWidth() + 20, currentY + PropertySize.GetHeight() / 2);

        currentY += PropertySize.GetHeight();
        pin->Draw(graphics);
    }
}
/**
 *  Adds a output pin at a calculated location on the cable.
 *
 * @param pin Pointer to the unique output pin.
 */
void Sensor::AddOutputPin(std::unique_ptr<PinOutput>& pin)
{
    double cableWidth = 300;
    double cableHeight = 164;
    double pinX = mCableX + (cableWidth / 2) + 130;
    double pinY = mCableY + (cableHeight / 2) + 20 + (mSensorCount * 40);
    pin = std::make_unique<PinOutput>();
    pin->SetLocation(pinX, pinY);
    mSensorCount++;
}
/**
 *  Checks if a given product is within the sensor's range.
 *
 * @param product Pointer to the product to check.
 * @return True if the product is in range, false otherwise.
 */
bool Sensor::IsProductInRange(const Product* product)
{
    // Example logic to determine if the product is in range
    if (product->GetPlacement() >= mY - 40 && product->GetPlacement() <= mY + 15) {
        return true;
    }
    return false;
}
