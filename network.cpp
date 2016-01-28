#include <iostream>
#include "network.h"

using namespace std;
using namespace Eigen;

Network::Network(vector<int> const& sizes)
{
    //Create Layers
    for (int i = 1; i < sizes.size(); ++i) {
        Layer * p_layer(0);
        p_layer = new Layer(sizes[i], sizes[i-1]);
        _layers.push_back(p_layer);
    }

    //Store sizes vector
    _sizes = sizes;

}

Network::~Network()
{
    for (int i = 0; i < _layers.size(); ++i) {
        delete _layers[i];
    }

}

int Network::Predict(VectorXd const& X)
{
    int label(-1);

    //Feedforward X in first layer
    _layers[0]->FeedForward(X);
    //For all other layers
    for (int i= 1; i< _layers.size(); ++i) {
        _layers[i]->FeedForward(_layers[i-1]->GetActivation());
    }

    //Get label with highest probabilty
    (_layers[_layers.size()-1]->GetActivation()).maxCoeff(&label);
    //Return number with label with highest probability
    return label;
}

//IDEE : surcharge d'opérateur pour gérer les cas où l'on passe 
//une ou plusieurs images à predict...
//void Network::predict(vector< Eigen::VectorXd>  const& X)
//{
//
//}

void Network::train(vector< Eigen::VectorXd> const& X, vector<int> const& Y)
{

}
