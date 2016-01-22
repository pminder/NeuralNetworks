#include "network.h"

using namespace std;

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

gsl_vector * Network::Predict(int rawInput[])
{
    gsl_vector * p_input;
    gsl_vector * p_output;

    //Create fisrt input vector
    p_input = gsl_vector_calloc(_sizes[0]);
    //Copy data into vector
    for (int i = 0; i < _sizes[0]; ++i) {
        gsl_vector_set(p_input, i, rawInput[i]);
    }

    for (int i = 0; i < _layers.size(); ++i) {
        p_output = _layers[i].FeedForward(p_input);
        gsl_vector_free(p_input);
        p_input = p_output;
    }

    return p_output;
}

//IDEE : surcharge d'opérateur pour gérer les cas où l'on passe 
//une ou plusieurs images à predict...
void Network::predict(vector< valarray<float> > const& X)
{

}

void Network::train(vector< valarray<float> > const& X, vector<char> const& Y)
{

}
