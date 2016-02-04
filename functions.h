#ifndef FUNCTIONS_H
#define FUNCTIONS_H 

#include <string>
#include <math.h>

//Abstract class function
class Function
{
public:
	Function();
	virtual ~Function();

	//Function
	virtual double fnt(double x) const = 0;
	//Derivative function
	virtual double prime(double x) const = 0;
	
};

//Sigmoid class inherits from Function
class Sigmoid : public Function
{
public:
	Sigmoid();
	~Sigmoid();

	virtual double fnt(double x) const;
	virtual double prime(double x) const;
	
};

#endif
