/**
 * @file Pins.h
 * @author Praseedha Vinukonda
 *
 *
 */
 
// Pins.h
#ifndef PINS_H
#define PINS_H

#include <wx/wx.h>
#include <vector>
class Gate;
enum class PinType { Input, Output };

class Pin {
public:
    PinType type;
    wxPoint position;
    bool isConnected;
    Pin* connectedTo;
    Gate* gate;  // Add this line

    Pin(PinType type, wxPoint position, Gate* gate);
    void Connect(Pin* otherPin);
    void Disconnect();
};

class Connection {
public:
    Pin* start;
    Pin* end;

    Connection(Pin* start, Pin* end);
    void Draw(wxGraphicsContext* graphics);
};

#endif // PINS_H
