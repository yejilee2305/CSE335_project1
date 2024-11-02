/**
 * @file Team.cpp
 * @author Yeji Lee
 */

#include "pch.h"
#include "Team.h"
/**
 * @brief Constructs a Team object and initializes sound effects.
 *
 * The constructor sets up a list of onomatopoeic sounds that can be randomly triggered
 * using the TriggerNoise method.
 */
Team::Team()
{
    mNoises = {"Pow!", "Bam!", "Wham!", "Boom!", "Zap!"};
}
/**
 * @brief Triggers a random sound effect from the team's noise set.
 *
 * @return A randomly selected sound effect as a std::string. Returns an empty string
 * if no sound effects are available.
 */
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
