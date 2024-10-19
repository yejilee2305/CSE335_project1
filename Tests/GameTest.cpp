/**
 * @file GameTest.cpp
 * @author Nicolas Roberts
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>

using namespace std;

TEST(GameTest, Construct) {
    Game game;
}

TEST(GameTest, Load) {
    Game game;

    wxString level = L"levels/level0.xml";

    game.Load(level);

    ASSERT_EQ(game.GetItemSize(), 2) << L"Scoreboard and Conveyor are loaded";
}
