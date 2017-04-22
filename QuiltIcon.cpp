//
// Created by peter on 10/05/15.
//

#include <math.h>
#include "QuiltIcon.h"

using namespace emu::symicon;

double QuiltIcon::pi = acos(-1);
double QuiltIcon::p2 = 2 * pi;

void QuiltIcon::generate1(double inputPoint[], double lambda, double alpha, double beta,
                          double gamma, double omega, double ma) {

    double shift, sx, sy;

    double xnew;
    double ynew;

    double x = inputPoint[0];
    double y = inputPoint[1];

    shift = 0;
    sx = sin(p2 * x);
    sy = sin(p2 * y);

    xnew = (lambda + alpha * cos(p2 * y)) * sx - omega * sy + beta * sin(2 * p2 * x) +
           gamma * sin(3 * p2 * x) * cos(2 * p2 * y) + ma * x + shift;
    ynew = (lambda + alpha * cos(p2 * x)) * sy + omega * sx + beta * sin(2 * p2 * y) +
           gamma * sin(3 * p2 * y) * cos(2 * p2 * x) + ma * y + shift;

    if (xnew > 1) {
        xnew = xnew - (int) (xnew);
    }
    else {
        if (xnew < 0) xnew = xnew + (int) (-xnew) + 1;
    }
    if (ynew > 1) {
        ynew = ynew - (int) (ynew);
    }
    else {
        if (ynew < 0) ynew = ynew + (int) (-ynew) + 1;
    }

    inputPoint[0] = xnew;
    inputPoint[1] = ynew;
}

/**************
void QuiltIcon::setParameters(double *const pDouble) {

    if (pDouble != nullptr) {
        lambda = *pDouble;
    }
    if (pDouble != nullptr) {
        alpha = *(pDouble + 1);
    }
    if (pDouble != nullptr) {
        beta = *(pDouble + 2);
    }
    if (pDouble != nullptr) {
        gamma = *(pDouble + 3);
    }
    if (pDouble != nullptr) {
        omega = *(pDouble + 4);
    }
    if (pDouble != nullptr) {
        ma = *(pDouble + 5);

    }

}
****************************/

/************
QuiltIcon::QuiltIcon() : Icon(6, 0) {
    pi = acos(-1); p2 = 2*pi;

    genFunc = &(QuiltIcon::generate1);
}

QuiltIcon::QuiltIcon(int numberParameters) : Icon(numberParameters, 0) {
    pi = acos(-1); p2 = 2*pi;

    genFunc = &(QuiltIcon::generate1);
}

QuiltIcon::QuiltIcon(const std::tuple<Params ...> &parameters) : IterativeFunctionBase(parameters) {

}
 ***********/
/*******
void QuiltIcon::operator()(double *input, double **output) {
    IterativeFunctionBase::operator()(input, output);
}

void QuiltIcon::UnrolledFunction(std::tuple &tuple, double *input, double **output) {
    generate1((std::get<0>(tuple)., )
}
*****************/

void QuiltIcon::iterFunction(double *input, Parameter<double> lambda, Parameter<double> alpha,
                             Parameter<double> beta,Parameter<double> gamma,Parameter<double> omega,Parameter<double> ma) {

    generate1(input, lambda.getValue(), alpha.getValue(), beta.getValue(), gamma.getValue(),
              omega.getValue(), ma.getValue());
}

void QuiltIcon::setValue(double _lambda, double _alpha, double _beta, double _gamma, double _omega, double _ma) {
    std::get<0>(stored_inputs)->setValue(_lambda);

    std::get<1>(stored_inputs)->setValue(_alpha);
    std::get<2>(stored_inputs)->setValue(_beta);
    std::get<3>(stored_inputs)->setValue(_gamma);
    std::get<4>(stored_inputs)->setValue(_omega);

    std::get<5>(stored_inputs)->setValue(_ma);
}
