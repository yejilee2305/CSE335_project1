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

class Team {
private:
 std::vector <std::string> mNoises;

public:
 Team();

 void TriggerNoise();

};



#endif //TEAM_H
