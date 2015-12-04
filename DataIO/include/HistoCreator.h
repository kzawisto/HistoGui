/**
 @file    HistoCreator.h
 @brief Loads multiplexed binary file for the GUI or processes ROOT tree to generate one
 @author   kzawisto
 @created:   2015-10-29
 **************************************************************/

#ifndef INCLUDE_HISTOCREATOR_H_
#define INCLUDE_HISTOCREATOR_H_
#include <string>
#include <vector>
#include"HistoConfig.h"
using std::__cxx11::string;
using std::vector;

class HistoCreator {
	string configPath;

public:
	vector<unsigned int> cutsLow,cutsHigh;
	HistogramConfig hc;
	vector< vector<unsigned int> > histos;
	HistoCreator(string configPath );
	HistoCreator(ptree pt );
	void processTree();
	void createHistos();
	void createHistosOld();
	void writeZeros();
	void runTests();
};

#endif /* INCLUDE_HISTOCREATOR_H_ */
