/**
* @file Gate.h
 * @author Praseedha Vinukonda
 *
 *
 */

#ifndef GATE_H
#define GATE_H
#include "Item.h"
#include "PinInput.h"
#include "PinOutput.h"
#include <wx/graphics.h>
#include <wx/pen.h>
#include <wx/brush.h>
#include "ids.h"
#include "States.h"

class Game;
class PinInput;
class PinOutput;


/**
 * @return the size of the OR gate
 */
const wxSize OrGateSize(75, 50); 

/**
 * @return the size of the AND gate
 */
const wxSize AndGateSize(75, 50); 

/**
 * @return the size of the NOT gate
 */
const wxSize NotGateSize(50, 50); 

/**
 * @return the size of the SR flip flop gate
 */
const wxSize SRFlipFlopSize(50, 75);

/**
 * @return the size of the D flip flop gate
 */
const wxSize DFlipFlopSize(50, 75); 


/**
 * represents a gate in the game
 *
 * the gates contian logic for input and output pins
 */
class Gate : public Item
{
private:
    ///< X position of the gate
    double mX = 0;
    ///< Y position of the gate
    double mY = 0;
    ///path member variable
    wxGraphicsPath mPath;
    /// Collection of logic gates
    std::vector<std::shared_ptr<Gate>> gates;
    /// Currently grabbed gate
    std::shared_ptr<Gate> mGrabbedGate;

protected:
    /// Input pins associated with the gate
    std::vector<PinInput> mInputPins;
    /// Output pins associated with the gate
    std::vector<PinOutput> mOutputPins;

public:
    /**
     * @brief Constructor for the Gate class.
     * @param game Pointer to the Game instance.
     * @param filename Name of the image file for the gate.
     */
    Gate(Game* game, const std::wstring& filename) : Item(game, filename)
    {
    }
    /**
     * draws the gate
     *
     * @param graphics
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0; // Pure virtual function to draw the gate
    /**
     * compute gate output
     *
     * virtual function
     */
    virtual States ComputeOutput() = 0; // Pure virtual function to compute the output
    /**
     *
     *
     * default destructor
     */
    virtual ~Gate() = default;
    
    /**
     * getter for x
     * 
     * @return double 
     */
    double GetX() const { return mX; }
    /**
     * getter for y
     * 
     * @return double 
     */
    double GetY() const { return mY; }
    /**
     *
     *
     * Get Width function of gate
     */
    virtual double GetWidth() const = 0; // Pure virtual function to get width
    /**
     *
     *
     * Get height function of gate
     */
    virtual double GetHeight() const = 0; // Pure virtual function to get height
    /**
     *On click function for gates
     *@param x X coordinate of the mouse click
     * @param y Y coordinate of the mouse click
     */
    void OnMouseClick(double x, double y);
    /**
     * Hit test function for gates
     *@param x X coordinate of the mouse click
     * @param y Y coordinate of the mouse click
     */
    virtual bool HitTest(double x, double y) const;
    /**
     * Set the position of the gates
     *@param x X coordinate of the mouse click
     * @param y Y coordinate of the mouse click
     */
    void SetPosition(double x, double y);

    /**
     * get the input pins
     * 
     * @return std::vector<PinInput>& 
     */
    std::vector<PinInput>& GetInputPins() { return mInputPins; }

    /**
     * get the output pins
     * 
     * @return std::vector<PinOutput>& 
     */
    std::vector<PinOutput>& GetOutputPins() { return mOutputPins; }

    /**
    *
    * Updating pin positions of gate
    */
    virtual void UpdatePinPositions() = 0;
    /**
    *
    *
    * Intializing the pins
    */
    void InitializePins();
    /**
     * accepts a visitor
     *
     * @param visitor
     */
    virtual void Accept(ItemVisitor* visitor) = 0;
};
/**
 * @class ORGate
 * @brief Class representing an OR gate.
 */
/**
 * class representing an OR gate
 */
class ORGate : public Gate
{
private:
    ///< State of input A
    States inputA;
    ///< State of input B
    States inputB;

public:
    /**
     * Constructor for the ORGate class.
     * @param game Pointer to the Game instance.
     */
    ORGate(Game* game);
    /**
     * set input A
     * @param state
     */
    void SetInputA(States state);
    /**
     * set input B
     * @param state
     */
    void SetInputB(States state);
    /**
     * Set the position of the OR gate
     *@param x X coordinate of the mouse click
     * @param y Y coordinate of the mouse click
     */
    void SetPosition(double x, double y);
    /**
     * compute output of OR gate
     *
     */
    States ComputeOutput() override;
    /**
     * Draw for OR
     * @param graphics
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    /**
     * update pin positions
     *
     */
    void UpdatePinPositions() override;
    /**
     * get width for OR
     * 
     * @return double the width 
     */
    double GetWidth() const override { return OrGateSize.GetWidth(); }

    /**
     * get height for OR
     * 
     * @return double the height 
     */
    double GetHeight() const override { return OrGateSize.GetHeight(); }
    ///< Gets a specific input pin
    PinInput* GetInputPin(int index);
    ///< Gets a specific output pin
    PinOutput* GetOutputPin();
     /**
      *Connect input for pins
      * @param inputIndex
      * @param outputPin 
      */
    void ConnectInput(int inputIndex, PinOutput* outputPin);
     /**
     * accepts a visitor
     *
     * @param visitor
     */
    void Accept(ItemVisitor* visitor) override;
};

