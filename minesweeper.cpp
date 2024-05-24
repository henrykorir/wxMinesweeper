#include "wx/wx.h"
#include <stdlib.h>

#include "minesweeper.h"
#include "field.h"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_CLOSE(MainFrame::OnExitProgram)
wxEND_EVENT_TABLE()


MainFrame::MainFrame(const wxString& title)
    : wxFrame(NULL,wxID_ANY, title,wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE | wxMINIMIZE_BOX)
{
    gridSizer = new wxGridSizer(9,9,0,0);

    int id = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            matrix[i][j] =  new Field(this, i,j, FIELD_EMPTY,id);
            if (rand()/(float)RAND_MAX < PROB)
                matrix[i][j]->SetType(FIELD_MINE);
            gridSizer->Add(matrix[i][j]);
            id++;
        }
    }

    gridSizer->Fit(this);
    gridSizer->SetSizeHints(this);

    SetSizer(gridSizer);

    Centre(wxBOTH);
}

MainFrame::~MainFrame()
{
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
        {
            delete matrix[i][j]->GetButton();
            delete matrix[i][j];
        }
    Destroy();
}

void MainFrame::OnExitProgram(wxCloseEvent& event)
{
    Destroy();
}

bool MainFrame::isFieldValid(int x, int y)
{
    return ((x >= 0) && (x <= 8) && (y >= 0) && (y <= 8));
}

void MainFrame::UnCover(int x, int y)
{
    int countMines = 0;

    if(isFieldValid(x-1, y))
    {
        if (matrix[x-1][y]->GetType() == FIELD_MINE) countMines++;
        else if(!instack[matrix[x-1][y]->GetID()])
        {
            st.push(matrix[x-1][y]);
            instack[matrix[x-1][y]->GetID()] = true;
        }
    }

    if(isFieldValid(x-1, y+1))
    {
        if (matrix[x-1][y+1]->GetType() == FIELD_MINE) countMines++;
        else if(!instack[matrix[x-1][y+1]->GetID()])
        {
            st.push(matrix[x-1][y+1]);
            instack[matrix[x-1][y+1]->GetID()] = true;
        }
    }
    if(isFieldValid(x, y+1))
    {
        if (matrix[x][y+1]->GetType() == FIELD_MINE) countMines++;
        else if(!instack[matrix[x][y+1]->GetID()])
        {
            st.push(matrix[x][y+1]);
            instack[matrix[x][y+1]->GetID()] = true;
        }
    }
    if(isFieldValid(x+1, y+1))
    {
        if (matrix[x+1][y+1]->GetType() == FIELD_MINE) countMines++;
        else if(!instack[matrix[x+1][y+1]->GetID()])
        {
            st.push(matrix[x+1][y+1]);
            instack[matrix[x+1][y+1]->GetID()] = true;
        }
    }
    if(isFieldValid(x+1, y))
    {
        if (matrix[x+1][y]->GetType() == FIELD_MINE) countMines++;
        else if(!instack[matrix[x+1][y]->GetID()])
        {
            st.push(matrix[x+1][y]);
            instack[matrix[x+1][y]->GetID()] = true;
        }
    }
    if(isFieldValid(x+1, y-1))
    {
        if (matrix[x+1][y-1]->GetType() == FIELD_MINE) countMines++;
        else if(!instack[matrix[x+1][y-1]->GetID()])
        {
            st.push(matrix[x+1][y-1]);
            instack[matrix[x+1][y-1]->GetID()] = true;
        }
    }
    if(isFieldValid(x, y-1))
    {
        if (matrix[x][y-1]->GetType() == FIELD_MINE) countMines++;
        else if(!instack[matrix[x][y-1]->GetID()])
        {
            st.push(matrix[x][y-1]);
            instack[matrix[x][y-1]->GetID()] = true;
        }
    }
    if(isFieldValid(x-1, y-1))
    {
        if (matrix[x-1][y-1]->GetType() == FIELD_MINE) countMines++;
        else if(!instack[matrix[x-1][y-1]->GetID()])
        {
            st.push(matrix[x-1][y-1]);
            instack[matrix[x-1][y-1]->GetID()] = true;
        }
    }

    matrix[x][y]->GetButton()->SetLabel(wxString::Format("%d",countMines));
    visited[matrix[x][y]->GetID()] = true;

    if(st.empty()) return;
    Field * top = st.top();
    st.pop();

    UnCover(top->GetX(), top->GetY());

}

wxDECLARE_APP(Minesweeper);
wxIMPLEMENT_APP(Minesweeper);

bool Minesweeper::OnInit()
{
    srand((unsigned) time(NULL));

    if (!wxApp::OnInit())
        return false;

    MainFrame * frame = new MainFrame(_("Minesweeper"));
    frame->Show();

    return true;
}
