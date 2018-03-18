//
// Created by peter on 30/06/17.
//

#ifndef SYMICON_SYMICONAPP_H
#define SYMICON_SYMICONAPP_H


#include "QuiltIcon.h"

#include "Generator.h"
#include "PaintIcon.h"

using namespace emu::symicon;

namespace emu {
    namespace symicon {

        class SymIconApp {
        public:
            SymIconApp(long iterations, double initX, double initY, QuiltIcon::QuiltType type, string fnBase,
                       int sz, double *iconParams, int numIconParams, double *bgColour, double *minColour,
                       double *maxColour, PaintIcon::ColourFn colourFn);


        private:

            long iterations = 100000;
            PointList hl;
            int sz = 1600;

            QuiltIcon::QuiltType type = QuiltIcon::QuiltType::SQUARE;
            double *iconParams;
            int numIconParams;
            double lambdaVal;
            double alphaVal;
            double betaVal;
            double gammaVal;
            double omegaVal;
            double maVal;
            /*******  pp.aA=2; pp.bB=0; pp.gG=1; pp.oO=0.01;
             pp.degreeSym=4; pp.scale=1;
             pp.lL=-1.8; ****/

            //-1.830826997756958</lL><aA>2.8900375366210938</aA><bB>-2.312030076980591</bB>
            // <gG>2.231203079223633</gG><oO>0.06578969955444336</oO><degreeSym>3</degreeSym><scale>8</scale>

            QuiltIcon *qi;
            Generator *gg;
            Point2D initPoint;


            double bg[];
            double min[];
            double max[];

            PaintIcon paintIcon;

            //paintIcon.setUseAlpha(false);

            std::string fnBase = "img_a_";

        public:
            void runGenerator();

            void paint();

            long fdiff;
            long maxhits;
        };
    }
}

#endif //SYMICON_SYMICONAPP_H
