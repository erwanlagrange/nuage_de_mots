#pragma once
#include <string>
#include <vector>
#include "CImg.h"

using namespace cimg_library;
using namespace std;

struct point { // cr�ation d'un type compos� "point" // Erwan
	int x;	// coordonn�e x
	int y;	// coordonn�e y
	point(int x_, int y_) : x(x_), y(y_) {} // constructeur par d�fault
};

struct Orientation // type compos� pour l'orientation du mot � afficher // Erwan
{
	int max = 0;	// angle maximal
	int min = 0;	// angle minimal
};

struct tableau // type compos� du tableau avec les mots  // Erwan
{
	string mots;	// un mot
	int freq;	// le nombre d'occurence du mot
	tableau (string m, int f) : mots(m), freq(f) {} // constructeur par d�fault
	tableau() {}									// constructeur sans parametre

	bool operator < (const tableau& tab) const	// fonction qui sert pour le trie dans l'ordre d�croissant
	{
		return (freq > tab.freq);				// le > sert a trier les mots dans l'ordre d�croissant
	}
};

string returnTexteFichier(const string a); // fonction externe car elle a une seule utilit� qui ne sert qu'a la classe Texte mais n'utilise pas ses attributs  // Erwan

class Texte	// 
{
private:
	vector<tableau> tab_;	// tableau de tableau(mot;fr�quence)
public:
	Texte();
	void remplir(string s);	//remplit le tableau a l'aide du chemin s // Antoine et Erwan
	void ajouter();	// permet d'ajouter un mot et sa fr�quence (un mot virtuel)  // Erwan
	void enlevermot(string mot);	// permet d'enlever un mot au tableau suivant son nom  // Erwan
	void enleverfreq(int f);	// permet d'enlever les mots dont la fr�quence est inf�rieur ou �gale � celle entr�e en param�tre  // Antoine & Erwan
	void enleverfreqmax(int max);	//	permet d'ajuster la fr�quence maximal des mots pour l'affichage  // Erwan
	void nombremot(int nb);	// permet de red�finir la taille du tableau, le nombre de mots �tudi�s  // Antoine & Erwan
	void afficher();	// affiche les �l�ments du tableau: mot/fr�quence  // Antoine
	vector<tableau> gettab() { return tab_; };	// retourne le tableau  // Erwan
};



class Parametre
{
private:
	vector<string> motsEnlever_;	// tableau de string pour les mots � enlever
	const string connecteur[25] = { "la","les","au","aux","et","je","tu","nous","vous","il","ils","elle","elles","un","une","de","se","ou","le","en","ne","qui","pas","des","qu"};	// liste de mots � filtrer
	int freqMinEnlever_ =0;	// seuil de fr�quence minimal
	int spirale_ = 1;	// choix entre la spirale carr� ou circulaire
	int nbMots_ = 100;	// nombre de mots maximal
	int couleurs_ = 0;	// choix de la couleurs
	Orientation orientation_ ;	// orientation des mots entre[min;max]
public:
	Parametre();	// initialise les param�tres
	void enleverMots();	// demande � l'utilisateur s'il veux enlever des mots suivants diff�rents param�tre: le nom, la fr�quence minimal ou appliquer le filtre de mots  // Erwan & Antoine
	void afficherEnlever();	// affiche les mots enlever via le param�tre nom // Antoine
	void setSpirale();	// demande � l'utilisateur entre une spirale carr� ou circulaire  // Erwan
	void setNbMots();	// demande � l'utilisateur s'il veux modifier le nombre de mot affich�s  // Erwan
	void setCouleurs();	// demande � l'utilisateur le th�me de couleur qu'il veut  // Erwan
	void setorientation(); // demande � l'utilisateur l'intervalle de l'orientation des mots  // Erwan
	void sauvegarder(string cheminTexte);	// enregistre les param�tres dans un fichier.txt  // Erwan
	string charger();	// initialise les attributs de cette classe avec les �l�ment s du fichier.txt et retourne le chemin du fichier.txt  // Erwan
	int getfreqMinEnlever() { return freqMinEnlever_; };	// retourne le seuil de fr�quence minimal  // Erwan
	int getSpirale() { return spirale_; };	// retourne le choix de spirale  // Erwan
	int getnbMots() { return nbMots_; };	// retourne le nombre de mots   // Erwan
	int getcouleurs() { return couleurs_; };	// retourne le choix du th�me de couleur  // Erwan
	Orientation getorientation() { return orientation_; };	// retourne [min;max]  // Erwan
	vector<string> getmotsEnlever() { return motsEnlever_; };	// retoune la liste des mots � enlever  // Erwan
};


class Construction  // Erwan
{
	Texte texte_;	// nouvel attribu Texte qui sera le nouveau texte g�n�r�
	Texte *txt_;	// pointeur sur l'objet texte cr�� dans le menu principal
	Parametre *param_;	// pointeur sur l'objet param�tre cr�� dans le menu principal
	vector<point> spirale_;	// vecteur de point qui repertorie tout les points de la spirale
	CImg<unsigned char> Image_;	// image finale
public:
	Construction(Texte *txt, Parametre *param);		// initialise les attributs avec ceux entr�s en param�tres  // Erwan
	Construction(); // obligatoire pour le Menu fonction  // Erwan
	void construiretexte();	// applique les param�tres au texte  // Erwan & Antoine
	void construirespiralecercle(int taille_x, int taille_y, int pas);	// construit  une spirale circulaire et rempli le tableau de point avec toutes les coordonn�e de la spirale  // Erwan
	void construirespiralecarre(int taille_x, int taille_y, int pas);	// construit une spirale carr�	et rempli le tableau de point avec toutes les coordonn�e de la spirale  // Erwan
	void afficher(int taille_x, int taille_y);	// colle les mots suivants les points de la spirale tout en v�rifiant les collisions  // Erwan
	void visualiser();	// appelle successivement construireTexte(), l'un des deux m�thode de construction de la spirale et la m�thode afficher()  // Erwan
	void enregistrer();	// enregistre l'image cr��e  // Erwan
};

