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

void Team::TriggerNoise()
{
 int randomIndex = rand() % mNoises.size();
 std::string noise = mNoises[randomIndex];

 wxLogMessage(wxString::FromAscii(noise.c_str()));
}
