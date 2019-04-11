#pragma once
#include <string>
#include <vector>
#include "CImg.h"

using namespace cimg_library;
using namespace std;

struct point { // création d'un type composé "point" // Erwan
	int x;	// coordonnée x
	int y;	// coordonnée y
	point(int x_, int y_) : x(x_), y(y_) {} // constructeur par défault
};

struct Orientation // type composé pour l'orientation du mot à afficher // Erwan
{
	int max = 0;	// angle maximal
	int min = 0;	// angle minimal
};

struct tableau // type composé du tableau avec les mots  // Erwan
{
	string mots;	// un mot
	int freq;	// le nombre d'occurence du mot
	tableau (string m, int f) : mots(m), freq(f) {} // constructeur par défault
	tableau() {}									// constructeur sans parametre

	bool operator < (const tableau& tab) const	// fonction qui sert pour le trie dans l'ordre décroissant
	{
		return (freq > tab.freq);				// le > sert a trier les mots dans l'ordre décroissant
	}
};

string returnTexteFichier(const string a); // fonction externe car elle a une seule utilité qui ne sert qu'a la classe Texte mais n'utilise pas ses attributs  // Erwan

class Texte	// 
{
private:
	vector<tableau> tab_;	// tableau de tableau(mot;fréquence)
public:
	Texte();
	void remplir(string s);	//remplit le tableau a l'aide du chemin s // Antoine et Erwan
	void ajouter();	// permet d'ajouter un mot et sa fréquence (un mot virtuel)  // Erwan
	void enlevermot(string mot);	// permet d'enlever un mot au tableau suivant son nom  // Erwan
	void enleverfreq(int f);	// permet d'enlever les mots dont la fréquence est inférieur ou égale à celle entrée en paramètre  // Antoine & Erwan
	void enleverfreqmax(int max);	//	permet d'ajuster la fréquence maximal des mots pour l'affichage  // Erwan
	void nombremot(int nb);	// permet de redéfinir la taille du tableau, le nombre de mots étudiés  // Antoine & Erwan
	void afficher();	// affiche les éléments du tableau: mot/fréquence  // Antoine
	vector<tableau> gettab() { return tab_; };	// retourne le tableau  // Erwan
};



class Parametre
{
private:
	vector<string> motsEnlever_;	// tableau de string pour les mots à enlever
	const string connecteur[25] = { "la","les","au","aux","et","je","tu","nous","vous","il","ils","elle","elles","un","une","de","se","ou","le","en","ne","qui","pas","des","qu"};	// liste de mots à filtrer
	int freqMinEnlever_ =0;	// seuil de fréquence minimal
	int spirale_ = 1;	// choix entre la spirale carré ou circulaire
	int nbMots_ = 100;	// nombre de mots maximal
	int couleurs_ = 0;	// choix de la couleurs
	Orientation orientation_ ;	// orientation des mots entre[min;max]
public:
	Parametre();	// initialise les paramètres
	void enleverMots();	// demande à l'utilisateur s'il veux enlever des mots suivants différents paramètre: le nom, la fréquence minimal ou appliquer le filtre de mots  // Erwan & Antoine
	void afficherEnlever();	// affiche les mots enlever via le paramètre nom // Antoine
	void setSpirale();	// demande à l'utilisateur entre une spirale carré ou circulaire  // Erwan
	void setNbMots();	// demande à l'utilisateur s'il veux modifier le nombre de mot affichés  // Erwan
	void setCouleurs();	// demande à l'utilisateur le thème de couleur qu'il veut  // Erwan
	void setorientation(); // demande à l'utilisateur l'intervalle de l'orientation des mots  // Erwan
	void sauvegarder(string cheminTexte);	// enregistre les paramètres dans un fichier.txt  // Erwan
	string charger();	// initialise les attributs de cette classe avec les élément s du fichier.txt et retourne le chemin du fichier.txt  // Erwan
	int getfreqMinEnlever() { return freqMinEnlever_; };	// retourne le seuil de fréquence minimal  // Erwan
	int getSpirale() { return spirale_; };	// retourne le choix de spirale  // Erwan
	int getnbMots() { return nbMots_; };	// retourne le nombre de mots   // Erwan
	int getcouleurs() { return couleurs_; };	// retourne le choix du thème de couleur  // Erwan
	Orientation getorientation() { return orientation_; };	// retourne [min;max]  // Erwan
	vector<string> getmotsEnlever() { return motsEnlever_; };	// retoune la liste des mots à enlever  // Erwan
};


class Construction  // Erwan
{
	Texte texte_;	// nouvel attribu Texte qui sera le nouveau texte généré
	Texte *txt_;	// pointeur sur l'objet texte créé dans le menu principal
	Parametre *param_;	// pointeur sur l'objet paramètre créé dans le menu principal
	vector<point> spirale_;	// vecteur de point qui repertorie tout les points de la spirale
	CImg<unsigned char> Image_;	// image finale
public:
	Construction(Texte *txt, Parametre *param);		// initialise les attributs avec ceux entrés en paramètres  // Erwan
	Construction(); // obligatoire pour le Menu fonction  // Erwan
	void construiretexte();	// applique les paramètres au texte  // Erwan & Antoine
	void construirespiralecercle(int taille_x, int taille_y, int pas);	// construit  une spirale circulaire et rempli le tableau de point avec toutes les coordonnée de la spirale  // Erwan
	void construirespiralecarre(int taille_x, int taille_y, int pas);	// construit une spirale carré	et rempli le tableau de point avec toutes les coordonnée de la spirale  // Erwan
	void afficher(int taille_x, int taille_y);	// colle les mots suivants les points de la spirale tout en vérifiant les collisions  // Erwan
	void visualiser();	// appelle successivement construireTexte(), l'un des deux méthode de construction de la spirale et la méthode afficher()  // Erwan
	void enregistrer();	// enregistre l'image créée  // Erwan
};

