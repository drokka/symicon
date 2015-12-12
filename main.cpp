#include <iostream>
#include <map>
#include "QuiltIcon.h"

#include "Generator.h"
#include <cairo.h>

using namespace std;
using namespace emu::symicon;

int main(int nparam, char** param) {

    int sz=800;
    long iterations = 100000;

    if(nparam == 3){
        sz = stoi(param[1]);
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

    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, sz, sz);
    cairo_t *cr = cairo_create (surface);
    cairo_set_line_width (cr, 1);
    cairo_set_source_rgb (cr, 0,0,0);
    cairo_paint (cr);
  //  cairo_set_operator (cr, CAIRO_OPERATOR_SOURCE);

    QuiltIcon qi(0.6,0.2,0.3,0.4,0.2,0.3, sz, sz);

    qi.setSz(sz, sz);


    PointList hl;
    Generator gg(&qi,iterations, &hl);
    gg.go(Point2D(.7,.53));

long maxhits = hl.freqTables[hl.COARSE]->maxHits;

   long fdiff = maxhits -1 ; //maxx -minn;

    PointList::FrequencyList2DConstIter iter = hl.freqTables[hl.COARSE]->frequencyListPtr->begin();

        while(iter != hl.freqTables[hl.COARSE]->frequencyListPtr->end()){
        int x= iter->first.val[0]; //(points+i)->x;
        int y= iter->first.val[1]; //((points+i)->y);
        long hits = iter->second;
     //   cout << "looking for " << (points+i)->x <<" "<< (points+i)->y <<endl;
            /*****
        PointFrequency::const_iterator pp = hl.hitPointList.find(*(points+i));
        if(pp!= hl.hitPointList.cend())
        {
             hits = pp->second;
      //       cout<< "found!! " <<hits <<endl;
        }
             ******************/
      //  cout << "maxhits " <<maxhits <<endl;
        double opacity = (double)(hits - 1)/fdiff;
     //   cout <<"opacity " << opacity <<endl;
//opacity=0.3*opacity;
        opacity = (opacity <= 0)?1:opacity;
        opacity = (opacity >1)?1:opacity;
        cairo_set_source_rgba (cr, 0.2, 0.95*opacity, .9,opacity);
        cairo_move_to (cr, x, y+0.5);
        cairo_line_to (cr, x+0.5, y+0.5);
        cairo_stroke (cr);
        iter++;
    }

  //  std::cout << "After painting complete. " <<t << '\n';


 //   cout<<"numPoints=" <<hl.numPoints <<endl;


    cairo_surface_write_to_png (surface, "/home/peter/img_a.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

/*   hl.updateFrequencyTable();
    long * freqs = hl.getDataFrequencies();
    for(int i=0;i<100;i++){
        cout << *(freqs+i) << " " ;

    }
    */

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
    