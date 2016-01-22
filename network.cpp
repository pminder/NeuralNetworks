#include "network.h"

using namespace std;

Network::Network(vector<int> const& sizes)
{
    for (int i = 1; i < sizes.size(); ++i) {
        Layer * p_layer(0);
        p_layer = new Layer(sizes[i], sizes[i-1]);
        _layers.push_back(p_layer);
    }

}

Network::~Network()
{
    for (int i = 0; i < _layers.size(); ++i) {
        delete _layers[i];
    }

}

void Network::predict(vector< valarray<float> > const& X)
{

}

void Network::train(vector< valarray<float> > const& X, vector<char> const& Y)
{

}
