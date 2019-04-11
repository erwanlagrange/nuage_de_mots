#include <iostream>
#include <cstdlib>
#include <vector>
#include "fonctions.h"
#include "menu_NuageMots.h"
#include <fstream>
#include "CImg.h"

using namespace cimg_library;
using namespace std;


MenuNuageMots::MenuNuageMots() : Menu("MENU PRINCIPAL")
{
	cheminTexte_ = "";
	setMenu();
}

void MenuNuageMots::setMenu()
{
	ajouterOption("aide", "Afficher de l'aide");
	ajouterOption("saisirTexte", "choisir un fichier");
	ajouterOption("afficherTexte", "afficher les mots et leur récurrence");
	ajouterOption("parametre", "Parametres");
	ajouterOption("sauvegarder", "Sauvegarder les modifications");
	ajouterOption("charger", "Charger un texte");
	ajouterOption("construire", "construire");
	ajouterOption("quitter", "Sortir de l'application");
}

void MenuNuageMots::executerOption(const string &nom, bool &fin)
{
	if (nom == "saisirTexte") saisirTexte();
	else if (nom == "afficherTexte") afficherTexte();
	else if (nom == "sauvegarder") sauvegarder();
	else if (nom == "parametre") parametre();
	else if (nom == "charger") 	saisirTexte(charger());
	else if (nom == "construire") construire();
	else Menu::executerOption(nom, fin);
}

void MenuNuageMots::afficherTexte()
{
	texte_.afficher();
	system("pause");
}

void MenuNuageMots::parametre()
{
	MenuParametre p(&parametre_);
	p.Menu::executer();
}

void MenuNuageMots::saisirTexte()
{	
	cheminTexte_ = getOpenFileName("Nom du fichier à ouvrir :", "Fichiers textes (*.txt *.cpp)");	// récupere l'adresse du fichier

	if (cheminTexte_ != "")
		cout << "Nom du fichier : " << cheminTexte_ << endl;
	else
		cout << "Abandon" << endl;

	texte_.remplir(returnTexteFichier(cheminTexte_)); // remplis le fichier grace a la chaine

	system("pause");
}

void MenuNuageMots::saisirTexte(string cheminTexte)
{
	if (cheminTexte != "")
		cout << "Nom du fichier : " << cheminTexte << endl;
	else
		cout << "Abandon" << endl;

	texte_.remplir(returnTexteFichier(cheminTexte));					// crée une classe texte avec la texte du fichier

	system("pause");
}

void MenuNuageMots::sauvegarder()
{
	parametre_.sauvegarder(cheminTexte_);
	system("pause");
}

void MenuNuageMots::construire()
{
	MenuConstruire c(&texte_, &parametre_);
	c.Menu::executer();
}

string MenuNuageMots::charger()
{
	return parametre_.charger();
}

MenuParametre::MenuParametre(Parametre * p) : Menu("MENU PARAMETRE")
{
	parametre_ = p;
	setMenu();
}

void MenuParametre::setMenu()
{
	Menu::ajouterOption("EnleverMots", "EnleverMots");
	Menu::ajouterOption("AfficherEnlever", "AfficherEnlever");
	Menu::ajouterOption("Spirale", "Spirale");
	Menu::ajouterOption("NbMots", "NbMots");
	Menu::ajouterOption("Couleurs", "Couleurs");
	Menu::ajouterOption("orientation", "orientation");
	Menu::ajouterOption("retour", "retour au menu");
}

void MenuParametre::executerOption(const string & nom, bool & fin)
{
	if (nom == "EnleverMots") EnleverMots();
	else if (nom == "AfficherEnlever") afficherEnlever();
	else if (nom == "Spirale") Spirale();
	else if (nom == "NbMots") NbMots();
	else if (nom == "Couleurs") Couleurs();
	else if (nom == "orientation") orientation();
	else if (nom == "retour") fin = true;
}

void MenuParametre::EnleverMots()
{
	parametre_->enleverMots();
	system("pause");
}

void MenuParametre::afficherEnlever()
{
	parametre_->afficherEnlever();
	system("pause");
}

void MenuParametre::Spirale()
{
	parametre_->setSpirale();
	system("pause");
}

void MenuParametre::NbMots()
{
	parametre_->setNbMots();
	system("pause");
}

void MenuParametre::Couleurs()
{
	parametre_->setCouleurs();
	system("pause");
}

void MenuParametre::orientation()
{
	parametre_->setorientation();
	system("pause");
}


MenuConstruire::MenuConstruire(Texte *txt, Parametre *param) : Menu("MENU CONSTRUIRE")
{
	Construction oui(txt, param);
	construire_ = oui;
	setMenu();
}

void MenuConstruire::setMenu()
{
	Menu::ajouterOption("visualiser", "visualiser");
	Menu::ajouterOption("enregistrer", "enregistrer");
	Menu::ajouterOption("retour", "retour au menu");
}

void MenuConstruire::executerOption(const string & nom, bool & fin)
{
	if (nom == "visualiser") visualiser();
	else if (nom == "enregistrer") enregistrer();
	else if (nom == "retour") fin = true;
}


void MenuConstruire::visualiser()
{
	construire_.visualiser();
}

void MenuConstruire::enregistrer()
{
	construire_.enregistrer();
}
