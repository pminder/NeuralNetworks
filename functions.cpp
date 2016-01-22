#include "functions.h"

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
    1./(1 + exp(-x));
}

double Sigmoid::prime(double x) const
{
    exp(-x)/((1 + exp(-x))*(1 + exp(-x)));
}
