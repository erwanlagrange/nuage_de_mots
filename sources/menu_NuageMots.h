#ifndef _MENUNUAGE
#define _MENUNUAGE

#include "menu.h"
#include "fonctions.h"
#include "filedialog.h"
#include "CImg.h"

using namespace cimg_library;

class MenuNuageMots : public Menu // Menuprincipal d�riv� de la class Menu
{
	Texte texte_;	// texte a traiter
	Parametre parametre_;	// param�tre du texte a �tablir
	string cheminTexte_;	// chaine qui correcpond au chemin du texte
public:
	MenuNuageMots();	// constructeur qui initialise cheminTexte_ et appel setMenu()  // Erwan
	void setMenu();	// ajoute les nouvelles options  // Erwan
	void executerOption(const string &nom, bool &fin); // fonction d�riv�e de la classe menu
	void saisirTexte();	// permet de choisir le fichier.txt avec GETOPENFILE  // Erwan
	void saisirTexte(string cheminTexte);	//sans GETOPENFILE  // Erwan
	void afficherTexte();	// appel la fonction d'affichage de la classe Texte pour avoir les mots et leur r�currence pr�-traitement  // Antoine
	void parametre();	// lance le MenuParametre // Erwan & Antoine
	void sauvegarder();	// lance la m�thode de sauvegarde de la classe Parametre  // Erwan
	void construire();	// lance le MenuConstruire   // Erwan & Antoine
	string charger();	// retourne le chemin du fichier, et charge tout les param�tre du projet  // Erwan
};

class MenuParametre : public Menu	// Menu des param�tre d�riv� de la class Menu
{
	Parametre *parametre_;	// pointeur sur l'objet param�tre cr�� dans le menu principal
public:
	MenuParametre(Parametre *p);// constructeur qui r�cup�re les param�tre et appel setMenu()
	void setMenu();	// ajoute les nouvelles options  // Erwan & Antoine
	void executerOption(const string &nom, bool &fin);
	void EnleverMots(); //appelle la m�thode EnleverMots() de la classe Parametre  // Antoine
	void afficherEnlever();	// appelle la m�thode afficherEnlever() de la classe Parametre // Antoine
	void Spirale();	// appelle la m�thode setSpirale() de la classe parametre  // Erwan
	void NbMots();	// appelle la m�thode setNbMots() de la classe parametre  // Erwan
	void Couleurs(); // appelle la m�thode setCouleurs() de la classe parametre   // Erwan
	void orientation();	// appelle la m�thode setorientation() de la classe parametre  // Erwan
};

class MenuConstruire : public Menu	// Menu de construction d�riv� de la class Menu  // Erwan
{
	Texte *txt_;	// pointeur sur l'objet texte cr�� dans le menu principal
	Parametre *param_;	// pointeur sur l'objet param�tre cr�� dans le menu principal
	Construction construire_;	// 
public:
	MenuConstruire(Texte *txt_ ,Parametre *param_);	// initialise l'attribut construire_  // Erwan
	void setMenu();	// ajoute les nouvelles options  // Erwan
	void executerOption(const string &nom, bool &fin); 
	void visualiser();	// appelle la m�thode visualiser() de la classe Construire  // Erwan
	void enregistrer();	// appelle la m�thode enregistrer() de la classe Construire   // Erwan
}; 
#endif