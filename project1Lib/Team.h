/**
 * @file Team.h
 * @author Yeji Lee
 *
 *
 */

#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <vector>
#include <wx/wx.h>

/**
 * class for the team feature
 */
class Team
{
private:
    std::vector<std::string> mNoises;

public:
    Team();

    std::string TriggerNoise();
};


#endif //TEAM_H
