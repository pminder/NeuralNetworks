#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <valarray>

#include "layer.h" 

class Network
{
public:
	//Constructeur
	Network(std::vector<int> const& sizes);
	//Destructeur
	~Network();

	//Fonction de classification
	//Pour l'instant la matrice X est un tableau de valarrays
	//(valarray étant un type approprié en C++ pour des opérations
	//vectorielles)
	void predict(std::vector< std::valarray<float> > const& X);

	//Fonction d'apprentissage
	//Attention, Y est constitué de char (et non de ints). C'est suffisant
	//car on ne dépasse pas 9... Mais cela pourrait nous induire en erreur?
	void train(std::vector< std::valarray<float> > const& X, std::vector<char> const& Y);

private:
    //Vector of pointers to layers
    std::vector<Layer *> _layers;
    //Sizes of layers
    vector<int> _sizes;
	
};


#endif
