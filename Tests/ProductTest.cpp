/**
 * @file ProductTest.cpp
 * @author zhi lin
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <Product.h>

class ProductTest : public ::testing::Test
{
protected:
    Game mGame;
};

TEST_F(ProductTest, Constructor)
{
    auto product = std::make_shared<Product>(&mGame, 100, // placement
                                             Product::Properties::Square, // shape
                                             Product::Properties::Red, // color
                                             Product::Properties::None, // no content
                                             true); // should kick

    ASSERT_NE(nullptr, product);
    ASSERT_EQ(100, product->GetPlacement());
    ASSERT_EQ(Product::Properties::Square, product->GetShape());
    ASSERT_EQ(Product::Properties::Red, product->GetColor());
    ASSERT_TRUE(product->ShouldKick());
}

TEST_F(ProductTest, ContentProduct)
{
    auto product = std::make_shared<Product>(&mGame, 200,
                                             Product::Properties::Circle,
                                             Product::Properties::Green,
                                             Product::Properties::Izzo,
                                             false);

    ASSERT_EQ(200, product->GetPlacement());
    ASSERT_EQ(Product::Properties::Circle, product->GetShape());
    ASSERT_EQ(Product::Properties::Green, product->GetColor());
    ASSERT_FALSE(product->ShouldKick());
}

TEST_F(ProductTest, DiamondShape)
{
    auto product = std::make_shared<Product>(&mGame, 300,
                                             Product::Properties::Diamond,
                                             Product::Properties::Blue,
                                             Product::Properties::None,
                                             true);

    ASSERT_EQ(Product::Properties::Diamond, product->GetShape());
    ASSERT_EQ(Product::Properties::Blue, product->GetColor());
}


TEST_F(ProductTest, Position)
{
    auto product = std::make_shared<Product>(&mGame, 100,
                                             Product::Properties::Square,
                                             Product::Properties::Red,
                                             Product::Properties::None,
                                             false);

    ASSERT_NEAR(0, product->GetX(), 0.001);
    ASSERT_NEAR(0, product->GetY(), 0.001);

    product->SetLocation(150, 400);
    ASSERT_NEAR(150, product->GetX(), 0.001);
    ASSERT_NEAR(400, product->GetY(), 0.001);
}

TEST_F(ProductTest, MovementTest)
{
    auto product = std::make_shared<Product>(&mGame, 100,
                                             Product::Properties::Square,
                                             Product::Properties::Red,
                                             Product::Properties::None,
                                             false);

    product->SetLocation(150, 400);

    double conveyorSpeed = 100.0; // 100 pixels per second
    product->SetOnConveyor(true, conveyorSpeed);

    // update for 1 second
    product->Update(1.0);

    ASSERT_NEAR(150, product->GetX(), 0.001);
    ASSERT_NEAR(400, product->GetY(), 0.001);
}

TEST_F(ProductTest, KickMovementTest)
{
    auto product = std::make_shared<Product>(&mGame, 100,
                                             Product::Properties::Square,
                                             Product::Properties::Red,
                                             Product::Properties::None,
                                             true);

    product->SetLocation(150, 400);

    double kickSpeed = 200.0;
    product->SetKicked(true, kickSpeed);

    product->Update(0.5);

    ASSERT_NEAR(50, product->GetX(), 0.001);
    ASSERT_NEAR(400, product->GetY(), 0.001);
}

TEST_F(ProductTest, CombinedMovementTest)
{
    auto product = std::make_shared<Product>(&mGame, 100,
                                             Product::Properties::Square,
                                             Product::Properties::Red,
                                             Product::Properties::None,
                                             false);

    product->SetLocation(150, 400);

    product->SetOnConveyor(true, 100.0);
    product->Update(1.0);

    product->SetKicked(true, 200.0);
    product->Update(0.5);

    ASSERT_NEAR(50, product->GetX(), 0.1);
    ASSERT_NEAR(400, product->GetY(), 0.1);
}
