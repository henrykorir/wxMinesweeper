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
    SetIcon(wxIcon("logo.png",wxBITMAP_TYPE_PNG , -1,-1));
    m_timer = new wxTimer(this, TIMER_ID);
    m_timer->Start(1000);

    wxBoxSizer * topSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer * dashSizer = new wxBoxSizer(wxHORIZONTAL);
    wxGridSizer * gridSizer = new wxGridSizer(9, 9, 0, 0);

    wxSize size = GetClientSize();
    topPanel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(size.GetWidth(), 50),wxBORDER_SIMPLE);
    text = new wxStaticText(topPanel,wxID_ANY,wxT("0"), wxDefaultPosition,wxDefaultSize, 0);
    wxBitmap clock(clock_xpm);
    wxBitmap::Rescale(clock, wxSize(32,32));
    wxStaticBitmap* staticBitmap = new wxStaticBitmap(topPanel, wxID_STATIC,clock);
    dashSizer->Add(topPanel);


    int id = 0;

    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            matrix[x][y] = new Field(this, x, y, FIELD_EMPTY, id);
            if (rand() / (float)RAND_MAX < PROB)
            {
                matrix[x][y]->SetType(FIELD_MINE);
                minesLoci.push_back((x * 9) + y);
            }
            gridSizer->Add(matrix[x][y]);
            id++;
        }
    }

    topSizer->Add(dashSizer);//, 0, wxALIGN_CENTER_HORIZONTAL | wxALL,4);
    topSizer->Add(gridSizer);//, 0, wxALIGN_CENTER  | wxALL, 4);
    topSizer->Fit(this);
    topSizer->SetSizeHints(this);

    SetSizer(topSizer);

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
    button->SetLabel(wxString::Format("%d", countMines));
    //button->Enable(false);
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
    int width = 9;
    for(long unsigned int i = 0; i < minesLoci.size(); i++)
    {
        int index = minesLoci[i];
        wxAnyButton * button = matrix[index / width][index %  width]->GetButton();
        button->SetForegroundColour(wxColor(255,0,0));
        button->SetLabel("M");
        //wxBitmap mine("logo.png",wxBITMAP_TYPE_PNG);
        //button->SetBitmap(mine, wxLEFT);
        //button->Disable();
    }
    SetWindowStyle(wxWS_EX_BLOCK_EVENTS);
}

void MainFrame::OnTimer(wxTimerEvent& event)
{
    interval += event.GetInterval();
    wxString s = wxString::Format("%d",interval/1000);
    text->SetLabel(s);
}

void MainFrame::StopTimer()
{
    m_timer->Stop();
}
wxDECLARE_APP(Minesweeper);
wxIMPLEMENT_APP(Minesweeper);

bool Minesweeper::OnInit()
{
    srand((unsigned)time(NULL));

    if (!wxApp::OnInit())
        return false;

    MainFrame *frame = new MainFrame(_("Minesweeper"));
    frame->Show();

    return true;
}
