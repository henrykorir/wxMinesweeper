#include "wx/wx.h"

class Minesweeper : public wxApp
{
public:
    virtual bool OnInit();
};

class Cell;

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString&);
    ~MainFrame();
    void OnExitProgram(wxCloseEvent&);
    void OnButtonClick(wxCommandEvent&);
    void OnMouseEvent(wxMouseEvent&);

private:
    Cell * matrix[9][9];
    wxGridSizer * gridSizer;
    wxDECLARE_EVENT_TABLE();
};

class Cell
{
public:
    Cell();
    Cell(int x, int y, wxWindow *);
    void SetX(int x);
    int GetX();
    void SetY(int y);
    int GetY();
    wxButton * GetButton();
private:
    int x;
    int y;
    wxButton * button;

};

Cell::Cell()
{
    x = 0;
    y = 0;
}

Cell::Cell(int x, int y, wxWindow * parrent)
{
    this->x = x;
    this->y = y;
    this->button = new wxButton(parrent, wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(70,70), wxBU_EXACTFIT);
}

void Cell::SetX(int x)
{
    this->x = x;
}

int Cell::GetX()
{
    return x;
}

void Cell::SetY(int y)
{
    this->y = y;
}

int Cell::GetY()
{
    return y;
}

wxButton * Cell::GetButton()
{
    return button;
}

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
            matrix[i][j] = new Cell(i,j, this);
            gridSizer->Add(matrix[i][j]->GetButton());
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
