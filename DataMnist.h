#ifndef DATAMNIST_H
#define DATAMNIST_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Eigen/Dense>

//We treat those as constants as this class is only designed to treat the MNIST data base
//So we do not lose modularity doing this
const int image_size = 28;
const int flat_image_size = 28*28 ;
const int test_size = 10000 ;
const int train_size = 60000 ;

class DataMnist
{

public:

	DataMnist(void);

	DataMnist(std::string data_path);

	~DataMnist(void);
	
	//Gives the right dimension to the elements of the database
	//We do not use static vectors though because the database images will be the output of access methods
	int initSizes();

	int initFileNames();

	int loadImages(int) ;

	int loadLabels(int) ;

	//Accesors
	int trainLabel (int);

	int testLabel (int);

	Eigen::VectorXd trainImage (int);

	Eigen::VectorXd testImage (int);
	



private : 
	//Path to access the MNIST data base in the computer
	std::string _path;

	//Vector of 2 containing the names of the files as strings
	//See constructor
	std::vector<std::string> _images_file_names ;

	std::vector<std::string> _labels_file_names ;

	//Class attributes containing the images
	std::vector < Eigen::VectorXd > _xtrain ;

	std::vector <Eigen::VectorXd> _xtest ;

	//Class attributes containing the labels
	std::vector <int> _ytrain ;

	std::vector <int> _ytest ;

};

#endif // DATAMNIST_H
