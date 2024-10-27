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
#include "Gate.h"
#include "Scoreboard.h"
#include "Beam.h"
#include "Product.h"

using namespace std;

/**
 * Constructor for GameView.
 */
GameView::GameView() : mCurrentLevel(0)
{
} // Initialize level to 0

void GameView::OnTimer(wxTimerEvent& event)
{
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    mGame.Update(elapsed);
    Refresh();
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

    Bind(wxEVT_TIMER, &GameView::OnTimer, this);
    mTimer.SetOwner(this);
    mTimer.Start(60);
    mStopWatch.Start();
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
        mCurrentLevel = 0; // Update the current level
        break;
    case IDM_LEVEL1:
        filename = L"resources/levels/level1.xml";
        mCurrentLevel = 1; // Update the current level
        break;
    case IDM_LEVEL2:
        filename = L"resources/levels/level2.xml";
        mCurrentLevel = 2; // Update the current level
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
    // for (const auto& wire : mGame.GetWires())
    // {
    //     wire->Draw(gc.get(), mGame.GetShowControlPoints());
    // }
    if (mSelectedOutputPin != nullptr && mSelectedInputPin != nullptr)
    {
        mDraggingWire = std::make_shared<Wire>(mSelectedOutputPin, mSelectedInputPin);
        mDraggingWire->Draw(gc.get(), mGame.GetShowControlPoints());
    }
    Refresh();

    // // Create a temporary scoreboard for this draw cycle
    // auto scoreboard = std::make_shared<Scoreboard>(700, 40, 10, -5);
    // scoreboard->SetInstructions(
    //     "Make Sparty kick all product from the conveyor\n that are not Izzo or Smith.");
    //
    // // Draw the scoreboard within the graphics context
    // scoreboard->Draw(gc.get());
}

void GameView::ToggleControlPoints()
{
    mGame.SetShowControlPoints(!mGame.GetShowControlPoints());
    Refresh();
}

/**
 * Handles the left mouse button down event.
 * Used to detect and manipulate game objects with the mouse.
 * @param event The mouse event
 */
void GameView::OnLeftDown(wxMouseEvent& event)
{
    auto mouseX = event.GetX();
    auto mouseY = event.GetY();

    mSelectedOutputPin = nullptr; // Reset selection
    mSelectedInputPin = nullptr;

    auto game = &mGame;
    auto scale = game->GetScale();
    auto xOffset = game->GetXOffset();
    auto yOffset = game->GetYOffset();

    double gameX = (mouseX - xOffset) / scale;
    double gameY = (mouseY - yOffset) / scale;


    for (const auto& gate : mGame.GetGates())
    {
        for (auto& outputPin : gate->GetOutputPins())
        {
            if (outputPin.HitTest(gameX, gameY))
            {
                mSelectedOutputPin = &outputPin; // Select the output pin
                std::cout << "Output pin clicked!" << std::endl;
            }
        }
        for (auto& inputPin : gate->GetInputPins())
        {
            if (inputPin.HitTest(gameX, gameY))
            {
                mSelectedInputPin = &inputPin; // Select the input pin
                return;
            }
        }
        if (gate->HitTest(gameX, gameY))
        {
            mGrabbedGate = gate; // Select the gate
        }
    }
}

/**
 * Handles the left mouse button up event.
 * @param event The mouse event
 */
void GameView::OnLeftUp(wxMouseEvent& event)
{
    auto mouseX = event.GetX();
    auto mouseY = event.GetY();

    auto game = &mGame;
    auto scale = game->GetScale();
    auto xOffset = game->GetXOffset();
    auto yOffset = game->GetYOffset();

    double gameX = (mouseX - xOffset) / scale;
    double gameY = (mouseY - yOffset) / scale;


    if (mSelectedOutputPin != nullptr)
    {
        for (const auto& gate : mGame.GetGates())
        {
            for (auto& inputPin : gate->GetInputPins())
            {
                if (inputPin.HitTest(gameX, gameY))
                {
                    mGame.AddWire(mSelectedOutputPin, &inputPin); // Connect the output pin to the input pin
                    mSelectedOutputPin = nullptr;
                    Refresh();
                }
            }
        }
    }
    mSelectedOutputPin = nullptr;
    mGrabbedGate = nullptr;
    Refresh();
}


/**
 * Handles mouse move events.
 * Allows dragging game objects with the mouse.
 * @param event The mouse event
 */
void GameView::OnMouseMove(wxMouseEvent& event)
{
    auto x = event.GetX();
    auto y = event.GetY();

    auto game = &mGame;
    auto scale = game->GetScale();
    auto xOffset = game->GetXOffset();
    auto yOffset = game->GetYOffset();

    double gameX = (x - xOffset) / scale;
    double gameY = (y - yOffset) / scale;


    if (mGrabbedGate != nullptr && event.Dragging() && event.LeftIsDown())
    {
        mGrabbedGate->SetPosition(gameX, gameY);
        Refresh();
    }

    if (mSelectedOutputPin != nullptr && event.Dragging() && event.LeftIsDown())
    {
        // Call OnDrag to update the output pin's position
        mSelectedOutputPin->OnDrag(gameX, gameY);
        Refresh();
    }
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
 * Handles the addition of an SR flip gate.
 * @param event The event triggered by the menu selection
 */
auto GameView::OnAddSRFLipFlopGate(wxCommandEvent& event) -> void
{
    // Create an SR gate and set its initial position
    auto srFlipFlop = std::make_shared<SRFlipFlopGate>();
    srFlipFlop->SetPosition(400, 100);

    // Add the SR gate to the game
    mGame.AddGate(srFlipFlop);
}

/**
 * Handles the addition of an SR flip gate.
 * @param event The event triggered by the menu selection
 */
auto GameView::OnAddDFLipFlopGate(wxCommandEvent& event) -> void
{
    // Create an D gate and set its initial position
    auto dFlipFlop = std::make_shared<DFlipFlopGate>();
    dFlipFlop->SetPosition(400, 100);

    // Add the D gate to the game
    mGame.AddGate(dFlipFlop);
}
