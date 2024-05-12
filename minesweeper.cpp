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
