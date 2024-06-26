#include "wx/wx.h"
#include "field.h"
#include "minesweeper.h"

Field::Field(wxFrame * parent, int x, int y, int type, int id)
    : wxPanel(parent, wxID_ANY,wxDefaultPosition,wxDefaultSize,wxBORDER_SIMPLE)
{
    SetBackgroundColour(wxColor(211, 211, 211));
    this->x = x;
    this->y = y;
    this->type = type;
    this->id = id;
    this->button = new wxButton(this, wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(70,70), wxBORDER_NONE);
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
void Field::SetID(int id)
{
    this->id = id;
}
int Field::GetID()
{
    return this->id;
}
wxAnyButton * Field::GetButton()
{
    return button;
}

void Field::OnButtonClick(wxCommandEvent& event)
{
    MainFrame * parent = dynamic_cast<MainFrame*>(GetParent());
    if(type == FIELD_MINE)
    {
        parent->StopTimer();
        parent->Reveal();
    }
    else
        parent->UnCover(x,y);
}

void Field::OnMouseRightClick(wxMouseEvent& event)
{
    this->SetBackgroundColour(wxColor(128, 128, 128));
    wxMessageBox("HEYYEY");
}

wxBEGIN_EVENT_TABLE(Field, wxPanel)
    EVT_BUTTON(wxID_ANY, Field::OnButtonClick)
    EVT_RIGHT_DOWN(Field::OnMouseRightClick)
wxEND_EVENT_TABLE()
