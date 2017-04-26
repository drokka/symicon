#include <iostream>
#include <map>
#include "QuiltIcon.h"

#include "Generator.h"
#include "PaintIcon.h"
#include <cairo.h>
#include <ctime>
#include <fstream>


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
    PointList hl;
    int sz = 1600;
    hl.addTable(sz); //add a fine scale
    hl.addPoints();

    if(nparam == 3){
        iterations = stol(param[2]);
    }
    Parameter<int> omega("omega", 7);
    cout<<  omega.getValue() <<endl;

    omega.setValue(77);
    cout<< omega.getName() <<" "<< omega.getValue() <<endl;

    Parameter<int> delta("delta",1, 10, false, false,  7);
    cout<< delta.getName() <<" "<< delta.getValue() <<endl;
    delta.setValue(11);

    delta=0.5;
    cout<< delta.getName() <<" "<< delta.getValue() <<endl;



    QuiltIcon qi(0.6,0.2,0.3,0.4,0.2,0.3);
    Generator gg(&qi,iterations, &hl);
    try {
        gg.go(Point2D(.7, .53));
    }catch (std::exception xx){
        cout<< "Error: " << xx.what() <<endl;
        return 1;
    }catch (...){
        cout<<"error some other exception" <<endl;
        return 1;
    }

    cout<< "done go!" <<endl;
    try{
//    hl.addTable(hl.COARSE);
        hl.addPoints();
}catch (std::exception xx){
    cout<< "Error: " << xx.what() <<endl;
    return 1;
}catch (...){
    cout<<"error some other exception" <<endl;
    return 1;
}
hl.addTable(400);
    hl.addPoints();
cout<<"done convert" <<endl;
long maxhits = hl.freqTables[sz].maxHits;
cout<< "maxHits for " << sz <<" is "<< maxhits<<endl;
   long fdiff = maxhits>1?maxhits-1: 1; //maxx -minn;
    double bg[] ={0.0,0.0,0.0,.2};
    double min[]= {0.0,0.0,1,0.5};
    double max[] = {1,1,0.0,1.0};

 //  PaintIcon paintIcon(sz,sz,bg,min,max,&hl);
    PaintIcon paintIcon(sz,sz,bg,min,max,&hl,&testColourFn);
    //paintIcon.setUseAlpha(false);
    paintIcon.paint();

    std::cout << "After painting complete. "  << '\n';


    std::time_t result = std::time(nullptr);
    const std::string ddate = to_string(result).data();
    std::string  fnBase= "img_a_";
    string dname = fnBase+ddate + ".sym";
    std::ofstream outy(dname,std::ios_base::out);
    outy<< hl;
    outy.flush(); outy.close();

    cout<< hl.rawSize() << " "<< maxhits <<endl;
    cout << "Done!" << endl;
//    HitList newHL (100,hl);
 //   cout<<"nnewHL numPoints=" <<newHL.numPoints <<endl;
/****************
     surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 100, 100);
    cr = cairo_create (surface);
    cairo_set_line_width (cr, 1);
    cairo_set_source_rgb (cr, 1,1,1);
    cairo_paint (cr);
    newHL.getPoints((Dim2Pixel**)&points, &minn, &maxx);
    cout<<"got maxx " <<maxx << " got minn " <<minn <<"num points " <<newHL.numPoints <<endl;
    fdiff = maxx -minn;

    for(int i=0;i<newHL.numPoints;i++ ) {

        int x = (points + i)->x;
        int y = ((points + i)->y);
        int hits = 1;
        //   cout << "looking for " << (points+i)->x <<" "<< (points+i)->y <<endl;
        PointFrequency::const_iterator pp = newHL.hitPointList.find(*(points + i));
        if (pp != newHL.hitPointList.cend()) {
            hits = pp->second;
            //       cout<< "found!! " <<hits <<endl;
        }
        //  cout << "maxhits " <<maxhits <<endl;HitList.h:46:10: note:   candidate expects 3 arguments, 1 provided
        double opacity = (double) (hits - minn) / fdiff;
           cout <<"opacity " << opacity <<endl;
//opacity=0.3*opacity;
        /*********
        cairo_set_source_rgba(cr, 0.5, 0.95 * (opacity), .9 * opacity, 0.7 + 0.3 * opacity);
        cairo_move_to(cr, x, y + 0.5);
        cairo_line_to(cr, x + 0.5, y + 0.5);
        cairo_stroke(cr);
         ************/
  //  }
   // cairo_surface_write_to_png (surface, "/home/peter/img_b.png");

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
    