/**
 @file    DataSource.cpp
 @brief DataSource implementation
 @author   kzawisto
 @created:   2015-10-29
 **************************************************************/
#include <DataSource.h>
#define DATA_PRELOAD_TRESHOLD 300000000
///Wrapper for a (char*) chunk of memory, used by PreloadedDataSourse
struct DataBuffer{
	int len;
	char * buf;
	DataBuffer(string filepath,long int length);
	~DataBuffer(){delete buf;}
};
DataSource::DataSource(string path) : file1(path.c_str(), fstream::in | fstream::binary){
}

unsigned int DataSource::read( int bytes) {
	unsigned int i =0;
	file1.read((char*)(&i),bytes);
	return i;
}

DataSource::~DataSource() {
	file1.close();
}

PreloadedDataSource::PreloadedDataSource(DataBuffer * buf)  {
	buffer = buf;
	iter=0;
}

unsigned int PreloadedDataSource::read(int bytes) {
	unsigned int i = 0;
	unsigned char* c = (unsigned char*) &i;
	for(int j =0;j<bytes;++j) c[j]= buffer->buf[iter+j];
	iter+=bytes;
	return i;
}

PreloadedDataSource::~PreloadedDataSource() {
	delete buffer;
}

DataBuffer::DataBuffer(string filepath,long int length) {
	fstream file1(filepath.c_str(), fstream::in | fstream::binary);
	len = length;
	buf = new char [len];
	file1.read (buf,len);
	file1.close();

}

long int PreloadContainer::getLength(string path) {
	if(lengths.find(path) == lengths.end()){
		fstream file1(path.c_str(), fstream::in | fstream::binary);
		file1.seekg (0, file1.end);
		lengths[path]=file1.tellg();;
		file1.close();
	}
	return lengths[path];
}

DataBuffer* PreloadContainer::getDataBuffer(string path) {
	if(buffers.find(path) == buffers.end()){
		buffers[path] = new DataBuffer(path, getLength((path)));
	}
	return buffers[path];
}

IDataSource* PreloadContainer::getDataSource(string path) {
	auto l = getLength(path);
	if(l > DATA_PRELOAD_TRESHOLD) return new DataSource(path);
	else return new PreloadedDataSource(getDataBuffer(path));
}
