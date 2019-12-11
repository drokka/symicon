#include <iostream>
#include <map>
#include "QuiltIcon.h"

#include "Generator.h"
#include "PaintIcon.h"
#include <ctime>
#include <fstream>
#include "SymIconApp.h"
#include "symi_interface.cpp"

using namespace std;
using namespace emu::symicon;


int main(int nparam, char** param) {

    long iterations = 1000000;
    if(nparam >1){
        try {
            iterations = atol(param[1]);
        }catch (...){//do nothing
        }
    }

    long res = callSym(iterations);
    cout << "got max hits:" << res << endl;

/************************************************************************
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
************************************************************/
    return 0;

    }


    