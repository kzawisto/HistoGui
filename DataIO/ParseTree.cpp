/*
 * ParseTree.cpp
 *
 *  Created on: Oct 27, 2015
 *      Author: krystian892
 */




#include <HistoCreator.h>
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "HistoConfig.h"
#include <fstream>

#include <boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>

using namespace boost::property_tree;
using namespace std;
int main(){
	ptree pt;
	read_json("config.json",pt);
	for(auto & p : pt){

		cout<<"\n"<<p.first;
		HistoCreator data(p.second);
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

