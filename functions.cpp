#include "functions.h"
#include <iostream>

Function::Function()
{

}

Function::~Function()
{

}


Sigmoid::Sigmoid()
{

}

Sigmoid::~Sigmoid()
{

}


double Sigmoid::fnt(double x) const
{
    return 1./(1 + exp(-x));
}

double Sigmoid::prime(double x) const
{
    double t =  ( exp(-x)/( 1.+ exp(-x)) ) * ( 1./(1. + exp(-x)));
    if (t != t) 
    {
        return 0.;
    }
    return t;
}
