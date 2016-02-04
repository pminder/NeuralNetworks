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
    return ( exp(-x)/( 1.+ exp(-x)) ) * ( 1./(1. + exp(-x)));
}
