/*
 * ParseTree.cpp
 *
 *  Created on: Oct 27, 2015
 *      Author: krystian892
 */




#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "HistoConfig.h"
#include"HistoCreator.h"
#include <fstream>

#include <boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>

using namespace boost::property_tree;
using namespace std;

class HistoProcessor : public HistoCreator{
public:
	HistoProcessor(ptree pt ) : HistoCreator(pt){

	}
	void processTree();
	void runTests();
};


/**
 * Loads ROOT file from hc.rootDataFile path and saves multiplexed binary file to hc.myDataFile path/
 */
void HistoProcessor::processTree() {
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
			file1.write((char*) &j, hc.vec[k].bytes);
		}
	}
	file1.close();

}



/**
 * Automatic testing function.
 * Loads data from ROOT tree, then processes the ROOT file again saving it to multiplexed binary file, then
 * loads multiplexed data with createHistos() and checks whether got the same bin values in all the histograms
 */
void HistoProcessor::runTests(){
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
int main(){
	ptree pt;
	read_json("config.json",pt);
	for(auto & p : pt){

		cout<<"\n"<<p.first;
		HistoProcessor data(p.second);
		data.runTests();
	}
}
//struct ENTRY{
// float val[5];
//} ;

//template<typename MyData>
//class BinParser{
//	string fileName,treeName,branch;
//	int leafnum;
//	int binnum;
//	MyData * arr;
//	 TTree* tree;
//	 TFile * file;
//	vector<TH1*> histos;
//	BinParser(string fileName, string treeName, string branch, int binnum, vector<TH1*> histos )
//	: fileName(fileName), treeName(treeName), branch(branch), leafnum(histos.size()), binnum(binnum), histos(histos){
//		arr = new MyData[leafnum];
//		file = new TFile("TestData.root");
//	}
//	void parse(ostream & out, string separator="\n"){
//		long entries = tree->GetEntries();
//		for(long i =0;i<entries;++i){
//			tree->GetEntry(i);
//			long result = 0;
//			for( unsigned j = 0; j < histos.size();++j){
//				histos[j]->FindBin(arr[j]);
//
//			}
//		}
//	}
//	~BinParser(){
//		delete [] arr;
//		delete [] file;
//		delete [] tree;
//	}
//
//};

