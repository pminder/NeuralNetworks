#include <iostream>
#include <fstream>
#include <vector>
#include <string> 

#include "DataMnist.h"

using namespace std;

DataMnist::DataMnist(void)
{
	path = "C:/Users/Dimitri/Desktop/My stuff/Taff/C++/Projet C++/MNIST/";
	images_file_names.push_back("train-images.idx3-ubyte");
	images_file_names.push_back("t10k-images.idx3-ubyte");
	labels_file_names.push_back("train-labels.idx1-ubyte");
	labels_file_names.push_back("t10k-labels.idx1-ubyte");
}


DataMnist::DataMnist(std::string data_path)
{
	path = data_path;
	images_file_names.push_back("train-images-idx3-ubyte");
	images_file_names.push_back("t10k-images-idx3-ubyte");
	labels_file_names.push_back("train-labels-idx1-ubyte");
	labels_file_names.push_back("t10k-labels-idx1-ubyte");
}


DataMnist::~DataMnist(void)
{
}


//See header file for explanations
int DataMnist::highEndianLowEndian (int i) 
{
	unsigned char a, b, c, d;
	a = i & 255;
    b = (i >> 8) & 255;
    c = (i >> 16) & 255;
    d = (i >> 24) & 255;
	return ((int)a << 24) + ((int)b << 16) + ((int)c << 8) + d;
}


//This method is a bit long, but we did not had a choice : 
//We have to unpack the file in one shot
//as we cannot have access to a precise point in the file.
//beg = 0 ou 1 
//if beg = 0, loads xtrain and xtest
//if beg = 1, loads only xtest
//Once it is run on an element of the class Data,
//This element has xtrain and xtest as attributes (if beg=1)
//Else it only has xtest
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

		
		ifstream file ( (path + images_file_names[k]).c_str(), ios::binary);

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
		//it will continue unloading the data where we it stopped the time before  
		file.read((char*)&magic_number,sizeof(magic_number)); 
		file.read((char*)&number_of_images,sizeof(number_of_images));
		file.read((char*)&number_of_rows,sizeof(number_of_rows));
		file.read((char*)&number_of_cols,sizeof(number_of_cols));

		//Convert out high endian ints into low endian ints
		//Display the values
		number_of_images = highEndianLowEndian(number_of_images);
		cout << "Number of images = " << number_of_images << endl;
		number_of_rows = highEndianLowEndian(number_of_rows);
		cout << "Number of rows in an image = " <<  number_of_rows << std::endl;
		number_of_cols = highEndianLowEndian(number_of_cols);
		cout << "Number of columns in an image = " <<  number_of_cols << endl;

		//Storing the data
		vector <vector <double> > data_vector;
		for (int i = 0; i < number_of_images; ++i)
			{
				vector <double> temporary_vector;
				for(int r = 0; r < number_of_rows; ++r)
				{
					for(int c = 0; c < number_of_cols; ++c)
					{
						//In the structure of the MNIST database,
						//pixels are unsigned bytes which can be interpreted as numbers
						//describing the nuance of black of the pixel.
						//As the file.read method needs a pointer to a character
						//to store the data, we create an unsigned char (value between 0 and 255) 
						//instead of a char (value between -127 and 128)
						//it does not matter since they both correspond to a byte memorywise
						char pix = 0;
						file.read(&pix,sizeof(pix));
						temporary_vector.push_back((double) pix);
					}
				}
				data_vector.push_back(temporary_vector);
			}
			//We fill the class attributes with the data
			if (k == 0) 
			{
				xtrain = data_vector ; 
			}
			else 
			{
				xtest = data_vector ;
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
		ifstream file ( (path + labels_file_names[k]).c_str(), ios::binary);

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

		//Convert out high endian ints into low endian ints
		number_of_items = highEndianLowEndian(number_of_items);
		cout << "Number of labels =" << endl;
		cout << number_of_items << endl;

		//Storing the data
		vector <int> data_vector;
		for (int i = 0; i < number_of_items; ++i)
		{
			unsigned char temporary = 0;
			file.read((char*)&temporary,sizeof(temporary));
			data_vector.push_back((int)temporary);
		}

		//We fill the class attributes with the data
		if (k == 0) 
		{
			ytrain = data_vector ; 
		}
		else 
		{
			ytest = data_vector ;
		}
		cout << "Labels loaded successfully" << endl;

	}
return 0;
}

//Accessors
vector <vector <double> > DataMnist::getTestImages()
{
	return xtest ;
}

vector <vector <double> > DataMnist::getTrainImages(void)
{
	return xtrain ;
}

vector <int> DataMnist::getTrainLabels(void)
{
	return ytrain ;
}

vector <int> DataMnist::getTestLabels(void)
{
	return ytest ;
}

int DataMnist::trainLabels (int i)
{
	return ytrain[i];
}

int DataMnist::testLabels (int i)
{
	return ytest[i];
}

double DataMnist::testImagesPixels (int i, int j)
{
	return xtest[i][j];
}

double DataMnist::trainImagesPixels (int i, int j)
{
	return xtrain[i][j];
}

vector <double> DataMnist::trainImages (int i)
{
	return xtrain[i];
}

vector <double> DataMnist::testImages (int i)
{
	return xtest[i];
}

;
