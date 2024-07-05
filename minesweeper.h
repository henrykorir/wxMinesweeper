#ifndef __MINESWEEPER_H__
#define __MINESWEEPER_H__

#include "wx/wx.h"
#include "wx/stack.h"
#include <vector>
#include "field.h"

#define PROB 0.2
#define TIMER_ID 1000

class Minesweeper : public wxApp
{
public:
    virtual bool OnInit();
};

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString&);
    ~MainFrame();
    void OnExitProgram(wxCloseEvent&);
    void OnMouseEvent(wxMouseEvent&);
    void OnNewGame(wxCommandEvent&);
    void OnExitGame(wxCommandEvent&);
    void UnCover(int, int);
    void Reveal();

    void OnTimer(wxTimerEvent&);
    void StopTimer();

private:
    Field * matrix[9][9];
    wxPanel * topPanel;
    int interval{0};
    std::vector<int> minesLoci;
    wxTimer * m_timer;
    wxStaticText * clockText;
    wxStaticText * flagText;
    wxStack<Field*> st;
    bool visited[81] {false};
    bool instack[81] {false};
    bool IsFieldValid(int,int);
    wxString FormatClock();
    wxDECLARE_EVENT_TABLE();
};

enum
{
    FIELD_EMPTY = 0, FIELD_MINE
};

#endif