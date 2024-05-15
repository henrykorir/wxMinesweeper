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
            matrix[i][j] =  new Field(this, i,j, FIELD_EMPTY);
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

void MainFrame::UnCoverNeighbour(int x, int y)
{
    matrix[x-1][y]->GetButton()->SetLabel(wxString::Format(wxT("A")));
    matrix[x-1][y+1]->GetButton()->SetLabel(wxString::Format(wxT("B")));
    matrix[x][y+1]->GetButton()->SetLabel(wxString::Format(wxT("C")));
    matrix[x+1][y+1]->GetButton()->SetLabel(wxString::Format(wxT("D")));
    matrix[x+1][y]->GetButton()->SetLabel(wxString::Format(wxT("E")));
    matrix[x+1][y-1]->GetButton()->SetLabel(wxString::Format(wxT("F")));
    matrix[x][y-1]->GetButton()->SetLabel(wxString::Format(wxT("G")));
    matrix[x-1][y-1]->GetButton()->SetLabel(wxString::Format(wxT("H")));
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
