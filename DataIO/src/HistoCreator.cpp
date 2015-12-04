/**
 @file    HistoCreator.cpp
 @brief HistoCreator implementation
 @author   kzawisto
 @created:   2015-10-29
 **************************************************************/

#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include<fstream>
#include<iostream>
#include<DataSource.h>
#include <HistoCreator.h>
using namespace std;
/**
 * Unused, takes configuration from json at _configPath.
 */
HistoCreator::HistoCreator(string _configPath) :
		configPath(_configPath), hc(_configPath) {
	for (int i = 0; i < hc.vec.size(); ++i) {
		histos.push_back(vector<unsigned int>(hc.vec[i].bins));
		cutsLow.push_back(0);
		cutsHigh.push_back(hc.vec[i].bins);
	}
}
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
 * Loads ROOT file from hc.rootDataFile path and saves multiplexed binary file to hc.myDataFile path/
 */
void HistoCreator::processTree() {
	TFile * file = new TFile( hc.rootDataFile.c_str());
	TTree* tree = (TTree*) file->Get(hc.treeName.c_str());
	fstream file1(hc.myDataFile.c_str(), fstream::out | fstream::binary);
	tree->GetEntries();
	float val[32];
	for (int i = 0; i < 32; ++i)
		val[i] = 0;
	tree->SetBranchAddress(hc.branchName.c_str(), val);
	for (int i = 0; i <  hc.numOfEvents; ++i) {
		tree->GetEntry(i);
		for (int k = 0; k < hc.vec.size(); ++k) {
			unsigned int j = hc.getBin(k, val[k]);
			//cout<<j<<" ";
			file1.write((char*) &j, hc.vec[k].bytes);
		}
		//cout<<"\n";
	}
	file1.close();

}

/**
 * Loads data from DataSource and fills bins
 */
void HistoCreator::createHistos() {
	writeZeros();
	//fstream file1(hc.myDataFile.c_str(), fstream::in | fstream::binary);
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
/**
 * Automatic testing function.
 * Loads data from ROOT tree, then processes the ROOT file again saving it to multiplexed binary file, then
 * loads multiplexed data with createHistos() and checks whether got the same bin values in all the histograms
 */
void HistoCreator::runTests(){
	for(auto h:histos)
		for(int i =0;i<h.size();++i) h[i]=0;

	vector< vector<unsigned int> > histos_copy;
	for (int i = 0; i < hc.vec.size(); ++i) {
			histos_copy.push_back(vector<unsigned int>(hc.vec[i].bins));
	}
	TFile * file = new TFile(hc.rootDataFile.c_str());
	TTree* tree = (TTree*) file->Get(hc.treeName.c_str());
	tree->GetEntries();
	float val[32];
	for (int i = 0; i < 32; ++i)val[i] = 0;
	tree->SetBranchAddress(hc.branchName.c_str(), val);
	for (int i = 0; i <  hc.numOfEvents; ++i) {
			tree->GetEntry(i);
			for (int k = 0; k < hc.vec.size(); ++k) {
						unsigned int j = hc.getBin(k, val[k]);
						histos_copy[k][j]++;
			}
	}
	processTree();
	createHistos();
	int errors=0;
	for(int i =0;i < histos.size();++i)
		for(int j =0; j<histos[i].size();++j){
			errors+= histos[i][j]!= histos_copy[i][j];
		}
	cout<<"Errors: "<<errors<<".";
	if(errors == 0) cout<<" Everything is fine.";
	else cerr<<"What a terrible failure";
}
