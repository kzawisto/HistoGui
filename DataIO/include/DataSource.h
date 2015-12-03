/*
 * DataSource.h
 *
 *  Created on: Nov 2, 2015
 *      Author: kzawisto
 */

#ifndef INCLUDE_DATASOURCE_H_
#define INCLUDE_DATASOURCE_H_
#include <fstream>
#include <string>
#include <map>
using std::__cxx11::string;
using std::fstream;
using std::map;
///Abstract DataSource, taken by HistoCreator to load multiplexed data
class IDataSource{
public:

	IDataSource(){}
	virtual unsigned int read(int bytes)=0;
	virtual bool good(){return true;}
	virtual ~IDataSource(){};
};
///Regular DataSource, loads from multiplexed binary file each time.
class DataSource :public IDataSource{
	fstream file1;
public:
	DataSource(string path);
	virtual unsigned int read(int bytes);
	virtual ~DataSource();
};
struct DataBuffer;
class PreloadContainer{
	map<string, long int> lengths;
	map<string, DataBuffer*> buffers;
	long int getLength(string path);
public:
	static PreloadContainer& get(){ static PreloadContainer inst; return inst;}
	DataBuffer * getDataBuffer(string path);
	IDataSource * getDataSource(string path);
};
///Cached DataSource, data stored in RAM during program run.
class PreloadedDataSource : public IDataSource{
	DataBuffer * buffer;
	long int iter;
public:
	PreloadedDataSource(DataBuffer * buf);
	virtual unsigned int read(int bytes);
	virtual ~PreloadedDataSource();
};
#endif /* INCLUDE_DATASOURCE_H_ */
