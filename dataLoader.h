#ifndef DATALOADER_H
#define DATALOADER_H

#include <string>

class DataLoader
{
public:
	//Constructeur
	DataLoader(std::string filename);
	//Destructeur
	~DataLoader();

	//Charge les données de la base MNIST et renvoie le nb total d'images
	int load();

	
private:
};


#endif  