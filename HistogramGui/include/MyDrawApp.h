    /***************************************************************
 * Name:      MyDrawApp.h
 * Purpose:   Defines Application Class
 * Author:    kzawisto ()
 * Created:   2015-10-29
 * Copyright: kzawisto ()
 * License:
 **************************************************************/

#ifndef MYDRAWAPP_H
#define MYDRAWAPP_H

#include <wx/app.h>
#include "MyDrawMain.h"

/** Generic wxWidgets App class, nothing special here
 *
 */
class MyHistoApp: public wxApp
{
    bool OnInit();

    wxFrame *frame;
    HistoDrawPane * drawPane;
public:

};
#endif // MYDRAWAPP_H
