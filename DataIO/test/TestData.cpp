/*
 * TestData.cpp
 *
 *  Created on: Nov 3, 2015
 *      Author: kzawisto
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test2
#include "boost/test/unit_test.hpp"

#include <string>

using std::__cxx11::string;

#include "DataSource.h"

BOOST_AUTO_TEST_CASE(test1){
 string path = "bindata";
 IDataSource * dat1 = new DataSource(path),
	*dat2 = new PreloadedDataSource(PreloadContainer::get().getDataBuffer("bindata"));
for(int a=0;a<4000;++a){
 long int i1= dat1->read(4), i2 = dat2->read(4);
 BOOST_CHECK_EQUAL(i1,i2);
}
}
