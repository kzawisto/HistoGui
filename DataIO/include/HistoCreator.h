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
using std::string;
using std::vector;


///Creates histos from single IDataSource
class HistoCreator {
	string configPath;

public:
	vector<unsigned int> cutsLow,cutsHigh;
	HistogramConfig hc;
	vector< vector<unsigned int> > histos;

	HistoCreator(ptree pt );

	void createHistos();
	void createHistosOld();
	void writeZeros();

};

#endif /* INCLUDE_HISTOCREATOR_H_ */
