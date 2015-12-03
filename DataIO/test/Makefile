IDIR = -I../ -I../include/
FLAGS = -std=c++11 -g 

TestData: TestData.o DataSource.o
	g++ -o $@ $^ -L/usr/lib/x86_64-linux-gnu/ -lboost_unit_test_framework

DataSource.o: ../src/DataSource.cpp
	g++ -o $@ -c $^ ${IDIR} ${FLAGS}
TestData.o: TestData.cpp
	g++ -o $@ -c $^ ${IDIR} ${FLAGS}