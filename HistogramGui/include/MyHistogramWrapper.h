/****
@file MyHistogramWrapper.h
 @brief Responsible for direct communication between the GUI and HistoCreator
 @author   kzawisto
 @created:   2015-11-04
 ***/
/** *************************************************************
 @file      MyHistogramWrapper.h
 @brief   Responsible for direct communication between the GUI and HistoCreator
 @author    kzawisto
 @created:   2015-10-29

 **************************************************************/
#ifndef MYHISTOGRAM_H
#define MYHISTOGRAM_H
#include<vector>
#include<string>
using namespace std;
class HistoCreator;
/**
 * This class handles all the communication between the GUI and DataIO framework
 */
class MyHistogramWrapper
{

    public:
         float xmin,  xmax;
    float hmin, hmax;
    float tics_spacing=0.1, numbered_tics_spacing = 0.2;
    string title;
    ///pointer to vector owned by creator
    vector<unsigned int> * bins;
    HistoCreator * creator;
    ///id of a histogram in creator
    int histoId;
    int cutLow=0, cutHigh=0;
    ///constructor, sets bin range and the num of bins
        MyHistogramWrapper(int n, float xmin, float  xmax);

        virtual ~MyHistogramWrapper();
        void fillGauss(int n, int center, float height);
        void setH();
        void setCut(int b);
        void setCutLow(int b);
        void setCutHigh(int b);
        float getNormalizedBin(int num);
        void fillPoisson(int n, float height,float k);
        void fillRandom(int n, float hmin, float hmax);
        void fillFermi(int n, float height, float coeff);
       // bool testPointInside(long int x, long int y);
    protected:
    private:
};


#endif // MYHISTOGRAM_H
