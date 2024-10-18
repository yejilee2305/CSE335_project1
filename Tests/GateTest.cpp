/**
 * @file GateTest.cpp
 * @author Praseedha Vinukonda
 */
#include <pch.h>
#include "gtest/gtest.h"
#include <Gate.h>

using namespace std;


TEST(GameTest, OrGateConstruct)
{
 ORGate orGate;
 EXPECT_EQ(orGate.ComputeOutput(), States::Unknown) << "ORGate should initialize with Unknown state inputs.";

}

TEST(GateTest, ANDGateConstruct)
{
 ANDGate andGate;

 EXPECT_EQ(andGate.ComputeOutput(), States::Unknown) << "ANDGate should initialize with Unknown state inputs.";
}

