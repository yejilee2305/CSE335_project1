/**
 * @file MainFrame.h
 * @author Zhi Lin
 *
 *
 */

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>

class GameView;

/**
 * @class MainFrame
 * @brief The MainFrame class represents the main application window.
 *
 * MainFrame initializes the main window, handles menu commands, manages game
 * elements (such as adding gates), and manages the display of control points.
 */
class MainFrame : public wxFrame
{
private:
    GameView *mGameView; ///< Pointer to the game view instance
    wxMenuItem* mControlPointsMenuItem; ///< Menu item for toggling control points

public:
    /**
 * @brief Initializes the main frame and sets up the user interface.
 *
 * Sets up the frame size, menus, and connects event handlers.
 */
    void Initialize();
    /**
 * @brief Event handler for exiting the application.
 *
 * @param event wxCommandEvent object containing event details.
 */
    void OnExit(wxCommandEvent& event);
    /**
 * @brief Event handler for displaying the "About" dialog.
 *
 * @param event wxCommandEvent object containing event details.
 */
    void OnAbout(wxCommandEvent& event);
    /**
 * @brief Event handler for handling the frame's close event.
 *
 * Ensures that resources are properly cleaned up and prompts the user if necessary.
 *
 * @param event wxCloseEvent object containing event details.
 */
    void OnClose(wxCloseEvent& event);
    /**
 * @brief Adds an OR gate to the game view.
 *
 * @param event wxCommandEvent object containing event details.
 */
    void OnAddORGate(wxCommandEvent& event);
   /**
 * @brief Adds an AND gate to the game view.
 *
 * @param event wxCommandEvent object containing event details.
 */
    void OnAddANDGate(wxCommandEvent& event);
   /**
 * @brief Adds a NOT gate to the game view.
 *
 * @param event wxCommandEvent object containing event details.
 */
    void OnAddNOTGate(wxCommandEvent& event);
   /**
 * @brief Adds an SR Flip-Flop gate to the game view.
 *
 * @param event wxCommandEvent object containing event details.
 */
    void OnAddSRFlipFlopGate(wxCommandEvent& event);
   /**
 * @brief Adds a D Flip-Flop gate to the game view.
 *
 * @param event wxCommandEvent object containing event details.
 */
    void OnAddDFlipFlopGate(wxCommandEvent& event);
   /**
 * @brief Toggles the display of control points in the game view.
 *
 * @param event wxCommandEvent object containing event details.
 */
    void OnToggleControlPoints(wxCommandEvent& event);
   /**
    * @enum GateIDs
    * @brief Enumerates custom IDs for gate menu items.
    */
    enum
    {
        ID_ORGate = 1001, ///< ID for OR gate menu item
        ID_ANDGate = 1002, ///< ID for AND gate menu item
        ID_NOTGate = 1003 ///< ID for NOT gate menu item
    };
};


#endif //MAINFRAME_H
