#ifndef __MINESWEEPER_H__
#define __MINESWEEPER_H__

#include "wx/wx.h"
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
    void UnCoverNeighbour(int, int);

private:
    Field * matrix[9][9];
    wxGridSizer * gridSizer;
    bool isFieldValid(int,int);
    void labelField(int, int, const wxString&);
    wxDECLARE_EVENT_TABLE();
};

enum
{
    FIELD_EMPTY = 0, FIELD_MINE
};

#endif
