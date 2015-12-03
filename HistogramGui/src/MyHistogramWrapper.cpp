
#include <MyHistogramWrapper.h>
#include<cmath>
#include<cstdlib>
#include "HistoCreator.h"

MyHistogramWrapper::MyHistogramWrapper(int n, float xmin, float  xmax) : xmin(xmin), xmax(xmax)
{
//    fillGauss(n,n/2, 100);
//bins =new vector<unsigned int>();
//    setH();
//    title="Gauss";
}

MyHistogramWrapper::~MyHistogramWrapper()
{
    //dtor
}
/**Testing function: gaussian distribution, requires *bins to be allocated manually*/
void  MyHistogramWrapper::fillGauss(int n, int center, float height){
    for (int i =0;i<n ;++i )
        bins->push_back(height * exp(- pow(center - i,2)/1000 ));

}

/** Sets visible histogram Y range
 *
 */
void MyHistogramWrapper::setH()
{
    hmin = 0;
    hmax =0;
    for(int i =0;i< bins->size();++i){
        if((*bins)[i] < hmin) hmin = (*bins)[i];
        if((*bins)[i] > hmax) hmax = (*bins)[i];
    }
}
/**Find value given bin corresponds to
 *
 */
float MyHistogramWrapper::getNormalizedBin(int num)
{
    return (float)((*bins)[num] -hmin) /(float)(hmax-hmin);

}

/*Testing function: poissonian distribution, requires *bins to be allocated manually
 *
 */
void MyHistogramWrapper::fillPoisson(int n, float height,float lambda)
{
    int iFac =1;
    bins->clear();
    for (int i =0;i<n ;++i ){
        bins->push_back(height * pow(lambda,i)/iFac * exp(-lambda));
        if(i) iFac *=i;
    }
}

/**Testing function: random distribution, requires *bins to be allocated manually
 *
 */
void MyHistogramWrapper::fillRandom(int n, float hmin, float hmax)
{
    srand(time(0));
    int r = (hmax-hmin) * 100;
    bins->clear();
    for (int i =0;i<n ;++i ){
        bins->push_back(hmin + (rand() % r) / 100.0f);
    }
    setH();
}

/**Testing function: Fermi-Dirac distribution, requires *bins to be allocated manually
 *
 */
void MyHistogramWrapper::fillFermi(int n, float height, float coeff)
{   float j = xmin, step = (xmax - xmin)/n;
    bins->clear();
       for (;j<xmax ;j+=step )
        bins->push_back( 100.f / (1.f +exp(-j* coeff)) - 0.5f);
    setH();
}
/**
 * deprecated
 */
void MyHistogramWrapper::setCut(int b) {
	cutLow= b;
}
/**Sets lower cut and triggers histogram recreation
 *
 */
void MyHistogramWrapper::setCutLow(int b) {
	cutLow= b;
	creator->cutsLow[histoId] = b;
	creator->createHistos();
}

/**Sets higher cut and triggers histogram recreation
 *
 */
void MyHistogramWrapper::setCutHigh(int b) {
	cutHigh= b;
		creator->cutsHigh[histoId] = b;
	creator->createHistos();
}
