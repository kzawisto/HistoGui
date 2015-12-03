/***************************************************************
 @file      MyDrawMain.cpp
 @brief   Code for Application Frame
 * Author:    kzawisto ()
 * Created:   2015-10-29
 * Copyright: kzawisto ()
 * License:
 **************************************************************/


#include"MyDrawMain.h"
#include "Utils.h"
#include "wx/font.h"
#include <algorithm>
#include <cmath>

/**This function specifies histogram layout on each redraw of the GUI.
 * Tweak the layout here.
 */
void HistoDrawPane::setHistSizes() {
	if(!hc.good) return;
	GetSize(&old_width,&old_height);
//	histovec=hc.buildGuiHistos();
//	hc.createLogicalHistos();
	int rows =2, cols = (histovec.size()+1)/2;
//	if(histovec.size() <=5){
//		rows = 1; cols = histovec.size();
//	}
//	if(histovec.size() >=9){
//		rows = 3; cols = (histovec.size()+2)/3;
//	}

			int ofs = min(old_width,old_height)/20;

			int sizex = old_width/cols - ofs*2, sizey = old_height/rows - ofs*2;
			wxSize mySize(sizex, sizey);
			//int per_row=2, per_column=2;
			for(int i =0;i<rows;++i)
				for(int j=0;j< cols &&  i*rows + j <histovec.size();++j){
					 histovec[i*rows+j].r= wxRect(wxPoint((1+2*j)*ofs + j *sizex,10+(1+2*i)*ofs +i *sizey), mySize);
				}

}

BEGIN_EVENT_TABLE(HistoDrawPane, wxPanel)
// some useful events
/*
 EVT_MOTION(BasicDrawPane::mouseMoved)

 EVT_LEFT_UP(BasicDrawPane::mouseReleased)
 EVT_RIGHT_DOWN(BasicDrawPane::rightClick)
 EVT_LEAVE_WINDOW(BasicDrawPane::mouseLeftWindow)
 EVT_KEY_DOWN(BasicDrawPane::keyPressed)
 EVT_KEY_UP(BasicDrawPane::keyReleased)
 EVT_MOUSEWHEEL(BasicDrawPane::mouseWheelMoved)
 */
EVT_LEFT_DOWN(HistoDrawPane::mouseDown)
// catch paint events
EVT_PAINT(HistoDrawPane::paintEvent)
EVT_SIZE(HistoDrawPane::sizeEvent)
END_EVENT_TABLE()


// some useful events
/*
 void BasicDrawPane::mouseMoved(wxMouseEvent& event) {}
 void BasicDrawPane::mouseDown(wxMouseEvent& event) {}
 void BasicDrawPane::mouseWheelMoved(wxMouseEvent& event) {}
 void BasicDrawPane::mouseReleased(wxMouseEvent& event) {}
 void BasicDrawPane::rightClick(wxMouseEvent& event) {}
 void BasicDrawPane::mouseLeftWindow(wxMouseEvent& event) {}
 void BasicDrawPane::keyPressed(wxKeyEvent& event) {}
 void BasicDrawPane::keyReleased(wxKeyEvent& event) {}
 */

HistoDrawPane::HistoDrawPane(wxFrame* parent) :
wxPanel(parent),   hc("config.json")//, myHist(100,0,300),myHist1(100,-100,100), myHist2(100,0,100),  myHist3(100,0,100)
{

	 loCut = new wxRadioButton(this, -1,
	      wxT("Low"), wxPoint(5, 5), wxDefaultSize, wxRB_GROUP);

	  hiCut = new wxRadioButton(this, -1,
	      wxT("High"), wxPoint(100, 5));
	if(hc.good){
		histovec = hc.buildGuiHistos();
		hc.createLogicalHistos();
		for(auto &h :histovec)
			h.histo.setH();
		setHistSizes();
	}
}

/**
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */
void HistoDrawPane::paintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    render(dc);
}

/**
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 *
 * In most cases, this will not be needed at all; simply handling
 * paint events and calling Refresh() when a refresh is needed
 * will do the job.
 */
void HistoDrawPane::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

/**
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void HistoDrawPane::render(wxDC&  dc)
{
    int width, height;
    dc.GetSize(&width,&height);
    // draw some text
//    dc.DrawText(wxT("Testing"), width/2, 60);

    // draw a circle
//    dc.SetBrush(*wxGREEN_BRUSH); // green filling
//    dc.SetPen( wxPen( wxColor(255,0,0), 5 ) ); // 5-pixels-thick red outline
//    dc.DrawCircle( wxPoint(200,100), 25 /* radius */ );

    // draw a rectangle
//    dc.SetBrush(*wxWHITE_BRUSH); // blue filling
//    dc.SetPen( wxPen( wxColor(0,175,0), 3) ); // 10-pixels-thick pink outline
//    dc.DrawRectangle( 0, 0, width/2, height/2 );

    // draw a line
   setHistSizes();
    dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
    int ofs = min(width,height)/20;
    int sizex = width/2 - ofs*3/2, sizey = height/2 - ofs*3/2;
    wxSize mySize(sizex, sizey);
   for(int a=0;a<histovec.size();++a){

   	drawHisto(dc,histovec[a].histo,histovec[a].r.GetLeftTop(),histovec[a].r.GetSize());
    }
