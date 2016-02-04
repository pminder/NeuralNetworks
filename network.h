#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <Eigen/Dense>

#include "layer.h" 

class Network
{
public:
	Network(std::vector<int> const& sizes);
	~Network();

	//Classification function for one image
	int Predict(Eigen::VectorXd const& X);

	//Training function
	void Train(std::vector< Eigen::VectorXd>  const& X, std::vector<int> const& Y,
            int epochs = 30, int miniBatchSize = 10, double eta = 3.0);

    //Update weights and biases using specified minibatch
    void UpdateMiniBatch(std::vector<Eigen::VectorXd> x, std::vector<int> y, double eta);

    //Compute first value used in backpropagation algorithm
    Eigen::VectorXd InitBackProp(int y, Eigen::VectorXd activations);


private:
    //Vector of pointers to layers
    std::vector<Layer *> _layers;
    //Sizes of layers
    std::vector<int> _sizes;
	
};


#endif
