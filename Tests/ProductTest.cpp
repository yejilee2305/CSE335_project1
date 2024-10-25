/**
 * @file ProductTest.cpp
 * @author zhi lin
 */
// Add to Tests/ProductTest.cpp

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <Product.h>

class ProductTest : public ::testing::Test {
protected:
    Game mGame;
};

TEST_F(ProductTest, Constructor) {
    auto product = std::make_shared<Product>(&mGame, 100,  // placement
        Product::Properties::Square,  // shape
        Product::Properties::Red,     // color
        Product::Properties::None,    // no content
        true);                       // should kick

    ASSERT_NE(nullptr, product);
    ASSERT_EQ(100, product->GetPlacement());
    ASSERT_EQ(Product::Properties::Square, product->GetShape());
    ASSERT_EQ(Product::Properties::Red, product->GetColor());
    ASSERT_TRUE(product->ShouldKick());
}

