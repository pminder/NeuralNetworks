#include <iostream>
#include <fstream>
#include <vector>
#include <string> 
#include <Eigen/Dense>

#include "DataMnist.h"

using namespace std;
using namespace Eigen;

DataMnist::DataMnist(void)
{
	_path = "C:/Users/Dimitri/Desktop/My stuff/Taff/C++/Projet C++/MNIST/";
	initFileNames();
	initSizes();
}


DataMnist::DataMnist(std::string data_path)
{
	_path = data_path;
	initFileNames();
	initSizes();
}


DataMnist::~DataMnist(void)
{
}

int DataMnist::initSizes()
{
	_xtest.resize(test_size);
	_xtrain.resize(train_size);
	_ytest.resize(test_size);
	_ytrain.resize(train_size);
	for (int i = 0; i<test_size; ++i)
	{
		_xtest[i].resize(flat_image_size);
	}
	for (int i = 0; i<train_size; ++i)
	{
		_xtrain[i].resize(flat_image_size);
	}
	return 0;
}


int DataMnist::initFileNames()
{
	_images_file_names.push_back("train-images.idx3-ubyte");
	_images_file_names.push_back("t10k-images.idx3-ubyte");
	_labels_file_names.push_back("train-labels.idx1-ubyte");
	_labels_file_names.push_back("t10k-labels.idx1-ubyte");
	return 0;
}


//This method is a bit long, but we did not had a choice : 
//We have to unpack the file in one shot
//as we cannot have access to a precise point in the file.

//beg = 0 ou 1 
//if beg = 0, loads xtrain and xtest
//if beg = 1, loads only xtest
//Once it is run on an element of the class Data,
//This element has _xtrain and _xtest as attributes (if beg=0)
//Else it only has _xtest
int DataMnist::loadImages(int beg)
{
	//Test to verify if the users has given a right value
	//If not, default to 1
	if (beg != 0 && beg != 1) 
	{
		beg = 1; 
	}

	//If beg == 1, this loop only has one iteration
	//As we only load one file (the test one)
	for (int k = beg; k < 2; ++k)
	{
		//The ios::binary parameters is very important here 
		//(without it the data we get is all zeros)

		
		ifstream file ( (_path + _images_file_names[k]).c_str(), ios::binary);

		//test to be sure that the file is open
		if (!file.is_open())
		{
			cerr << "Could not open file" << endl;
			return 1;
		}

		
		//We initialize variables to unload the header variables of the MNIST database
		//magic_number is useless, but we need to unload it to keep going in the data (cf next commentary) 
		int magic_number = 0;
		int number_of_images = 0;
		int number_of_rows = 0;
		int number_of_cols = 0;

		//The method fstream::read() takes two parameters : 
		//		- a pointer to an array of char where the characters are stored 
		//      (thus we cast &magic_number as a char* for instance)
		//		- the number of character it should extract
		//The method fstream::read() works serially : 
		//Once we call it on a file, the next time we will call it on that same file
		//it will continue unloading the data at the point it stopped the previous time
		//Thus we unload the first elements of the database even though they won't be useful
		file.read((char*)&magic_number,sizeof(magic_number)); 
		file.read((char*)&number_of_images,sizeof(number_of_images));
		file.read((char*)&number_of_rows,sizeof(number_of_rows));
		file.read((char*)&number_of_cols,sizeof(number_of_cols));
		
		//Storing the data into class attributes for train images
		if (k == 0 )
		{
			for (int i = 0; i < train_size; ++i)
			{
				int count = 0;
				for(int r = 0; r < image_size; ++r)
				{
					for(int c = 0; c < image_size; ++c)
					{
						//In the structure of the MNIST database,
						//pixels are unsigned bytes which can be interpreted as numbers
						//describing the nuance of black of the pixel.
						//As the file.read method needs a pointer to a character
						//to store the data, we create an unsigned char (value between 0 and 255) 
						//instead of a char (value between -127 and 128)
						//It is more practical since we want our pixel coloration to take positive value
						unsigned char pix = 0;
						file.read((char*)&pix,sizeof(pix));
						_xtrain[i](count)= (double) pix / 255.;
						++ count;

					}
				}
			}
		}
		//Storing the data for test images
		else
		{
			for (int i = 0; i < test_size; ++i)
			{
				int count = 0;
				for(int r = 0; r < image_size; ++r)
				{
					for(int c = 0; c < image_size; ++c)
					{
						//In the structure of the MNIST database,
						//pixels are unsigned bytes which can be interpreted as numbers
						//describing the nuance of black of the pixel.
						//As the file.read method needs a pointer to a character
						//to store the data, we create an unsigned char (value between 0 and 255) 
						//instead of a char (value between -127 and 128)
						//it does not matter since they both correspond to a byte memorywise
						unsigned char pix = 0;
						file.read((char*)&pix,sizeof(pix));
						_xtest[i](count)= (double) pix / 255.;
						++ count;

					}
				}
			}
		}
		cout << "Images loaded successfully" << endl;
	}
	return 0;
}


//Same principle as Data::loadImages with labels
int DataMnist :: loadLabels(int beg)
{
	//Test to verify if the users has given a right value
	//If not, default to 1
	if (beg !=0 && beg !=1) 
	{
		beg = 1; 
	}

	//If beg == 1, this loop only has one iteration
	//As we only load one file
	for (int k = beg; k < 2; ++k)
	{
		ifstream file ( (_path + _labels_file_names[k]).c_str(), ios::binary);

	//test to be sure that the file is open
		if (!file.is_open())
		{
			cerr << "Could not open file" << endl;
			return 1;
		}

		//We initialize variables to unload the header variables of the MNIST database
		//magic_number is useless, but we need to unload it to keep going in the data (cf next commentary) 
		int magic_number = 0;
		int number_of_items = 0;

		file.read((char*)&magic_number,sizeof(magic_number)); 
		file.read((char*)&number_of_items,sizeof(number_of_items));

		//Storing the data
		if (k==0)
		{
			for (int i = 0; i < train_size ; ++i)
			{
				unsigned char temporary = 0;
				file.read((char*)&temporary,sizeof(temporary));
				_ytrain[i]=temporary;
			}
		}
		else
		{
			for (int i = 0; i < test_size ; ++i)
			{
				unsigned char temporary = 0;
				file.read((char*)&temporary,sizeof(temporary));
				_ytest[i]=temporary;
			}
		}
		cout << "Labels loaded successfully" << endl;

	}
	return 0;
}

//Accessors
int DataMnist::trainLabel (int i)
{
	return _ytrain[i];
}

int DataMnist::testLabel (int i)
{
	return _ytest[i];
}


Eigen::VectorXd DataMnist::trainImage (int i)
{
	return _xtrain[i];
}

Eigen::VectorXd DataMnist::testImage (int i)
{
	return _xtest[i];
}

vector<VectorXd> DataMnist::GetTrainImages()
{
    return _xtrain;
}

vector<int> DataMnist::GetTrainLabels()
{
    return _ytrain;
}
