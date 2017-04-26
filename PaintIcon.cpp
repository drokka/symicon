//
// Created by peter on 2/04/17.
//

#include "PaintIcon.h"

#include <ctime>
#include <fstream>


emu::symicon::PaintIcon::PaintIcon(int xSz, int ySz, double *bgRGBA, double *minRGBA, double *maxRGBA, PointList *pointList,
          ColourFn colourFn ) : xSz(xSz), ySz(ySz), bgRGBA(bgRGBA),
                                                              minRGBA(minRGBA), maxRGBA(maxRGBA),
                                                              pointList(pointList), colourFn(colourFn) {

}

emu::symicon::PaintIcon::PaintIcon(int xSz, int ySz, double *bgRGBA, double *minRGBA,
                                   double *maxRGBA, PointList *pointList)
        : xSz(xSz), ySz(ySz), bgRGBA(bgRGBA), minRGBA(minRGBA), maxRGBA(maxRGBA), pointList(pointList),
          colourFn(emu::symicon::simpleColourFn) {

}
void emu::symicon::PaintIcon::paint() {

    cairo_format_t cairoFormat;
    if(useAlpha){
        cairoFormat=CAIRO_FORMAT_ARGB32;
    }
    else {
        cairoFormat=CAIRO_FORMAT_RGB30;
    }
    cairo_surface_t *surface = cairo_image_surface_create (cairoFormat, xSz, ySz);
    cairo_t *cr = cairo_create (surface);
    if(useAlpha){
        cairo_set_source_rgba(cr,bgRGBA[0],bgRGBA[1],bgRGBA[2], bgRGBA[3]);
    }
    else
    {
        cairo_set_source_rgb(cr,bgRGBA[0],bgRGBA[1],bgRGBA[2]);

    }
    cairo_save(cr);
    cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
    if(!useAlpha) {
        cairo_paint(cr);
    }else{
        cairo_paint_with_alpha(cr, bgRGBA[3]);
    }
    cairo_restore(cr);


    emu::utility::FrequencyList2DConstIter iter = pointList->freqTables[xSz].frequencyList->begin();

    while(iter != pointList->freqTables[xSz].frequencyList->end()){
        int x= iter->first.val[0]; //(points+i)->x;
        int y= iter->first.val[1]; //((points+i)->y);
        long hits = iter->second;
        //   cout << "looking for " << x <<" "<< y <<" " << hits <<endl;
        /*****
    PointFrequency::const_iterator pp = pointList->hitPointList.find(*(points+i));
    if(pp!= pointList->hitPointList.cend())
    {
         hits = pp->second;
  //       cout<< "found!! " <<hits <<endl;
    }
         ******************/
        double rgba[] ={0,0,0,0};
        FrequencyData fd = pointList->freqTables[xSz];
        colourFn(minRGBA, maxRGBA, hits, fd, rgba);
        paintPoint(cr, x, y, rgba);
        iter++;
    }

    std::time_t result = std::time(nullptr);
    const std::string ddate = to_string(result).data();
    std::string  fnBase= "img_a_";
    string ext = ".png";
    string fname= fnBase  +std::to_string(xSz)+ "_" + ddate + ext;
    //
    //fn.append(ddate).append(".png");
    cairo_surface_write_to_png (surface, fname.c_str());

    cairo_destroy (cr);
    cairo_surface_destroy (surface);

}

void emu::symicon::PaintIcon::paintPoint(cairo_t *cr, int x, int y, const double *rgba) const {
    if(useAlpha){
        cairo_set_source_rgba (cr, rgba[0], rgba[1], rgba[2], rgba[3] );
    }
    else{
        cairo_set_source_rgb (cr, rgba[0], rgba[1], rgba[2]);

    }
    //     cairo_set_source_rgb (cr, 0.2, 0.95, .9);
    cairo_move_to (cr, x, y+0.5);
    cairo_line_to (cr, x+0.5, y+0.5);
    cairo_stroke (cr);
}

static void emu::symicon::simpleColourFn(double *minRGBA, double *maxRGBA, long hits, FrequencyData &fd,
                                                    double *rgbaOut) {
    long maxhits = fd.maxHits;
    // cout<< "maxHits for " << sz <<" is "<< maxhits<<endl;
    long fdiff = maxhits>1?maxhits-1: 1; //maxx -minn;

    //  cout << "maxhits " <<maxhits <<endl;
    double opacity = (double)(hits - 1)/fdiff;
    //   cout <<"opacity " << opacity <<endl;std::max(
//opacity=0.3*opacity;
    //bound opacity between 0 and 1.
    opacity = (opacity <= 0)?0.05:opacity;
    opacity = (opacity >1)?1:opacity;
 rgbaOut[0]= 0.5 +0.5*opacity;
    rgbaOut[1]=  .9*opacity;
    rgbaOut[2]= 0.3 +0.7*opacity;
    rgbaOut[3]=opacity;
}

void emu::symicon::PaintIcon::saveImage() {}

void emu::symicon::PaintIcon::showImage() {}