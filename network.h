#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <valarray>
#include <Eigen/Dense>

#include "layer.h" 

class Network
{
public:
	//Constructeur
	Network(std::vector<int> const& sizes);
	//Destructeur
	~Network();

	//Fonction de classification pour une image
	int Predict(Eigen::VectorXd const& X);

	//Fonction d'apprentissage
	void train(std::vector< Eigen::VectorXd>  const& X, std::vector<int> const& Y);

private:
    //Vector of pointers to layers
    std::vector<Layer *> _layers;
    //Sizes of layers
    std::vector<int> _sizes;
	
};


#endif