/**
 * class representing an AND gate
 */
class ANDGate : public Gate
{
private:
    States inputA; ///< State of input A
    States inputB; ///< State of input B

public:
     /**
     * Constructor for the ANDGate class.
     * @param game Pointer to the Game instance.
     */
    ANDGate(Game* game);
     /**
     * set input A
     * @param state
     */
    void SetInputA(States state);
     /**
     * set input B
     * @param state
     */
    void SetInputB(States state);
     /**
     * compute output of OR gate
     *
     */
    States ComputeOutput() override;
     /**
     * Set the position of the AND gate
     *@param x X coordinate of the mouse click
     * @param y Y coordinate of the mouse click
     */
    void SetPosition(double x, double y);
    /**
     * Draw for AND
     * @param graphics
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
     /**
    * accepts a visitor
    *
    * @param visitor
    */
    void Accept(ItemVisitor* visitor);
    /**
     * get width
     * 
     * @return double 
     */
    double GetWidth() const override { return AndGateSize.GetWidth(); }
    /**
     * get height
     * 
     * @return double 
     */
    double GetHeight() const override { return AndGateSize.GetHeight(); }
    /**
    * update pin positions
    *
    */
    void UpdatePinPositions() override;
};

/**
 * class representing a NOT gate
 * 
 */
class NOTGate : public Gate
{
private:
 ///< State of input A
    States inputA;

public:
     /**
     * NOT gate constructor
     *
    */
    NOTGate(Game* game);
    /**
     * set input A
     * @param state
     */
    void SetInputA(States state);
     /**
     * set input B
     * @param state
     */
    void SetInputB(States state);
     /**
     * Computes output
     *
     */
    States ComputeOutput() override;
     /**
     * Set the position of the AND gate
     *@param x X coordinate of the mouse click
     * @param y Y coordinate of the mouse click
     */
    void SetPosition(double x, double y);
     /**
     * Draw for NOT
     * @param graphics
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    /**
     * get width
     *
     */
    double GetWidth() const override { return NotGateSize.GetWidth(); }
     /**
     * get height
     *
     */
    double GetHeight() const override { return NotGateSize.GetHeight(); }
    /**
     * update pins
     *
     */
    void UpdatePinPositions() override;
   /**
   * accepts a visitor
   *
   * @param visitor
   */
    void Accept(ItemVisitor* visitor) override;
};
/**
 * class representing a SR flip flop gate
 * 
 */
class SRFlipFlopGate : public Gate
{
private:
 ///< State of input S
    States inputS;
 ///< State of input R
    States inputR;
 ///< State of input Q
    States outputQ;
 ///< State of input Q'
    States outputQPrime;

public:
    /**
     * SR gate constructor
     *@param game
    */
    SRFlipFlopGate(Game* game);
     /**
     * set input S
     * @param state
     */
    void SetInputS(States state);
     /**
     * set input R
     * @param state
     */
    void SetInputR(States state);
     /**
     * compute output
     *
     */
    States ComputeOutput() override;
     /**
     * Set the position of the SR gate
     *@param x X coordinate of the mouse click
     * @param y Y coordinate of the mouse click
     */
    void SetPosition(double x, double y);
     /**
     * Draw for NOT
     * @param graphics
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
     /**
     * get width for the gate
     *
     */
    double GetWidth() const override { return AndGateSize.GetWidth(); }
     /**
     * get height for the gate
     *
     */
    double GetHeight() const override { return AndGateSize.GetHeight(); }
     /**
     * Updating pin positions
     *
     */
    void UpdatePinPositions() override;
     /**
     * vistor accept function
     * @param visitor
     */
    void Accept(ItemVisitor* visitor) override;
};

/**
 * class representing a D flip flop gate
 */
class DFlipFlopGate : public Gate
{
private:
 ///< State of input D
    States inputD;
 ///< State of input clock
    States clock;
 ///< State of input Q
    States outputQ;
    States outputQPrime; ///< State of input Q'

public:
    /**
     * D flip flop gate constructor
     *@param game
    */
    DFlipFlopGate(Game* game);
     /**
     * input D
     *@param state
    */
    void SetInputD(States state);
     /**
     * input clock
     *@param state
    */
    void SetClock(States state);
    /**
     * compute output
     *
    */
    States ComputeOutput() override;
     /**
     * Set the position of the SR gate
     *@param x X coordinate of the mouse click
     * @param y Y coordinate of the mouse click
     */
    void SetPosition(double x, double y);
     /**
     * Draw for D flip flop
     * @param graphics
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    /**
     * get width for the gate
     *
     */
    double GetWidth() const override { return AndGateSize.GetWidth(); }
    /**
     * get height for the gate
     *
     */
    double GetHeight() const override { return AndGateSize.GetHeight(); }
     /**
     * update pin positions
     *
     */
    void UpdatePinPositions() override;
    /**
    * vistor accept function
    * @param visitor
    */
    void Accept(ItemVisitor* visitor) override;
};

#endif //GATE_H
