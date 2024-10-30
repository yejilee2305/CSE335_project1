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

void Sensor::AddOutputPin(Product::Properties property)
{
    // Create new output pin
}

bool Sensor::IsProductInRange(const Product* product)
{
    // Example logic to determine if the product is in range
    if (product->GetPlacement() >= mY - 40 && product->GetPlacement() <= mY + 15) {
        return true;
    }
    return false;
}
