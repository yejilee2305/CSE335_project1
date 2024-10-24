/**
 * @file Pins.cpp
 * @author Praseedha Vinukonda
 */
 
#include "Pins.h"

// Pins.cpp
#include "pch.h"


Pin::Pin(PinType type, wxPoint position, Gate* gate)
    : type(type), position(position), isConnected(false), connectedTo(nullptr), gate(gate) {}

void Pin::Connect(Pin* otherPin) {
 if (this->type != otherPin->type) {
  this->isConnected = true;
  otherPin->isConnected = true;
  this->connectedTo = otherPin;
  otherPin->connectedTo = this;
 }
}

void Pin::Disconnect() {
 if (isConnected && connectedTo) {
  isConnected = false;
  connectedTo->isConnected = false;
  connectedTo->connectedTo = nullptr;
  connectedTo = nullptr;
 }
}

Connection::Connection(Pin* start, Pin* end) : start(start), end(end) {}

void Connection::Draw(wxGraphicsContext* graphics) {
 wxPoint p1 = start->position;
 wxPoint p4 = end->position;

 int offset = std::min(200.0, static_cast<double>(abs(p4.x - p1.x)));
 wxPoint p2(p1.x + offset, p1.y);
 wxPoint p3(p4.x - offset, p4.y);

 graphics->SetPen(wxPen(wxColour(128, 128, 128), 3));
 graphics->StrokeLine(p1.x, p1.y, p2.x, p2.y);
 graphics->StrokeLine(p2.x, p2.y, p3.x, p3.y);
 graphics->StrokeLine(p3.x, p3.y, p4.x, p4.y);
}