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
    _delta = VectorXd(_nNeurons);
    _nabla_b = VectorXd(_nNeurons);
    _nabla_w = MatrixXd(_nNeurons, _nInput);
    //Activation function creation
    _activationFunction = new Sigmoid;

    //Initialize weights and biases using random normal distribution
    InitWeightsBiases();
    
}

Layer::~Layer()
{
    delete _activationFunction;
}

void Layer::InitWeightsBiases()
{
    //Initialize random number generator
    default_random_engine generator;
    normal_distribution<double> distribution(0.0,1.0);
    //Fill biases and set _nabla_b to 0
    for (int i = 0; i < _nNeurons; ++i) {
        _biases(i) = distribution(generator);
        _nabla_b(i) = 0;
    }
    //Fill weights and set _nabla_w to 0
    for (int i = 0; i < _nNeurons; ++i) {
        for (int j = 0; j < _nInput; ++j) {
            _weights(i, j) = distribution(generator);
            _nabla_w(0, 0) = 0;
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

MatrixXd Layer::GetWeights()
{
    return _weights;
}

VectorXd Layer::GetDelta()
{
    return _delta;
}

void Layer::FeedBackward(VectorXd delta)
{
    //Using equation (BP1), compute _delta^L
    for (int i = 0; i < _weightedInput.size(); ++i) {
        _delta(i) = _activationFunction->prime(_weightedInput(i)) * delta(i);
    }
}

void Layer::FeedBackward(MatrixXd w, VectorXd delta)
{
    //Using equation (BP2), compute _delta^l
    VectorXd temp = w.transpose() * delta;
    for (int i = 0; i < _weightedInput.size(); ++i) {
        _delta(i) = _activationFunction->prime(_weightedInput(i)) * temp(i);
    }
}

void Layer::ComputeNabla(VectorXd activations)
{
    //Add _delta to _nabla_b
    _nabla_b += _delta;

    //Add nabla_w to _nabla_w
    _nabla_w += _delta * activations.transpose();
}

void Layer::CleanNabla()
{
    //Set _nabla_b to 0
    _nabla_b -= _nabla_b;

    //Set _nabla_w
    _nabla_w -= _nabla_w;
}

void Layer::UpdateWeightsBiases(double eta, int miniBatchSize)
{
    _weights -= (eta/miniBatchSize) * _nabla_w;
    _biases -= (eta/miniBatchSize) * _nabla_b;
}
