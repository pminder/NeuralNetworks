#include <iostream>
#include <fstream>
#include <vector>
#include <valarray>

#include "DataMnist.h"

using namespace std ;

int main(int argc, char const *argv[])
{
	DataMnist database;

	//Test of data.loadLabels
	//We only load the test labels (10 000) 
	//to save time (this is just a test)
	cout << "Test of labels" << endl;
	database.loadLabels(1);
	//We display the first 10 to see if the data has the right form
	for (int j = 0; j<10; ++j)
	{ 
		cout << database.testLabels(j) << endl;
	}


	//Test of data.loadImages
	cout << "Test of images" << endl;
	database.loadImages(1);
	for (int j = 0; j < 784; j++)
	{
		cout << database.testImagesPixels(0,j) << endl;
	}
	cin.get();
}
