/**
 * @file ItemTest.cpp
 * @author Zhi Lin
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Game.h>

const std::wstring randomFile = L"images/izzo.png";

class ItemMock : public Item
{
public:
    ItemMock(Game* game): Item(game, randomFile)
    {
    }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override
    {
    };
};

TEST(ItemTest, Constructor)
{
    Game game;
    ItemMock item(&game);
}

TEST(ItemTest, GettersSetters)
{
    Game game;
    ItemMock item(&game);

    item.SetLocation(10.0, 10.0);

    ASSERT_NEAR(10.0, item.GetX(), 0.0001);
    ASSERT_NEAR(10.0, item.GetY(), 0.0001);
}


TEST(ItemTest, HitTest)
{
    Game game;
    ItemMock item(&game);

    item.SetLocation(200.0, 200.0);
    ASSERT_TRUE(item.HitTest(200.0, 200.0));

    // right
    ASSERT_FALSE(item.HitTest(300.0, 200.0));

    //left
    ASSERT_FALSE(item.HitTest(100.0, 200.0));

    //above
    ASSERT_FALSE(item.HitTest(200.0, 300.0));

    //below
    ASSERT_FALSE(item.HitTest(200.0, 100.0));
}
