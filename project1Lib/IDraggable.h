/**
 * @file IDraggable.h
 * @author Praseedha Vinukonda
 *
 *
 */
 

#ifndef IDRAGGABLE_H
#define IDRAGGABLE_H

/**
 * class for the draggable interface
 * 
 */
class IDraggable {
public:
    /**
     * Virtual function to set location
     * @param x The X coordinate
     * @param y The Y coordinate
     */
    virtual void SetLocation(double x, double y) = 0;
    /**
     * Deconstructor
     */
    virtual ~IDraggable() = default;
    /**
     * Virtual function to drag the wire
     * @param x The X coordinate
     * @param y The Y coordinate
     */
    virtual void OnDrag(double x, double y) = 0;
};

#endif // IDRAGGABLE_H