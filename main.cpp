#include <iostream>
#include <fstream>
#include <vector>

#include "DataMnist.h"
#include "layer.h"
#include "network.h"

using namespace std ;

int main(int argc, char const *argv[])
{
	//Check number of arguments: you should pass as argument the directory where
    //the MNIST database is stored
	if (argc != 2)
	{
		cerr << "Pass MNIST database directory as argument" << endl;
		return 1;
	}

    //Create DataMnist instance
	DataMnist database(argv[1]);
    //Load labels
	if (database.loadLabels(0) == 1)
	{
        //If an error occured, exit program
		return 1;
	}
    //Load images
    if (database.loadImages(0) == 1)
    {
        //If an error occured, exit program
        return 1;
    }


    //Create vector of sizes for our Network
    vector<int> sizes(3);
    sizes[0] = 784; sizes[1] = 30; sizes[2] = 10;
    //Initialize the network
    Network network(sizes);

    
    //Initialize total number of epochs
    int nEpochs = 30;
    for (int epochs = 0; epochs < nEpochs; ++epochs)
    {
        //TRAIN NETWORK
        //It is possible to pass extra arguments to the Train function in order to
        //optimize training. These parameters are:
        //  - nEpochs : number of repetition of learning cycles (without printing
        //  error rate throughout the learning process)
        //  - miniBatchSize: size of minibatches
        //  - eta: learning parameter. The lower eta, the slower and more precise
        //  the training.
        network.Train(database.GetTrainImages(), database.GetTrainLabels(), 1);

        //Compute number of errors
        double errors(0);
        for (int i = 0; i < 10000; ++i) {
            if (network.Predict(database.testImage(i)) != database.testLabel(i)) 
            {
                errors++;
            }
        }
        cout << "Epoch " << epochs << " completed." << endl;
        cout << "Errors: " << errors / 100.0 << "%" << endl;
    }

	//For windows :)
	cin.get();
}
