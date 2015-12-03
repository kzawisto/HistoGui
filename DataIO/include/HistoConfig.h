/*
 * HistoConfig.h
 *
 *  Created on: Oct 30, 2015
 *      Author: kzawisto
 */

#ifndef INCLUDE_HISTOCONFIG_H_
#define INCLUDE_HISTOCONFIG_H_
#include <string>
#include <vector>
#include<cmath>
#include <boost/property_tree/ptree.hpp>
using std::__cxx11::string;
using std::vector;
typedef short unsigned int SUINT;
using namespace boost::property_tree;
///A configuration container for histograms created from one ROOT branch (as series of events).

class HistogramConfig{
public:
	///number of histograms in given binary file/ROOT file
	int numOfHistos;
	///number of events to load
	int numOfEvents;
	///length of a given event in bytes in muptiplexed data file (all entries together)
	int multiplexedByteLenOfEvent;
	string treeName, branchName, rootDataFile, myDataFile;
	///Basic single histogram config aggregate, contains its name, value range, byte length (log_128(bins)).
	struct MyHisto{
		string name;
		int bins, bytes;
		float min, max;
	};
	///vector of histogram config data aggregates
	vector<MyHisto> vec;
	HistogramConfig(string path_to_json);
	HistogramConfig(ptree pt);
	unsigned int getBin(int histo, float value);
	int noOfBytes(int i);
};
/// Returns how much bytes do we need to save given unsigned int
inline int HistogramConfig::noOfBytes(int i) {
		return (log(i)/log(2.0)+7.9999999)/8;
}


#endif /* INCLUDE_HISTOCONFIG_H_ */
