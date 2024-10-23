/**
 * @file GameView.cpp
 * @author Nicolas Roberts
 */


#include "pch.h"
#include "GameView.h"
#include <wx/stdpaths.h>
#include <wx/dcbuffer.h>
#include "MainFrame.h"
#include "ids.h"
#include "Scoreboard.h"

using namespace std;

/**
 * Constructor for GameView.
 */
GameView::GameView() : mCurrentLevel(0)  // Initialize level to 0
{
}

/**
 * Initialize the game view class.
 * @param mainFrame The parent window for this class
 */
void GameView::Initialize(wxFrame* mainFrame)
{
    Create(mainFrame, wxID_ANY,
           wxDefaultPosition, wxDefaultSize,
           wxFULL_REPAINT_ON_RESIZE);

    // Allows for background repainting
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Bind the paint event to the OnPaint method
    Bind(wxEVT_PAINT, &GameView::OnPaint, this);

    // Bind menu events for all levels
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelOption, this, IDM_LEVEL0);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelOption, this, IDM_LEVEL1);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelOption, this, IDM_LEVEL2);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelOption, this, IDM_LEVEL3);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelOption, this, IDM_LEVEL4);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelOption, this, IDM_LEVEL5);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelOption, this, IDM_LEVEL6);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelOption, this, IDM_LEVEL7);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelOption, this, IDM_LEVEL8);

    // Bind mouse events
    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &GameView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &GameView::OnMouseMove, this);

    // Bind gate-adding menu events
    mainFrame->Bind(wxEVT_MENU, &GameView::OnAddORGate, this);
    mainFrame->Bind(wxEVT_MENU, &GameView::OnAddANDGate, this);

    // Load the initial level (default to mCurrentLevel)
    mGame.Load(wxString::Format("levels/level%d.xml", mCurrentLevel));

    // Request a repaint to reflect the initial game state
    Refresh();
}

/**
 * Handle level choosing event.
 * @param event The command event triggered by the menu selection
 */
void GameView::OnLevelOption(wxCommandEvent& event)
{
    wxString filename;

    // Switch based on the selected level
    switch (event.GetId())
    {
    case IDM_LEVEL0:
        filename = L"resources/levels/level0.xml";
        mCurrentLevel = 0;  // Update the current level
        break;
    case IDM_LEVEL1:
        filename = L"resources/levels/level1.xml";
        mCurrentLevel = 1;  // Update the current level
        break;
    case IDM_LEVEL2:
        filename = L"resources/levels/level2.xml";
        mCurrentLevel = 2;  // Update the current level
        break;
    // Add other cases for different levels...
    }

    // Reload the game with the selected level
    mGame = Game();
    mGame.Load(filename);

    // Request a repaint to reflect the loaded level
    Refresh();
}

/**
 * Handles the paint event for the game view.
 * This function is responsible for rendering the game scene.
 * @param event The paint event
 */
void GameView::OnPaint(wxPaintEvent& event)
{
    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Clear the display to black
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context for advanced drawing
    auto gc = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Get the dimensions of the current view
    wxRect rect = GetRect();

    // Instruct the game to draw its elements
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());

    // // Create a temporary scoreboard for this draw cycle
    // auto scoreboard = std::make_shared<Scoreboard>(700, 40, 10, -5);
    // scoreboard->SetInstructions(
    //     "Make Sparty kick all product from the conveyor\n that are not Izzo or Smith.");
    //
    // // Draw the scoreboard within the graphics context
    // scoreboard->Draw(gc.get());
}

/**
 * Handles the left mouse button down event.
 * Used to detect and manipulate game objects with the mouse.
 * @param event The mouse event
 */
void GameView::OnLeftDown(wxMouseEvent& event)
{
    // Check if the mouse clicked on a game object
    mGrabbedItem = mGame.HitTest(event.GetX(), event.GetY());

    // If an item was grabbed, request a repaint
    if (mGrabbedItem != nullptr)
    {
        Refresh();
    }
}

/**
 * Handles the left mouse button up event.
 * @param event The mouse event
 */
void GameView::OnLeftUp(wxMouseEvent& event)
{
    // Release the item if it was grabbed
    if (mGrabbedItem != nullptr)
    {
        mGrabbedItem = nullptr; // Release the item
        Refresh(); // Refresh to update the display
    }
}

/**
 * Handles mouse move events.
 * Allows dragging game objects with the mouse.
 * @param event The mouse event
 */
void GameView::OnMouseMove(wxMouseEvent& event)
{
    mGame.HandleMouseMove(event.GetX(), event.GetY(), event);
    Refresh();
}

/**
 * Adds a gate to the game.
 * @param gate The gate to add
 */
void GameView::AddGate(std::shared_ptr<Gate> gate)
{
    // Add the gate to the game
    mGame.AddGate(gate);

    // Request a repaint to show the new gate
    Refresh();
}

/**
 * Handles the addition of an OR gate.
 * @param event The event triggered by the menu selection
 */
void GameView::OnAddORGate(wxCommandEvent& event)
{
    // Create an OR gate and set its initial position
    auto orGate = std::make_shared<ORGate>();
    orGate->SetPosition(100, 100);

    // Add the OR gate to the game
    mGame.AddGate(orGate);

    // Print to console for debugging
    std::cout << "yay" << std::endl;
}

/**
 * Handles the addition of an AND gate.
 * @param event The event triggered by the menu selection
 */
auto GameView::OnAddANDGate(wxCommandEvent& event) -> void
{
    // Create an AND gate and set its initial position
    auto andGate = std::make_shared<ANDGate>();
    andGate->SetPosition(300, 100);

    // Add the AND gate to the game
    mGame.AddGate(andGate);
}

/**
 * Handles the addition of an NOT gate.
 * @param event The event triggered by the menu selection
 */
auto GameView::OnAddNOTGate(wxCommandEvent& event) -> void
{
    // Create an NOT gate and set its initial position
    auto notGate = std::make_shared<NOTGate>();
    notGate->SetPosition(400, 100);

    // Add the NOT gate to the game
    mGame.AddGate(notGate);
}

/**
 * Handles the addition of an NOT gate.
 * @param event The event triggered by the menu selection
 */
auto GameView::OnAddSRFLipFlopGate(wxCommandEvent& event) -> void
{
    // Create an NOT gate and set its initial position
    auto srFlipFlop = std::make_shared<SRFlipFlopGate>();
    srFlipFlop->SetPosition(400, 100);

    // Add the NOT gate to the game
    mGame.AddGate(srFlipFlop);
}