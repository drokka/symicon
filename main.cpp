#include <iostream>
#include <map>
#include "QuiltIcon.h"

#include "Generator.h"
#include "PaintIcon.h"
#include <ctime>
#include <fstream>
#include "SymIconApp.h"

using namespace std;
using namespace emu::symicon;

void testColourFn(double *minRGBA, double *maxRGBA, long hits, FrequencyData &fd, double *rgbaOut) ;

int main(int nparam, char** param) {

    long iterations = 1000000;
    if(nparam >1){
        try {
            iterations = atol(param[1]);
        }catch (...){//do nothing
        }
    }

    int sz = 1600;

    QuiltIcon::QuiltType quiltType = QuiltIcon::QuiltType::SQUARE;
    if (nparam >= 3) {
        if ('H' == param[2][0]) { quiltType = QuiltIcon::QuiltType::HEX; }
        else if ('F' == param[2][0]) { quiltType = QuiltIcon::QuiltType::FRACTAL; }
    }
    double lambdaVal = 0.6;
    double alphaVal = 0.2;
    double betaVal = 0.3;
    double gammaVal = 0.4;
    double omegaVal = 0.2;
    double maVal = 0.3;
    if (nparam == 9) {
        try {
            lambdaVal = atof(param[3]);
            alphaVal = atof(param[4]);
            betaVal = atof(param[5]);
            gammaVal = atof(param[6]);
            omegaVal = atof(param[7]);
            maVal = atof(param[8]);
        } catch (...) {
            cout << "Error reading QuiltIcon parameters." << endl;
            //continue using default values
        }
    }
    cout << "got parameters " << endl;
    cout << "lambdaVal " << lambdaVal << endl;
    cout << "alphaVal " << alphaVal << endl;
    cout << "betaVal " << betaVal << endl;
    cout << "gammaVal " << gammaVal << endl;
    cout << "omegaVal " << omegaVal << endl;
    cout << "maVal " << maVal << endl;


    double initX = 0.307;
    double initY = 0.079;
    std::string fnBase = "img_a_";

    double iconParams[] = {lambdaVal, alphaVal, betaVal, gammaVal, omegaVal, maVal};
    int numIconParams = 6;
    double bg[] ={0.0,0.0,0.0,.2};
    double min[]= {0.0,0.0,1,0.5};
    double max[] = {1,1,0.0,1.0};

    PaintIcon::ColourFn colourFn = testColourFn;

    SymIconApp app(iterations, initX, initY, quiltType, fnBase, sz, iconParams, numIconParams, bg, min, max, colourFn);
    app.runGenerator();
    cout << "max hits: " << app.maxhits << endl;
    app.paint();

    return 0;

    }

void testColourFn(double *minRGBA, double *maxRGBA, long hits, FrequencyData &fd,
                  double *rgbaOut) {
    long maxhits = fd.maxHits;
    // cout<< "maxHits for " << sz <<" is "<< maxhits<<endl;
    long fdiff = maxhits>1?maxhits-1: 1; //maxx -minn;

    //  cout << "maxhits " <<maxhits <<endl;
    double opacity = (double)((double)hits/(double)maxhits);
    //   cout <<"opacity " << opacity <<endl;std::max(
//opacity=0.3*opacity;
    //bound opacity between 0 and 1.
    opacity = (opacity <= .5)?0.5:opacity;
   // opacity = (opacity >1)?1:opacity;
    double span1= maxRGBA[0] - minRGBA[0];
    double span2= maxRGBA[1] - minRGBA[1];
    double span3= maxRGBA[2] - minRGBA[2];

    rgbaOut[0]= minRGBA[0] +span1*opacity;
    rgbaOut[1]= minRGBA[1] +span2*opacity;
    rgbaOut[2]= minRGBA[2] +span3*opacity;
    rgbaOut[3]=opacity;
}
    