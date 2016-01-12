#ifndef FUNCTIONS_H
#define FUNCTIONS_H 

#include <string>

//Classe abstraite Fonction
class Function
{
public:
	Function();
	virtual ~Function();

	//Fonction de base
	virtual float fnt(float x) const = 0;
	//Dérivée
	virtual float prime(float x) const = 0;

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

	virtual float fnt(float x) const;
	virtual float prime(float x) const;
	
};

#endif