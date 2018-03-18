//
// Created by peter on 2/04/17.
// Wrapper for painting generated data.
//

#ifndef SYMICON_PAINTICON_H
#define SYMICON_PAINTICON_H

#include <cairo.h>
#include "PointList.h"

using namespace emu::utility;
namespace emu {
    namespace symicon {

        static void simpleColourFn(double *minRGBA, double *maxRGBA, long hits, FrequencyData &fd,
                                   double *rgbaOut);
    class PaintIcon {
        int xSz, ySz; //Dimensions
        double *bgRGBA;
        double *minRGBA;
        double *maxRGBA;
        PointList *pointList;
        bool useAlpha = false;



    public:
        typedef void (*ColourFn)(double min[4], double max[4], long frequency, FrequencyData &pointList,
                                 double *rgbaOut); //calculate RGBA to colourise frequency

        PaintIcon(int xSz, int ySz, double *bgRGBA, double *minRGBA, double *maxRGBA, PointList *pointList,
                 ColourFn colourFn );

        PaintIcon(int xSz, int ySz, double *bgRGBA, double *minRGBA, double *maxRGBA, PointList *pointList);

        ColourFn colourFn = 0;
        void paintPoint(cairo_t *cr, int x, int y, const double *rgba) const;
        void paint();
        void saveImage();
        void showImage();
        void setUseAlpha(bool use){useAlpha = use;}

       // static ColourFn simpleColourFn;
    };

}
}
#endif //SYMICON_PAINTICON_H
