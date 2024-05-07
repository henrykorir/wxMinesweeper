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
    ~MainFrame();
    void OnExitProgram(wxCloseEvent&);
    void OnButtonClick(wxCommandEvent&);

private:
    wxButton * matrix[9][9];
    wxGridSizer * gridSizer;
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_CLOSE(MainFrame::OnExitProgram)
    EVT_BUTTON(wxID_ANY, MainFrame::OnButtonClick)
wxEND_EVENT_TABLE()


MainFrame::MainFrame(const wxString& title)
    : wxFrame(NULL,wxID_ANY, title,wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE | wxMINIMIZE_BOX)
{
    gridSizer = new wxGridSizer(9,9,0,0);

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            matrix[i][j] = new wxButton(this, wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(70,70), wxBU_EXACTFIT);
            gridSizer->Add(matrix[i][j]);
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
            delete matrix[i][j];
    Destroy();
}
void MainFrame::OnExitProgram(wxCloseEvent& event)
{
    Destroy();
}

void MainFrame::OnButtonClick(wxCommandEvent& event)
{
    wxWindow * m_button = FindWindow(event.GetId());
    m_button->SetFont(wxFont(13, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false));
    m_button->SetLabel("0");
    m_button->Enable(false);
    m_button->SetForegroundColour(wxColor(0,255,0));
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
