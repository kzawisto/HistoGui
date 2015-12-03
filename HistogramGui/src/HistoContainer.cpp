/*
 @file HistoContainer.cpp
 @brief Implementation of container for HistoCreators
 *  Created on: Nov 4, 2015
 *      Author: kzawisto
 */

#include <MyHistogramWrapper.h>
#include "HistoContainer.h"
#include"HistoCreator.h"
#include<cstdlib>
#include<sys/stat.h>
#include<fstream>
/// to test whether config_json exists
bool fileExists(const std::string & name){
	ifstream f(name.c_str());
	bool ret=(f.good());
	f.close();
	return ret;

}
HistoContainer::HistoContainer(string json_path) {
		ptree pt;

		if(! fileExists(json_path)){
			cout<<"ERROR: No such file: "<<json_path<<"\n";
			cout<<"Current working dir is"<<endl;
			system("pwd");
			good = false;
		}
		else{
			good = true;
		read_json(json_path,pt);
		for(auto & p : pt){
			cout<<"boo";
			if(p.first.substr(0,3) =="dat")
			creators.push_back(new HistoCreator(p.second));
		}
		}
}

vector<HistoGraph> HistoContainer::buildGuiHistos() {
	vector<HistoGraph> histos;
	for(auto  c : creators){
		auto it =c->histos.begin();
		int i=0;
		for(auto &h: c->hc.vec){
			histos.push_back(HistoGraph(h.bins,h.min,h.max));
			histos.back().histo.title = h.name;
			histos.back().histo.bins = &(*it);
			histos.back().histo.creator = &(*c);
			histos.back().histo.histoId = i;
			it++;
			i++;
		}
	}

	return histos;
}
void HistoContainer::createLogicalHistos() {
	for(auto  c : creators) c->createHistos();
}
HistoContainer::~HistoContainer() {
	for(int i =0;i < creators.size();++i)
		delete	creators[i];
}
