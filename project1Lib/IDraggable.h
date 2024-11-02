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
    virtual void SetLocation(double x, double y) = 0;
    virtual ~IDraggable() = default;
    virtual void OnDrag(double x, double y) = 0;
};

#endif // IDRAGGABLE_H