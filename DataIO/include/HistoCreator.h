/*
 * DataIO.h
 *
 *  Created on: Oct 30, 2015
 *      Author: kzawisto
 */

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
