/**
 @file    HistoCreator.cpp
 @brief HistoCreator implementation
 @author   kzawisto
 @created:   2015-10-29
 **************************************************************/


#include<fstream>
#include<iostream>
#include<DataSource.h>
#include <HistoCreator.h>
using namespace std;

/**
 * Constructor takes configuration from boost::program_options ptree, loaded from json_config
 */
HistoCreator::HistoCreator(ptree pt) :hc(pt)  {

	for (int i = 0; i < hc.vec.size(); ++i) {
			histos.push_back(vector<unsigned int>(hc.vec[i].bins));
			cutsLow.push_back(0);
				cutsHigh.push_back(hc.vec[i].bins);
		}
}


/**
 * Loads data from DataSource and fills bins
 */
void HistoCreator::createHistos() {
	writeZeros();
	IDataSource *ids= PreloadContainer::get().getDataSource(hc.myDataFile.c_str());
	unsigned int val [hc.vec.size()];
	for (int i = 0; i < hc.numOfEvents; ++i){
			int l = 0;
			for (int k = 0; k < hc.vec.size(); ++k){
				val[k]=ids->read( hc.vec[k].bytes);
				if(val[k] < cutsLow[k] or val[k]>= cutsHigh[k]) l = hc.vec.size();
			}
			for(;l<hc.vec.size();++l){
				histos[l][val[l]]++;
			}

	}
}
void HistoCreator::createHistosOld() {
	fstream file1(hc.myDataFile.c_str(), fstream::in | fstream::binary);
	unsigned int val [hc.vec.size()];
	for (int i = 0; i < hc.numOfEvents; ++i) {

			for (int k = 0; k < hc.vec.size(); ++k) {
				val[k]=0;
				file1.read((char*)(val+k), hc.vec[k].bytes);
				histos[k][val[k]]++;

//				//unsigned int j = hc.getBin(k, val[k]);
//				file1.write((char*) &j, hc.vec[k].bytes);
			}
	}
}
/**
 * Writes zeros to all histograms' bins
 */
void HistoCreator::writeZeros() {
		for (auto &vec: histos) for(auto &v:vec) v =0;
}

