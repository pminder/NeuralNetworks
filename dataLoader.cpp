#include <fstream>
#include <iostream>

#include "dataLoader.h"

using namespace std;




//Ne pas oublier de libérer toute la mémoire en cas de
// - impossibilité ouvrir fichier
// - memory error ??

DataLoader::DataLoader() 
{

}

DataLoader::~DataLoader()
{

}

int DataLoader::load()
{

	loadLabels(ytrainFile);
}

vector<char> * DataLoader::loadLabels(string filename)
{

	//Number of items
	int nItems(0);

	ifstream file(filename.c_str());
	if (!file)
	{
		throw string("Could not open file");
	}

	//Discard magic number 
	file.ignore(4);
	//Get number of items
	for (int i = 24; i >= 0; i-=8)
	{
		nItems += file.get() << i;
	}

	cout << nItems << endl;

}

vector< valarray<float> > * DataLoader::loadImages(string filename)
{

}