#include <iostream>
#include <fstream>
#include <vector>
//#include <stdio.h>
//#include <stdlib.h>
//#include <gsl/gsl_matrix.h>

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

//    //Test if allocation and destruction of Network works
//    vector<int> sizes(3);
//    sizes[0] = 200;
//    sizes[1] = 30;
//    sizes[2] = 10;
//
//    Network network(sizes);
//    Layer * p_layer = network._layers[0];
//    gsl_matrix * matrix = (*p_layer)._weights;
//    gsl_matrix_fprintf(stdout, matrix, "%f");
    

    return 0;
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

	//For windows :)
	cin.get();
}
