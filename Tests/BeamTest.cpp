/**
 * @file BeamTest.cpp
 * @author Zhi Lin
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <Product.h>
#include <Beam.h>

class BeamTest : public ::testing::Test
{
protected:
    Game mGame;
};


TEST_F(BeamTest, Constructor)
{
    auto beam = std::make_shared<Beam>(&mGame, 242, 437, -175);

    ASSERT_EQ(beam->GetX(), 67);
    ASSERT_EQ(beam->GetY(), 437);
    ASSERT_FALSE(beam->IsBroken());
}

TEST_F(BeamTest, ProductIntersection)
{
    auto beam = std::make_shared<Beam>(&mGame, 242, 437, -175);

    auto intersectingProduct = std::make_shared<Product>(&mGame,
                                                         100,
                                                         Product::Properties::Square,
                                                         Product::Properties::Red,
                                                         Product::Properties::None,
                                                         false);


    intersectingProduct->SetLocation(150, 437);

    ASSERT_TRUE(beam->IsIntersecting(intersectingProduct));
}

TEST_F(BeamTest, ProductNotIntersecting)
{
    auto beam = std::make_shared<Beam>(&mGame, 242, 437, -175);

    auto nonIntersectingProduct = std::make_shared<Product>(&mGame,
                                                            100,
                                                            Product::Properties::Square,
                                                            Product::Properties::Red,
                                                            Product::Properties::None,
                                                            false);


    nonIntersectingProduct->SetLocation(400, 437); // x position beyond beam

    ASSERT_FALSE(beam->IsIntersecting(nonIntersectingProduct));
}

TEST_F(BeamTest, ProductAboveBeam)
{
    auto beam = std::make_shared<Beam>(&mGame, 242, 437, -175);

    auto product = std::make_shared<Product>(&mGame,
                                             100,
                                             Product::Properties::Square,
                                             Product::Properties::Red,
                                             Product::Properties::None,
                                             false);

    product->SetLocation(150, 337); // y position 100 pixels above beam

    ASSERT_FALSE(beam->IsIntersecting(product));
}

TEST_F(BeamTest, ProductBelowBeam)
{
    auto beam = std::make_shared<Beam>(&mGame, 242, 437, -175);

    auto product = std::make_shared<Product>(&mGame,
                                             100,
                                             Product::Properties::Square,
                                             Product::Properties::Red,
                                             Product::Properties::None,
                                             false);

    product->SetLocation(150, 537); // y position 100 pixels below beam

    ASSERT_FALSE(beam->IsIntersecting(product));
}

TEST_F(BeamTest, BeamBreaking)
{
    auto beam = std::make_shared<Beam>(&mGame, 242, 437, -175);

    auto product = std::make_shared<Product>(&mGame,
                                             100,
                                             Product::Properties::Square,
                                             Product::Properties::Red,
                                             Product::Properties::None,
                                             false);

    product->SetLocation(150, 437);

    mGame.AddProduct(product);

    beam->Update(0.016); // 60 fps

    ASSERT_TRUE(beam->IsBroken());
}
