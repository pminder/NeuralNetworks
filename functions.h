#ifndef FUNCTIONS_H
#define FUNCTIONS_H 

#include <string>
#include <math>

//Classe abstraite Fonction
class Function
{
public:
	Function();
	virtual ~Function();

	//Fonction de base
	virtual double fnt(double x) const = 0;
	//Dérivée
	virtual double prime(double x) const = 0;

protected:
	//Nom de la fonction (pour l'affichage)
	std::string name;
	
};

//La classe Sigmoid hérite de la classe fonction
//mais celle-ci n'est pas abstraite
class Sigmoid : public Function
{
public:
	Sigmoid();
	~Sigmoid();

	virtual double fnt(double x) const;
	virtual double prime(double x) const;
	
};

#endif
