#ifndef LAYER_H
#define LAYER_H

#include <Eigen/Dense>
#include "functions.h"

class Layer
{
    public:
        //Constructor: 
        //args:
        //  - nNeurons: number of neurons in layer
        //  - nInput: number of neurons in previous layer
        Layer(int nNeurons, int nInput);

        //Destructor:
        ~Layer();
        //Feed forward step
        void FeedForward(Eigen::VectorXd const& input);

        //Accessors
        //(OPTIMIZATION: do not copy ?)
        Eigen::VectorXd GetActivation();

    private:
        //Attributes
        int _nNeurons;
        int _nInput;
        //Weights
        Eigen::MatrixXd  _weights;
        //Biases
        Eigen::VectorXd _biases;
        //Weighted input
        Eigen::VectorXd _weightedInput;
        //Layer activation
        Eigen::VectorXd _activation;

        //Activation function
        Function * _activationFunction;

        //Initialize weights and biaises
        void InitWeightsBiases();

};

#endif
