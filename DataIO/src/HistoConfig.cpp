/*
 * HistoConfig.cpp
 *
 *  Created on: Oct 30, 2015
 *      Author: kzawisto
 */

#include "HistoConfig.h"

#include<boost/property_tree/json_parser.hpp>
#include <cstdlib>
#include <iosfwd>
using namespace std;
/**
 * UNUSED, loads config from json file, aside from that the same as ptree version.
 */
HistogramConfig::HistogramConfig(string path_to_json) {
	using namespace boost::property_tree;
	ptree pt;
	read_json(path_to_json, pt);
	ptree histos=pt.get_child("histos");
	ptree options=pt.get_child("options");

	numOfEvents = options.get<int>("numOfEvents");
	treeName = options.get<string>("treeName");
	branchName = options.get<string>("branchName");
	rootDataFile = options.get<string>("rootDataFile");
	myDataFile = options.get<string>("myDataFile");
	//auto iter = pt.begin(),iterEnd = pt.end();
	multiplexedByteLenOfEvent=0;
	for(auto h:histos){
		int bins =  h.second.get<int>("bins");
		int bytes = noOfBytes(bins);
		multiplexedByteLenOfEvent +=bytes;
		vec.push_back({h.second.get<string>("name"), bins,bytes,h.second.get<float>("min"),h.second.get<float>("max")});
	}
	numOfHistos = vec.size();
		    //cout<<" "<<  iter->second; // The object at each step {"pos": [0,0,0], "vel": [0,0,0]}, etc.

}
/**
 * Constructor loads config stuff from boost::program_options ptree (json initialized), i.e.
 * ROOT data config (number of events to load, file name, tree name, branch name), multiplexed data file name
 * (location of the existing or a path to write a new one from ROOT tree.
 */
HistogramConfig::HistogramConfig(ptree pt){
	ptree histos=pt.get_child("histos");
	ptree options=pt.get_child("options");
	numOfEvents = options.get<int>("numOfEvents");
	treeName = options.get<string>("treeName");
	branchName = options.get<string>("branchName");
	rootDataFile = options.get<string>("rootDataFile");
	myDataFile = options.get<string>("myDataFile");
	//auto iter = pt.begin(),iterEnd = pt.end();
	multiplexedByteLenOfEvent=0;
	for(auto h:histos){
		int bins =  h.second.get<int>("bins");
		int bytes = noOfBytes(bins);
		multiplexedByteLenOfEvent +=bytes;
		vec.push_back({h.second.get<string>("name"), bins,bytes,h.second.get<float>("min"),h.second.get<float>("max")});
	}
	numOfHistos = vec.size();
}
/*
 * For a given value retrieve a bin number it should be added to, for a given histogram.
 */
unsigned int HistogramConfig::getBin(int histo, float value) {

	long int b = (long int) (( value - vec[histo].min)/(vec[histo].max - vec[histo].min) *  vec[histo].bins);
	if(b<0) {
		b=0;
		cerr<<"\n" << value <<" out of range ["<<vec[histo].min<<", "<<vec[histo].max<< "]";
	}
	else if(b>=  vec[histo].bins){
		b=vec[histo].bins;
		cerr<<"\n" << value <<" out of range ["<<vec[histo].min<<", "<<vec[histo].max<< "]";
	}
	return (unsigned int)b;
}

