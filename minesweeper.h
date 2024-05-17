#ifndef __MINESWEEPER_H__
#define __MINESWEEPER_H__

#include "wx/wx.h"
#include "wx/stack.h"
#include "field.h"

#define PROB 0.2

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
    void UnCover(int, int);

private:
    Field * matrix[9][9];
    wxStack<Field*> st;
    bool visited[81] {false};
    wxGridSizer * gridSizer;
    bool isFieldValid(int,int);
    wxDECLARE_EVENT_TABLE();
};

enum
{
    FIELD_EMPTY = 0, FIELD_MINE
};

#endif
