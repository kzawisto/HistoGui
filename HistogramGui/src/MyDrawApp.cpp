/**
 @file      MyDrawApp.cpp
 @brief   Implementation for Application Class
 @author    kzawisto
 @created  2015-10-29
 * Copyright: kzawisto ()
 * License:
 **************************************************************/

#include "MyDrawApp.h"
#include "wx/wx.h"
#include "wx/sizer.h"

//(*AppHeaders
#include "MyDrawMain.h"
#include <wx/image.h>

#include <HistoCreator.h>
//*)

IMPLEMENT_APP(MyHistoApp)


bool MyHistoApp::OnInit()
{
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    frame = new wxFrame((wxFrame *)NULL, -1,  wxT("Hello wxDC"), wxPoint(50,50), wxSize(800,600));

    drawPane = new HistoDrawPane( (wxFrame*) frame );

    sizer->Add(drawPane, 1, wxEXPAND);

    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);

    frame->Show();
    return true;
}
