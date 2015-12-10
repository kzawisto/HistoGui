/** *************************************************************
 @file      MyDrawMain.h
 @brief   Defines wxWidgets Application Frame
 @author:    kzawisto
 @created:   2015-10-29
 **************************************************************/

#ifndef MYDRAWMAIN_H
#define MYDRAWMAIN_H

//(Headers(MyDrawFrame)
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
//*)
#include "wx/wx.h"
#include "wx/sizer.h"
#include <vector>

#include"HistoContainer.h"
#include "MyHistogramWrapper.h"


using namespace std;

///generic wxWidgets panel for drawing, and user interaction
class HistoDrawPane : public wxPanel
{
	int old_width, old_height;

public:
    //MyHistogram myHist,myHist1,myHist2,myHist3;//,myHist2;
	///Radio button to select low cut
	wxRadioButton * loCut,
	///Radio button to select high
	* hiCut;
	///Container for histoCreators
	HistoContainer hc;
	/// Histogram wrappers with is position and dimmensions
    std::vector<HistoGraph> histovec;
    ///Generic constructor
    HistoDrawPane(wxFrame* parent);

    void paintEvent(wxPaintEvent & evt);
    void sizeEvent(wxSizeEvent & evt);
    void paintNow();

    void render(wxDC& dc);
    void drawHisto(wxDC& dc, MyHistogramWrapper & h, wxPoint from, wxSize hsize);
    void drawTics(wxDC& dc, MyHistogramWrapper & h, wxPoint from, wxSize hsize);
    // some useful events
    void mouseDown(wxMouseEvent& event);

    void setHistSizes();
    ~HistoDrawPane(){}
    /*
     void mouseMoved(wxMouseEvent& event);

     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */

    DECLARE_EVENT_TABLE()
};

#endif // MYDRAWMAIN_H
