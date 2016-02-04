#ifndef LAYER_H
#define LAYER_H

#include <Eigen/Dense>
#include "functions.h"

class Layer
{
    public:
        Layer(int nNeurons, int nInput);
        ~Layer();

        //Feed forward step
        void FeedForward(Eigen::VectorXd const& input);

        //Feed backward for last layer
        void FeedBackward(Eigen::VectorXd delta);
        //Feed backward for hidden layers
        void FeedBackward(Eigen::MatrixXd w, Eigen::VectorXd delta);

        //Compute _nabla_w and _nabla_b
        void ComputeNabla(Eigen::VectorXd activations);
        //Set all values of _nabla_w and _nabla_b to 0
        void CleanNabla();

        //Update weights and biases
        void UpdateWeightsBiases(double eta, int miniBatchSize);


        //Accessors
        Eigen::VectorXd GetActivation();
        Eigen::MatrixXd GetWeights();
        Eigen::VectorXd GetDelta();

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
        //Intermediate value useful for calcultaions: derivative of cost
        //error with respect to weighted input
        Eigen::VectorXd _delta;
        //Sum of partial derivatives of the cost function with respect to
        //_biases
        Eigen::VectorXd _nabla_b;
        //Sum of partial derivatives of the cost function with respect to
        //_weights
        Eigen::MatrixXd _nabla_w;
        //Activation function
        Function * _activationFunction;

        //Initialize weights and biaises
        void InitWeightsBiases();

};

#endif
