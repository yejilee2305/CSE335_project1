/**
 * @file GameView.cpp
 * @author Nicolas Roberts
 */

#include "pch.h"
#include "GameView.h"
#include <wx/stdpaths.h>
#include <wx/dcbuffer.h>
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
    case IDM_LEVEL0:filename = L"levels/level0.xml";
        levelNumber = 0;
        break;
    case IDM_LEVEL1:filename = L"levels/level1.xml";
        levelNumber = 1;
        break;
    case IDM_LEVEL2:filename = L"levels/level2.xml";
        levelNumber = 2;
        break;
    case IDM_LEVEL3:filename = L"levels/level3.xml";
        levelNumber = 3;
        break;
    }
}
void GameView::AddGate(std::shared_ptr<Gate> gate) {
    mGates.push_back(gate); // Add the new gate to the list
    Refresh(); // Refresh the view to trigger a redraw
}
void GameView::OnDraw(wxGraphicsContext* gc, int width, int height) {
    for (const auto& gate : mGates) {
        gate->Draw(gc); // Call the draw method for each gate
    }
}