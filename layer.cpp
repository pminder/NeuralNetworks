#include "layer.h"
#include <random>
#include <iostream>

using namespace std;

Layer::Layer(int const nNeurons, int const nInput)
{
    //Store nNeurons and nInput
    _nNeurons = nNeurons;
    _nInput = nInput;
    //Allocate biases
    _biases = gsl_vector_calloc(_nInput);
    _weights = gsl_matrix_calloc(_nNeurons, _nInput);

    InitLayer();
    
}

Layer::~Layer()
    //Let's not forget to free memory :)
{
    gsl_vector_free(_biases);
    gsl_matrix_free(_weights);
}

void Layer::InitLayer()
{
    //Initialize random number generator
    default_random_engine generator;
    normal_distribution<double> distribution(0.0,1.0);
    //Fill biases
    for (int i = 0; i < _nInput; ++i) {
        gsl_vector_set(_biases, i, distribution(generator));
    }
    //Fill weights
    for (int i = 0; i < _nNeurons; ++i) {
        for (int j = 0; j < _nInput; ++j) {
            gsl_matrix_set(_weights, i, j, distribution(generator));
        }
    }
}


//TODO
gsl_vector * Layer::FeedForward(gsl_vector * input)
{
    return ???;
}
