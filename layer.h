#ifndef LAYER_H
#define LAYER_H

#include <gsl/gsl_matrix.h>

class Layer
{
    public:
        //Constructor: 
        //args:
        //  - nNeurons: number of neurons in layer
        //  - nInput: number of neurons in previous layer
        Layer(int const nNeurons, int const nInput);

        //Destructor:
        //DO NOT FORGET TO FREE MEMORY
        ~Layer();

    private:
        //Attributes
        int _nNeurons;
        int _nInput;
        gsl_matrix * _weights;
        gsl_vector * _biases;

        //Initialize weights and biaises
        void InitLayer();

};

#endif
