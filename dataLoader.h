#ifndef DATALOADER_H
#define DATALOADER_H

#include <string>
#include <vector>
#include <valarray>


//Quelques constantes : les noms de fichiers
#define xtrainFile "data/xtrain.mnist"
#define ytrainFile "data/ytrain.mnist"
#define xtestFile "data/xtest.mnist"
#define ytestFile "data/ytest.mnist"

class DataLoader
{
public:
	//Constructeur
	DataLoader();
	//Destructeur
	~DataLoader();

	//Charge les données de la base MNIST et renvoie le nb total d'images
	int load();

	
private:
	//Réference vers la base d'apprentissage (size 50 000)
	std::vector< std::valarray<float> > * xtrain;
	//Référence vers les labels d'apprentissage
	std::vector<char> * ytrain;

	//Réference vers la base de test (size 10 000)
	std::vector< std::valarray<float> > * xtest;
	//Référence vers les labels de test
	std::vector<char> *  ytest;

	//Réference vers la base "validation" size (10 000)
	std::vector< std::valarray<float> > * xvalid;
	//Référence vers les labels "validation"
	std::vector<char> * yvalid;

	std::vector<char> * loadLabels(std::string filename);
	std::vector< std::valarray<float> > * loadImages(std::string filename);
};


#endif  