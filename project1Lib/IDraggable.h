/**
 * @file IDraggable.h
 * @author Praseedha Vinukonda
 *
 *
 */
 

#ifndef IDRAGGABLE_H
#define IDRAGGABLE_H

class IDraggable {
public:
    virtual void SetLocation(double x, double y) = 0;
    virtual ~IDraggable() = default;
};

#endif // IDRAGGABLE_H