#ifndef DATAMNIST_H
#define DATAMNIST_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>



class DataMnist
{

public:

	DataMnist(void);

	DataMnist(std::string data_path);

	~DataMnist(void);

	int loadImages(int) ;

	int loadLabels(int) ;

	//Accesors
	std::vector < std::vector <double> > getTestImages();

	std::vector < std::vector <double> > getTrainImages();
	
	std::vector <int> getTrainLabels();

	std::vector <int> getTestLabels();

	int trainLabels (int);

	int testLabels (int);

	double trainImagesPixels (int,int);

	double testImagesPixels (int,int);

	std::vector <double> trainImages (int);

	std::vector <double> testImages (int);
	



private : 
	//Path to access the MNIST data base in the computer
	std::string path;

	//Vector of 2 containing the names of the files as strings
	//See constructor
	std::vector<std::string> images_file_names ;

	std::vector<std::string> labels_file_names ;

	//Class attributes containing the images
	std::vector <std::vector <double> > xtrain ;

	std::vector <std::vector <double> > xtest ;

	//Class attributes containing the labels
	std::vector <int> ytrain ;

	std::vector <int> ytest ;

	//All the integer in the MNIST data base are stored in the high endian format
	//Thus we need a process to transform high endian stored integers into low endian integers
	//We did not thought of the transformation algorithm ourselves (we got a lot of help from the internet)
	int highEndianLowEndian (int i);

};

#endif // DATAMNIST_H
