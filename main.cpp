#include <iostream>
#include <fstream>
#include <vector>

#include "DataMnist.h"
#include "layer.h"
#include "network.h"

using namespace std ;

int main(int argc, char const *argv[])
{
	//Check number of arguments
	if (argc != 2)
	{
		cerr << "Pass MNIST database directory as argument" << endl;
		return 1;
	}

    //Create vector of sizes for our Network
    vector<int> sizes(3);
    sizes[0] = 784; sizes[1] = 30; sizes[2] = 10;
    //Initialize the network
    Network network(sizes);


   //Create dataloader instance
	DataMnist database(argv[1]);
    //Load labels
	if (database.loadLabels(0) == 1)
	{
		return 1;
	}
    //Load images
    if (database.loadImages(0) == 1)
    {
        return 1;
    }


    //Train network
    network.Train(database.GetTrainImages(), database.GetTrainLabels());


    return 0;

    //Compute number of errors
    double errors(0);
    for (int i = 0; i < 10000; ++i) {
        if (network.Predict(database.testImage(i)) != database.testLabel(i)) 
        {
            errors++;
        }
    }

    cout << "Errors: " << errors / 100.0 << "%" << endl;

	//For windows :)
	cin.get();
}
