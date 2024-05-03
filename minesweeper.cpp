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
    void OnExitProgram(wxCloseEvent&);
private:
    wxButton * matrix[81];
    wxGridSizer * gridSizer;
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_CLOSE(MainFrame::OnExitProgram)
wxEND_EVENT_TABLE()


MainFrame::MainFrame(const wxString& title)
    : wxFrame(NULL,wxID_ANY, title,wxDefaultPosition,wxDefaultSize,wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    gridSizer = new wxGridSizer(9,9,0,0);

    for (int i = 0; i < 81; i++)
    {
        matrix[i] = new wxButton(this, wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(70,70));
        gridSizer->Add(matrix[i]);
    }

    gridSizer->Fit(this);
    gridSizer->SetSizeHints(this);


    this->Centre();

    this->SetSizer(gridSizer);
}
void MainFrame::OnExitProgram(wxCloseEvent& event)
{
    if (wxMessageBox("Are you sure?") == wxOK){
        Destroy();
    }
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
