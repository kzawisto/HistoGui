/** *************************************************************
 @file     MyDrawApp.h
 @brief   Defines wxWidgets Application class
 @author   kzawisto
 @created:   2015-10-29
 **************************************************************/

#ifndef MYDRAWAPP_H
#define MYDRAWAPP_H

#include <wx/app.h>
#include "MyDrawMain.h"

/// Generic wxWidgets App class, nothing special here
class MyHistoApp: public wxApp
{
    bool OnInit();

    wxFrame *frame;
    HistoDrawPane * drawPane;
public:

};
#endif // MYDRAWAPP_H
