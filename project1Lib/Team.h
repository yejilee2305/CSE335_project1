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
 * @class Team
 * @brief A class responsible for managing and triggering random sound effects.
 *
 * The Team class maintains a list of sound effects (stored as strings) and includes
 * a method to return a random sound effect from this list.
 */
class Team
{
private:
    std::vector<std::string> mNoises; ///< List of onomatopoeic sounds to trigger.

public:
    /**
 * @brief Default constructor that initializes the list of sound effects.
 */
    Team();
    /**
     * @brief Triggers a random sound effect.
     *
     * @return A randomly selected sound effect as a std::string. Returns an
     * empty string if no sound effects are available.
     */
    std::string TriggerNoise();
};


#endif //TEAM_H
