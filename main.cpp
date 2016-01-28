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
	if (database.loadLabels(1) == 1)
	{
		return 1;
	}
    //Load images
    if (database.loadImages(1) == 1)
    {
        return 1;
    }

    cout << network.Predict(database.testImage(55)) << endl;

	//For windows :)
	cin.get();
}
