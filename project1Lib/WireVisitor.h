/**
 * @file WireVisitor.h
 * @author Praseedha Vinukonda
 *
 *
 */
 
#ifndef WIREVISITOR_H
#define WIREVISITOR_H

#include "ItemVisitor.h"
#include "Wire.h"
#include "Game.h"
#include <memory>


class AddWireVisitor: public ItemVisitor
{
private:
 Game* mGame;
public:
 AddWireVisitor() = default;
 AddWireVisitor(Game* game) : mGame(game) {}
 void VisitWire(Wire* wire) override
 {
  PinOutput* outputPin = wire->GetOutputPin();
  PinInput* inputPin = wire->GetInputPin();
  if (outputPin && inputPin) {
   mGame->AddWire(outputPin, inputPin);
  }
 }
};
class DrawWireVisitor: public ItemVisitor
{
private:
 Game* mGame;
 std::shared_ptr<wxGraphicsContext> mGraphics;
public:
 DrawWireVisitor()= default;
 DrawWireVisitor(Game* game, std::shared_ptr<wxGraphicsContext> graphics)
        : mGame(game), mGraphics(graphics) {}
 void VisitWire(Wire* wire) override
 {
  if (wire && mGraphics) {
   wire->Draw(mGraphics.get(), mGame->GetShowControlPoints());
  }
 }
};
class ClearWireVisitor : public ItemVisitor
{
private:
 Game* mGame;
public:
 ClearWireVisitor() = default;
 void VisitWire(Wire* wire) override
 {
  wire->Clear();
 }
};
class DrawItemVisitor : public ItemVisitor {
private:
 std::shared_ptr<wxGraphicsContext> mGraphics;
 bool mShowControlPoints;

public:
 DrawItemVisitor(std::shared_ptr<wxGraphicsContext> graphics, bool showControlPoints)
     : mGraphics(graphics), mShowControlPoints(showControlPoints) {}

 void VisitWire(Wire* wire) override {
  if (wire) {
   wire->Draw(mGraphics.get(), mShowControlPoints);
  }
 }

};
#endif //WIREVISITOR_H

