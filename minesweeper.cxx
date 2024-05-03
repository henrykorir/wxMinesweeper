#include "wx/wx.h"

class Minesweeper : public wxApp
{
public:
    virtual bool OnInit();
};

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString&);
private:
    wxButton * matrix[81];
    wxGridSizer * gridSizer;
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
wxEND_EVENT_TABLE()
MainFrame::MainFrame(const wxString& title)
    : wxFrame(NULL,wxID_ANY, title)
{
    gridSizer = new wxGridSizer(9,9,0,0);

    for (int i = 0; i < 81; i++)
    {
        matrix[i] = new wxButton(this, wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(70,70));
        gridSizer->Add(matrix[i]);
    }

    gridSizer->Fit(this);
    gridSizer->SetSizeHints(this);

    this->Center();

    this->SetSizer(gridSizer);
}

wxDECLARE_APP(Minesweeper);
wxIMPLEMENT_APP(Minesweeper);

bool Minesweeper::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    MainFrame * frame = new MainFrame(_("Minesweeper"));
    frame->Show();

    return true;
}
