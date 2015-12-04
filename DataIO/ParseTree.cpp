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
struct ENTRY{
 float val[5];
} ;

template<typename MyData>
class BinParser{
	string fileName,treeName,branch;
	int leafnum;
	int binnum;
	MyData * arr;
	 TTree* tree;
	 TFile * file;
	vector<TH1*> histos;
	BinParser(string fileName, string treeName, string branch, int binnum, vector<TH1*> histos )
	: fileName(fileName), treeName(treeName), branch(branch), leafnum(histos.size()), binnum(binnum), histos(histos){
		arr = new MyData[leafnum];
		file = new TFile("TestData.root");
	}
	void parse(ostream & out, string separator="\n"){
		long entries = tree->GetEntries();
		for(long i =0;i<entries;++i){
			tree->GetEntry(i);
			long result = 0;
			for( unsigned j = 0; j < histos.size();++j){
				histos[j]->FindBin(arr[j]);

			}
		}
	}
	~BinParser(){
		delete [] arr;
		delete [] file;
		delete [] tree;
	}

};
int main(){
//	HistogramConfig hc("myproperties.json");
//			for(auto & c : hc.vec){
//				cout<<c.name<<" ";
//			}
//	TFile * file = new TFile("TestData.root");
//		 TTree* tree = (TTree*)file->Get("TestTree");
//		 fstream file1("multiplexed.bin", fstream::out | fstream::binary);
//		 tree->GetEntries();
//		 ENTRY aEntry;
//		 //tree->Branch("entry",&aEntry,"mass/f:ptL1/f:ptL2/f:isoL1/f:isoL2/f");
//		 float val[32];
//		 for(int i =0;i<32;++i) val[i]=0;
//		 tree->SetBranchAddress("entry", val);
//		cout<<tree->GetEntries()<<"entries\n";
//		int basis = 128;
//		for(int i =0;i<100;++i){
//			tree->GetEntry(i);
//			for(int j=0;j<6;++j)cout<<val[j]<<" ";
//			cout<<"\n";
//			for(int k=0;k< hc.vec.size();++k){
//							unsigned int j =hc.getBin(k,val[k]);
//							cout<<j<<" ";
//							file1.write((char*)&j, hc.vec[k].bytes);
//
//			}
//			cout<<"\n\n";
//
//		}
//		file1.close();
//
//		cout<<"\n"<<sizeof(short unsigned int);
	ptree pt;
	read_json("myproperties.json",pt);
	for(auto & p : pt){

		HistoCreator data(p.second);
		data.runTests();
		cout<<"\n"<<p.first;
	}
}
