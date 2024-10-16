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

using namespace std;

/**
 * Constructor
 */
GameView::GameView()
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

    // Allows ability to paint on background
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Binds paint function with event
    Bind(wxEVT_PAINT, &GameView::OnPaint, this);

    // mouse events
    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &GameView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &GameView::OnMouseMove, this);
    mainFrame->Bind(wxEVT_MENU, &GameView::OnAddORGate, this);
    mainFrame->Bind(wxEVT_MENU, &GameView::OnAddANDGate, this);
}

/**
 * Handles the paint event for the game view.
 *
 * This function is responsible for drawing the game scene, including graphics, text, and notices.
 *
 * @param event The paint event.
 */
void GameView::OnPaint(wxPaintEvent& event)
{
    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Clear the image to black
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto gc =
        std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Tell the game class to draw
    wxRect rect = GetRect();
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());
}

/**
 * handles the left mosue button down event
 * @param event
 */
void GameView::OnLeftDown(wxMouseEvent& event)
{
    mGrabbedItem = mGame.HitTest(event.GetX(), event.GetY());

    if (mGrabbedItem != nullptr)
    {
        Refresh();
    }
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void GameView::OnLeftUp(wxMouseEvent& event)
{
    OnMouseMove(event);
}

/**
 * implemented from "aquarium" steps
 * Handles left mouse button down event
 * @param event
 */
void GameView::OnMouseMove(wxMouseEvent& event)
{
    // See if an item is currently being moved by the mouse
    if (mGrabbedItem != nullptr)
    {
        // If an item is being moved, we only continue to
        // move it while the left button is down.
        if (event.LeftIsDown())
        {
            mGrabbedItem->SetLocation(event.GetX(), event.GetY());
        }
        else
        {
            // When the left button is released, we release the
            // item.
            mGrabbedItem = nullptr;
        }

        // Force the screen to redraw
        Refresh();
    }
}

/**
 * Handle level choosing event
 * @param event
 */
void GameView::OnLevelOption(wxCommandEvent& event)
{
    wxString filename;
    int levelNumber = 0;

    switch(event.GetId())
    {
    case IDM_LEVEL0:filename = L"resources/levels/level0.xml";
        levelNumber = 0;
        break;
    case IDM_LEVEL1:filename = L"resources/levels/level1.xml";
        levelNumber = 1;
        break;
    case IDM_LEVEL2:filename = L"resources/levels/level2.xml";
        levelNumber = 2;
        break;
    case IDM_LEVEL3:filename = L"resources/levels/level3.xml";
        levelNumber = 3;
        break;
    case IDM_LEVEL4:filename = L"resources/levels/level4.xml";
        levelNumber = 4;
        break;
    case IDM_LEVEL5:filename = L"resources/levels/level5.xml";
        levelNumber = 5;
        break;
    case IDM_LEVEL6:filename = L"resources/levels/level6.xml";
        levelNumber = 6;
        break;
    case IDM_LEVEL7:filename = L"resources/levels/level7.xml";
        levelNumber = 7;
        break;
    case IDM_LEVEL8:filename = L"resources/levels/level8.xml";
        levelNumber = 8;
        break;
    }

    //mGame = Game();
    //mGame.Load(filename);
    //Refresh();
}

void GameView::AddGate(std::shared_ptr<Gate> gate)
{
    // Assuming you have access to the game object through mGame
    mGame.AddGate(gate);

    // Redraw the screen to show the added gate
    Refresh();
}
void GameView::OnAddORGate(wxCommandEvent& event)
{
    auto orGate = std::make_shared<ORGate>();
    orGate->SetPosition(100, 100); // Set initial position
    mGame.AddGate(orGate); // Add the gate to the view
    std::cout << "yay" << std::endl;
}

auto GameView::OnAddANDGate(wxCommandEvent& event) -> void
{
    auto andGate = std::make_shared<ANDGate>();
    andGate->SetPosition(200, 100); // Set initial position
    mGame.AddGate(andGate); // Add the gate to the view
}