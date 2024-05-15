#include "wx/wx.h"
#include "field.h"
#include "minesweeper.h"

Field::Field(wxFrame * parent, int x, int y, int type)
    : wxPanel(parent, wxID_ANY)
{
    this->x = x;
    this->y = y;
    this->type = type;
    this->button = new wxButton(this, wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(70,70), wxBU_EXACTFIT);
}

void Field::SetX(int x)
{
    this->x = x;
}

int Field::GetX()
{
    return x;
}

void Field::SetY(int y)
{
    this->y = y;
}

int Field::GetY()
{
    return y;
}

void Field::SetType(int type)
{
    this->type = type;
}

int Field::GetType()
{
    return type;
}
wxButton * Field::GetButton()
{
    return button;
}

void Field::OnButtonClick(wxCommandEvent& event)
{
    button->SetFont(wxFont(13, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false));
    button->SetLabel(wxString::Format(wxT("%d"),type));
    button->Enable(false);
    button->SetForegroundColour(wxColor(0,255,0));

    MainFrame * parent = dynamic_cast<MainFrame*>(GetParent());
    parent->UnCoverNeighbour(x,y);
}

wxBEGIN_EVENT_TABLE(Field, wxPanel)
    EVT_BUTTON(wxID_ANY, Field::OnButtonClick)
wxEND_EVENT_TABLE()
