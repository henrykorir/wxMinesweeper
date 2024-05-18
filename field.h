#ifndef __FIELD_H__
#define __FIELD_H__

#include "wx/wx.h"

class Field : public wxPanel
{
public:
    Field(wxFrame *, int, int, int, int);
    void SetX(int x);
    int GetX();
    void SetY(int y);
    int GetY();
    void SetType(int type);
    int GetType();
    void SetID(int);
    int GetID();
    wxButton * GetButton();

private:
    int x;
    int y;
    int type;
    int id;
    wxButton * button;
    void OnButtonClick(wxCommandEvent& );
    wxDECLARE_EVENT_TABLE();
};

#endif
