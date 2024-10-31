/**
* @file Sensor.cpp
  * @author zhi lin
  */

#include "pch.h"
#include "Sensor.h"
#include "Game.h"

// File paths for the camera and cable images
const std::wstring SensorCameraImage = L"images/sensor-camera.png";
const std::wstring SensorCableImage = L"images/sensor-cable.png";

/// How much space for each property
const wxSize PropertySize(100, 40);

/// for drawing the line towards the output pin
const int LineThickness = 3;

/// Color to use for "red"
const wxColour OhioStateRed(187, 0, 0);

/// Color to use for "green"
const wxColour MSUGreen(24, 69, 59);

/// Color to use for "blue"
const wxColor UofMBlue(0, 39, 76);

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

Sensor::~Sensor() {}

void Sensor::SetCameraPosition(double x, double y)
{
    mCameraX = x;
    mCameraY = y;
}

void Sensor::SetCablePosition(double x, double y)
{
    mCableX = x;
    mCableY = y;
}

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

    double boxX = mCableX+(cableWidth/2)+10;
    double boxY = mCableY+(cableHeight/2);
    double currentY = boxY;

    DrawOutputPin(graphics, OhioStateRed, mRedOutput, currentY);
    DrawOutputPin(graphics, MSUGreen, mGreenOutput, currentY);
    DrawOutputPin(graphics, UofMBlue, mBlueOutput, currentY);
    DrawOutputPin(graphics, *wxWHITE, mWhiteOutput, currentY);
    DrawOutputPin(graphics,*wxLIGHT_GREY, mSquareOutput, currentY);
    DrawOutputPin(graphics, *wxLIGHT_GREY, mCircleOutput, currentY);
    DrawOutputPin(graphics,*wxLIGHT_GREY, mDiamondOutput, currentY);
    DrawOutputPin(graphics, *wxLIGHT_GREY, mIzzoOutput, currentY);
    DrawOutputPin(graphics,*wxLIGHT_GREY, mSmithOutput, currentY);
    DrawOutputPin(graphics, *wxLIGHT_GREY, mFootballOutput, currentY);
    DrawOutputPin(graphics, *wxLIGHT_GREY, mBasketballOutput, currentY);

}

void Sensor::GetOutputPins(wxString sensorOutputs)
{
    while (!sensorOutputs.IsEmpty())
    {
        // Get the first word before the next space
        wxString token = sensorOutputs.BeforeFirst(' ');

        // Process the token
        if (token == "red")
        {
            AddOutputPin(Product::Properties::Red);
        }
        else if (token == "green")
        {
            AddOutputPin(Product::Properties::Green);
        }
        else if (token == "blue")
        {
            AddOutputPin(Product::Properties::Blue);
        }
        else if (token == "white")
        {
            AddOutputPin(Product::Properties::White);
        }
        else if (token == "square")
        {
            AddOutputPin(Product::Properties::Square);
        }
        else if (token == "circle")
        {
            AddOutputPin(Product::Properties::Circle);
        }
        else if (token == "diamond")
        {
            AddOutputPin(Product::Properties::Diamond);
        }
        else if (token == "izzo")
        {
            AddOutputPin(Product::Properties::Izzo);
        }
        else if (token == "smith")
        {
            AddOutputPin(Product::Properties::Smith);
        }
        else if (token == "basketball")
        {
            AddOutputPin(Product::Properties::Basketball);
        }
        else if (token == "football")
        {
            AddOutputPin(Product::Properties::Football);
        }

        // Remove the processed word and the leading space
        sensorOutputs = sensorOutputs.AfterFirst(' ');
    }
}

void Sensor::DrawOutputPin(std::shared_ptr<wxGraphicsContext> graphics, const wxColour& color, const std::unique_ptr<PinOutput>& pin, double& currentY)
{
    double cableWidth = 300;
    double boxX = mCableX+(cableWidth/2)+10;

    if (pin)
    {
        graphics->SetBrush(wxBrush(color));
        graphics->SetPen(*wxBLACK_PEN);
        graphics->DrawRectangle(boxX, currentY, PropertySize.GetWidth(), PropertySize.GetHeight());
        graphics->SetPen(wxPen(*wxBLACK, LineThickness));
        graphics->StrokeLine(boxX + PropertySize.GetWidth(), currentY + PropertySize.GetHeight() / 2,
                             boxX + PropertySize.GetWidth() + 20, currentY + PropertySize.GetHeight() / 2);
        currentY += PropertySize.GetHeight();
        pin->Draw(graphics);
    }
}

void Sensor::AddOutputPin(Product::Properties property)
{
    double cableWidth = 300;
    double cableHeight = 164;

    std::unique_ptr<PinOutput> outputPin = nullptr;

    double pinX = mCableX+(cableWidth/2)+130;
    double pinY = mCableY+(cableHeight/2)+20+(mSensorCount * 40);

    // Determine which pin to create based on the property
    switch (property) {
        case Product::Properties::Red:
            outputPin = std::make_unique<PinOutput>();
            outputPin->SetLocation(pinX, pinY);
            mRedOutput = std::move(outputPin);
            mSensorCount++;
            break;
        case Product::Properties::Green:
            outputPin = std::make_unique<PinOutput>();
            outputPin->SetLocation(pinX, pinY);
            mGreenOutput = std::move(outputPin);
            mSensorCount++;
            break;
        case Product::Properties::Blue:
            outputPin = std::make_unique<PinOutput>();
            outputPin->SetLocation(pinX, pinY);
            mBlueOutput = std::move(outputPin);
            mSensorCount++;
            break;
        case Product::Properties::White:
            outputPin = std::make_unique<PinOutput>();
            outputPin->SetLocation(pinX, pinY);
            mWhiteOutput = std::move(outputPin);
            mSensorCount++;
            break;
        case Product::Properties::Square:
            outputPin = std::make_unique<PinOutput>();
            outputPin->SetLocation(pinX, pinY);
            mSquareOutput = std::move(outputPin);
            mSensorCount++;
            break;
        case Product::Properties::Circle:
            outputPin = std::make_unique<PinOutput>();
            outputPin->SetLocation(pinX, pinY);
            mCircleOutput = std::move(outputPin);
            mSensorCount++;
            break;
        case Product::Properties::Diamond:
            outputPin = std::make_unique<PinOutput>();
            outputPin->SetLocation(pinX, pinY);
            mDiamondOutput = std::move(outputPin);
            mSensorCount++;
            break;
        case Product::Properties::Izzo:
            outputPin = std::make_unique<PinOutput>();
            outputPin->SetLocation(pinX, pinY);
            mIzzoOutput = std::move(outputPin);
            mSensorCount++;
            break;
        case Product::Properties::Smith:
            outputPin = std::make_unique<PinOutput>();
            outputPin->SetLocation(pinX, pinY);
            mSmithOutput = std::move(outputPin);
            mSensorCount++;
            break;
        case Product::Properties::Basketball:
            outputPin = std::make_unique<PinOutput>();
            outputPin->SetLocation(pinX, pinY);
            mBasketballOutput = std::move(outputPin);
            mSensorCount++;
            break;
        case Product::Properties::Football:
            outputPin = std::make_unique<PinOutput>();
            outputPin->SetLocation(pinX, pinY);
            mFootballOutput = std::move(outputPin);
            mSensorCount++;
            break;
    }
}

bool Sensor::IsProductInRange(const Product* product)
{
    // Example logic to determine if the product is in range
    if (product->GetPlacement() >= mY - 40 && product->GetPlacement() <= mY + 15) {
        return true;
    }
    return false;
}