//    drawHisto(dc, myHist, wxPoint(ofs,ofs), mySize);
//     drawHisto(dc, myHist1, wxPoint(2*ofs+sizex,ofs),  mySize);
//      drawHisto(dc, myHist2, wxPoint(ofs,2*ofs+sizey),  mySize);

}
/** Here we draw all the histogram i.e. bins, ticks, labels, frame, and so on
 *
 */
void HistoDrawPane::drawHisto(wxDC& dc, MyHistogramWrapper & hist, wxPoint from, wxSize hsize)
{
     wxFont signFont(min(hsize.y,hsize.x)/20, wxFontFamily::wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFontWeight::wxFONTWEIGHT_NORMAL);
     dc.SetFont(signFont);
     dc.SetBrush(*wxWHITE_BRUSH); // blue filling
    dc.SetPen( wxPen( wxColor(0,0,0), 3) ); // 10-pixels-thick pink outline
    dc.DrawRectangle(from, hsize);
    wxString mstr ( hist.title.c_str(),  wxConvUTF8);
    wxRect r ( from.x + hsize.x/2-50, from.y + hsize.y/12-50,100,100);

    dc.DrawLabel(mstr,r,wxALIGN_CENTER);
   //dc.DrawText(mstr,from.x + hsize.x/2, from.y + hsize.y/8);

    drawTics(dc,hist,from,hsize);

    for(int i =0; i < hist.bins->size();++i){
        int x = from.x + i * hsize.x / hist.bins->size();
        int y =int ( from.y + (1-hist.getNormalizedBin(i)) * hsize.y);

         //dc.DrawPoint( wxPoint(x,y));
        dc.DrawCircle( wxPoint(x,y),1);
    }

}
/**
 * Function triggered by wxWidgets when the window is resized. We trigger setHistSize in render()
 * anyway, so we just Refresh() here.
 */
 void HistoDrawPane::sizeEvent(wxSizeEvent& evt)
 {
       Refresh();
}
 /**
  * Draw ticks and labels
  */
void HistoDrawPane::drawTics(wxDC& dc, MyHistogramWrapper& hist, wxPoint from, wxSize hsize)
{
    int fontSize=min(hsize.y,hsize.x)/40;
     dc.SetPen( wxPen( wxColor(0,0,0), 2) );
     wxFont ticsFont(fontSize, wxFontFamily::wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFontWeight::wxFONTWEIGHT_NORMAL);
    dc.SetFont(ticsFont);
    for(float j = 0; j <= 1.f; j+=  hist.tics_spacing){
        dc.DrawLine(wxPoint(from.x+hsize.x * j, from.y+ hsize.y), wxPoint(from.x+hsize.x * j, from.y+ hsize.y - hsize.y *0.02f));
        dc.DrawLine(wxPoint(from.x , from.y+ hsize.y* j), wxPoint(from.x  + hsize.x *0.02f , from.y+ hsize.y* j));
    }
    for(float j = hist.numbered_tics_spacing; j <=1.f; j+=  hist.numbered_tics_spacing){
         wxRect r (from.x+hsize.x * j-20, from.y+ hsize.y-10 + fontSize*2,40,20);
        string s1 = Utils::itos<double> (hist.xmin + (hist.xmax - hist.xmin)*j, 2);
        dc.DrawLabel(wxString(s1.c_str(), wxConvUTF8),r,wxALIGN_CENTER);
        //        dc.DrawLine(wxPoint(from.x , from.y+ hsize.y* j), wxPoint(from.x  + hsize.x *0.02f , from.y+ hsize.y* j));
  }
   for(float j =  hist.numbered_tics_spacing; j <=1.f ; j+=  hist.numbered_tics_spacing){
          wxRect r1 (from.x-20 - fontSize*2.5, from.y+ hsize.y*(1-j)-10,40,20);
     string s2 = Utils::itos<double> (hist.hmin + (hist.hmax - hist.hmin)*j, 2);
      dc.DrawLabel(wxString(s2.c_str(), wxConvUTF8),r1,wxALIGN_CENTER);
   }
   if(hist.cutLow){
	   double c = hist.cutLow; c/= hist.bins->size();

	   cout<<c<<" ";
	   int x = from.x + hsize.x*c;
	   dc.SetPen( wxPen( wxColor(255,0,0), 2) );
	   dc.DrawLine(wxPoint(x, from.y),wxPoint(x, from.y+hsize.y));
   }
   if(hist.cutHigh){
  	   double c = hist.cutHigh; c/= hist.bins->size();
  	   cout<<c<<" ";
  	   int x = from.x + hsize.x*c;
  	 dc.SetPen( wxPen( wxColor(0,255,0), 2) );
  	   dc.DrawLine(wxPoint(x, from.y),wxPoint(x, from.y+hsize.y));
     }
   dc.SetPen( wxPen( wxColor(0,0,0), 2));
}
/** Here we react to clicks at point x,y, by setting cuts to the given histogram and resetting
 * all the histograms from the HistoCreator it belongs to
 */
void HistoDrawPane::mouseDown(wxMouseEvent& event) {

	long int x,y;
	event.GetPosition(&x,&y);
	wxPoint p=event.GetPosition();

	int a =0;
	for(;a<histovec.size();++a)
		if(histovec[a].r.Contains(p))break;;
	if(a==histovec.size()) return;
	int cut =histovec[a].histo.bins->size()* ((double)(x - histovec[a].r.x)) / (histovec[a].r.width);
	if(loCut->GetValue())
		histovec[a].histo.setCutLow(cut);
	else if(hiCut->GetValue())histovec[a].histo.setCutHigh(cut);

	Refresh();
}
