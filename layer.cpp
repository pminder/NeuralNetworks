#include <random>
#include <iostream>

#include "layer.h"

using namespace std;
using namespace Eigen;

Layer::Layer(int nNeurons, int nInput)
{
    //Store nNeurons and nInput
    _nNeurons = nNeurons;
    _nInput = nInput;
    //Allocate attributes
    _biases = VectorXd(_nNeurons);
    _weights = MatrixXd(_nNeurons, _nInput);
    _weightedInput = VectorXd(_nNeurons);
    _activation = VectorXd(_nNeurons);
    //Activation function creation
    _activationFunction = new Sigmoid;

    //Initialize weights and biases using random normal distribution
    InitWeightsBiases();
    
}

Layer::~Layer()
{
}

void Layer::InitWeightsBiases()
{
    //Initialize random number generator
    default_random_engine generator;
    normal_distribution<double> distribution(0.0,1.0);
    //Fill biases
    for (int i = 0; i < _nNeurons; ++i) {
        _biases(i) = distribution(generator);
    }
    //Fill weights
    for (int i = 0; i < _nNeurons; ++i) {
        for (int j = 0; j < _nInput; ++j) {
            _weights(i, j) = distribution(generator);
        }
    }
}


void Layer::FeedForward(VectorXd const& input)
{
    //Compute weighted inputs for this layer
    _weightedInput = _weights * input + _biases;
    //Compute activation for this layer
    for (int i = 0; i < _nNeurons; ++i) {
        _activation(i) = _activationFunction->fnt(_weightedInput(i));
    }

}

VectorXd Layer::GetActivation()
{
    return _activation;
}
