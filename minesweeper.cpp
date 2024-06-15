#include "wx/wx.h"
#include <stdlib.h>
#include <vector>

#include "minesweeper.h"
#include "field.h"

#include "red.xpm"
#include "clock.xpm"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_CLOSE(MainFrame::OnExitProgram)
    EVT_TIMER(TIMER_ID, MainFrame::OnTimer)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString &title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxMINIMIZE_BOX)
{
    SetIcon(wxIcon("mine.png",wxBITMAP_TYPE_PNG, -1,-1));
    m_timer = new wxTimer(this, TIMER_ID);
    m_timer->Start(1000);

    wxBoxSizer * topSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer * clockSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer * flagSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer * dashSizer = new wxBoxSizer(wxHORIZONTAL);
    wxGridSizer * gridSizer = new wxGridSizer(9, 9, 0, 0);

    wxBitmap clock(clock_xpm);
    wxBitmap::Rescale(clock, wxSize(24,24));
    wxStaticBitmap* staticBitmap = new wxStaticBitmap(this, wxID_STATIC,clock);
    clockText = new wxStaticText(this,wxID_ANY,wxT("00:00:00"), wxDefaultPosition,wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
    clockSizer->Add(staticBitmap, 0, wxCENTER);
    clockSizer->Add(clockText, 0, wxCENTER);

    wxBitmap flag("red-flag.png", wxBITMAP_TYPE_PNG);
    wxBitmap::Rescale(flag, wxSize(24,24));
    wxStaticBitmap* flagBitmap = new wxStaticBitmap(this, wxID_STATIC,flag);
    flagText = new wxStaticText(this,wxID_ANY,wxT("0"), wxDefaultPosition,wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
    flagSizer->Add(flagBitmap, 0, wxCENTER);
    flagSizer->Add(flagText, 0, wxCENTER);

    dashSizer->Add(clockSizer, 0, wxALIGN_CENTER | wxALL);
    dashSizer->Add(flagSizer, 0, wxALIGN_CENTER | wxALL);
    srand((unsigned)time(NULL));

    int id = 0;

    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            matrix[x][y] = new Field(this, x, y, FIELD_EMPTY, id);
            if (rand() / (float)RAND_MAX < PROB && minesLoci.size() < 10)
            {
                matrix[x][y]->SetType(FIELD_MINE);
                minesLoci.push_back((x * 9) + y);
            }
            gridSizer->Add(matrix[x][y]);
            id++;
        }
    }

    topSizer->Add(dashSizer, 0, wxALIGN_CENTER | wxALL, 4);
    topSizer->Add(gridSizer, 0, wxALIGN_CENTER);

    SetSizer(topSizer);
    topSizer->Fit(this);
    topSizer->SetSizeHints(this);

    Centre(wxBOTH);
}

MainFrame::~MainFrame()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            delete matrix[i][j]->GetButton();
            delete matrix[i][j];
        }
    Destroy();
}

void MainFrame::OnExitProgram(wxCloseEvent &event)
{
    Destroy();
}

bool MainFrame::IsFieldValid(int x, int y)
{
    return ((x >= 0) && (x <= 8) && (y >= 0) && (y <= 8));
}

void MainFrame::UnCover(int x, int y)
{
    int countMines = 0;
    wxStack<Field *> lh;

    if (IsFieldValid(x - 1, y))
    {
        if (matrix[x - 1][y]->GetType() == FIELD_MINE)
            countMines++;
        else
            lh.push(matrix[x - 1][y]);
    }

    if (IsFieldValid(x - 1, y + 1))
    {
        if (matrix[x - 1][y + 1]->GetType() == FIELD_MINE)
            countMines++;
        else
            lh.push(matrix[x - 1][y + 1]);
    }
    if (IsFieldValid(x, y + 1))
    {
        if (matrix[x][y + 1]->GetType() == FIELD_MINE)
            countMines++;
        else
            lh.push(matrix[x][y + 1]);
    }
    if (IsFieldValid(x + 1, y + 1))
    {
        if (matrix[x + 1][y + 1]->GetType() == FIELD_MINE)
            countMines++;
        else
            lh.push(matrix[x + 1][y + 1]);
    }
    if (IsFieldValid(x + 1, y))
    {
        if (matrix[x + 1][y]->GetType() == FIELD_MINE)
            countMines++;
        else
            lh.push(matrix[x + 1][y]);
    }
    if (IsFieldValid(x + 1, y - 1))
    {
        if (matrix[x + 1][y - 1]->GetType() == FIELD_MINE)
            countMines++;
        else
            lh.push(matrix[x + 1][y - 1]);
    }
    if (IsFieldValid(x, y - 1))
    {
        if (matrix[x][y - 1]->GetType() == FIELD_MINE)
            countMines++;
        else
            lh.push(matrix[x][y - 1]);
    }
    if (IsFieldValid(x - 1, y - 1))
    {
        if (matrix[x - 1][y - 1]->GetType() == FIELD_MINE)
            countMines++;
        else
            lh.push(matrix[x - 1][y - 1]);
    }

    wxAnyButton * button = matrix[x][y]->GetButton();
    button->SetFont(wxFont(13, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false));

    if(countMines>0)button->SetLabel(wxString::Format("%d", countMines));
    Field* field = matrix[x][y];
    if(countMines == 0)
        field->SetBackgroundColour(wxColor(254,254,254));

    visited[matrix[x][y]->GetID()] = true;

    while (lh.size() > 0 && countMines == 0)
    {
        if (!instack[lh.top()->GetID()])
        {
            st.push(lh.top());
            instack[lh.top()->GetID()] = true;
        }
        lh.pop();
    }
    if (st.empty())
    {
        while (lh.size() > 0)
            lh.pop();
        return;
    }
    Field *top = st.top();
    st.pop();

    UnCover(top->GetX(), top->GetY());
}

void MainFrame::Reveal()
{
    size_t width = 9, numberOfFields = 81;
    for(size_t i = 0; i < minesLoci.size(); i++)
    {
        int index = minesLoci[i];
        wxAnyButton * button = matrix[index / width][index %  width]->GetButton();
        button->SetForegroundColour(wxColor(255,0,0));
        wxBitmap mine("logo.png",wxBITMAP_TYPE_PNG);
        button->SetBitmap(mine, wxLEFT);
    }

    for(size_t idx = 0; idx < numberOfFields; idx++)
    {
        dynamic_cast<wxWindow *>(matrix[idx / numberOfFields][idx %  numberOfFields])->Disable();
    }
}

wxString MainFrame::FormatClock()
{
    int h, m, s, t = interval / 1000;
    h = t / 3600;
    t = t % 3600;
    wxString hh = h < 10 ? wxString::Format("0%d", h) : wxString::Format("%d", h);

    m = t / 60;
    t = t % 60;
    wxString mm = m < 10 ? wxString::Format("0%d", m) : wxString::Format("%d", m);

    s = t;
    wxString ss = s < 10 ? wxString::Format("0%d", s) : wxString::Format("%d", s);
    wxString period = hh + ":" + mm + ":" + ss;

    return (period);
}
void MainFrame::OnTimer(wxTimerEvent& event)
{
    interval += event.GetInterval();
    clockText->SetLabel(FormatClock());
}

void MainFrame::StopTimer()
{
    m_timer->Stop();
}
wxDECLARE_APP(Minesweeper);
wxIMPLEMENT_APP(Minesweeper);

bool Minesweeper::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    MainFrame *frame = new MainFrame(_("Minesweeper"));
    frame->Show();

    return true;
}
