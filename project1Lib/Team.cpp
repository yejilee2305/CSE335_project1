/**
 * @file Team.cpp
 * @author Yeji Lee
 */

#include "pch.h"
#include "Team.h"

Team::Team()
{
    mNoises = {"Pow!", "Bam!", "Wham!", "Boom!", "Zap!"};
}

std::string Team::TriggerNoise()
{
    if (mNoises.empty())
    {
        return "";
    }

    int randomIndex = rand() % mNoises.size();
    std::string noise = mNoises[randomIndex];


    return noise;
}
