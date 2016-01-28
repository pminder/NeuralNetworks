#include <iostream>
#include <algorithm>
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

void Network::Train(vector< Eigen::VectorXd> const& X, vector<int> const& Y, 
        int epochs, int miniBatchSize, double eta)
{
    //shortcut to number of training data
    int n = X.size();
    //Index of elements
    vector<int> index(n);
    for (int i = 0; i < n; ++i) {
        index[i] = i;
    }

    //For each epoch
    for (int j = 0; j < epochs; ++j) {
        //Set all nabla values to 0 for each layer
        for (int iLayer = 0; iLayer < _layers.size(); iLayer++) {
            _layers[iLayer]->CleanNabla();
        }
        //Shuffle index
        random_shuffle(index.begin(), index.end());
        for (int k = 0; k < n; k+=miniBatchSize) {
            //Create minibatch
            vector<VectorXd> xMiniBatch(miniBatchSize);
            vector<int> yMiniBatch(miniBatchSize);
            for (int i = 0; i < miniBatchSize; ++i) {
                xMiniBatch[i] = X[index[k + i]];
                yMiniBatch[i] = Y[index[k + i]];
            }
            //Update weights and biases
            UpdateMiniBatch(xMiniBatch, yMiniBatch, eta);
        }

        cout << "Epoch n°" << j << " completed" << endl;
    }
}

void Network::UpdateMiniBatch(vector<VectorXd> x, vector<int> y, double eta)
{
    //Shortcut to number of layers
    int nLayers = _layers.size();
    //for each training data in minibatch
    for (int i = 0; i < y.size(); ++i) {
        //Perform feed forward step
        Predict(x[i]);
        //Compute value of delta
        VectorXd delta = InitBackProp(y[i], _layers[nLayers -1]->GetActivation());
        _layers[nLayers-1]->FeedBackward(delta); //Use equation (BP1)
        for (int j = nLayers - 2; j >= 0; --j) {
            //Use equation (BP2)
            _layers[j]->FeedBackward(_layers[j+1]->GetWeights(), _layers[j+1]->GetDelta());
        }

        _layers[0]->ComputeNabla(x[i]); 
        for (int j = 1; j < nLayers; ++j) {
            //Use equations (BP3) + (BP4)
            _layers[j]->ComputeNabla(_layers[j-1]->GetActivation()); 
        }
    }

    //Update weights and biases
    for (int l = 0; l < nLayers; ++l) {
        _layers[l]->UpdateWeightsBiases(eta, y.size());
    }
}

VectorXd Network::InitBackProp(int y, VectorXd activations)
{
    //Get number of possible labels (for MNIST n = 10)
    int n = _sizes[_sizes.size()-1];

    //Vectorize y
    VectorXd vectorizedY(n);
    //Initialize all values to 0.0
    for (int i = 0; i < n; ++i) {
        vectorizedY(i) = 0.0;
    }
    //Set yth value to 1.0
    vectorizedY(y) = 1.0;

    return activations - vectorizedY;
}


