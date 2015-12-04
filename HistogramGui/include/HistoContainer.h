/**
 @file    HistoContainer.h
 @brief Wraps HistoCreators and provides data to the GUI
 @author   kzawisto
 @created:   2015-11-04
 **************************************************************/
#ifndef INCLUDE_HISTOCONTAINER_H_
#define INCLUDE_HISTOCONTAINER_H_
#include<string>
#include <vector>
#include<memory>

#include "wx/wx.h"
using namespace std;
#include <boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>

#include"MyHistogramWrapper.h"
class HistoCreator;
using namespace boost::property_tree;
///Wrapped histogram and its dimensions on the screen
struct HistoGraph{
	///wrapper
	MyHistogramWrapper histo;
	///Position and size
	wxRect r;
	///wrapped histo constructor
	HistoGraph(int bin, float min, float max):histo(bin,min,max){

	}

};
/**
 * Proxy between GUI and DataIO.so
 */
class HistoContainer {
	public:
		/// Whether histograms were loaded successufy and can be drawn
		bool good;
		///constructor, loads config from json and constructs HistoCreators
		HistoContainer(string json_path);
		///HistoCreators, construct histograms, store bins to display
		vector< HistoCreator* > creators;;
		///Set binding between data and GUI objects
		vector<HistoGraph>buildGuiHistos();
		/// Reset and fill bins with experimental data, loaded from file/RAM cache
		void createLogicalHistos();
		///Get rid of Creators
		~HistoContainer();
};

#endif /* INCLUDE_HISTOCONTAINER_H_ */
