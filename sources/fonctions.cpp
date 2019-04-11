#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <shlobj.h>
#include <iomanip>
#include "fonctions.h"
#include "menu_NuageMots.h"
#include "filedialog.h"

using namespace std;

string returnTexteFichier(const string chemin)
{
	cout << chemin << endl; // à enlever 

	string ligne;
	string contenu = ""; // vide pour que le debut de la chaine soit vide
	ifstream fichier(chemin.c_str(), ios::in); // déclare la fonction pour ouvrir le fichier
	if (fichier)  // si l'ouverture a réussi
	{
		
		while (getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu"
		{
			contenu = contenu + ligne; // concatene ligne a la suite de contenu pour avoir toutes les lignes
		}
	}
	else  // sinon
	{
		cerr << "Erreur à l'ouverture !" << endl;
	}
	return contenu;
}

Texte::Texte()
{
}

void Texte::remplir(string s) {
	int stop=0;
	size_t n_debut = 0, n_fin = 0; // garder le type size_t car c'est celui qui est retourné par find_first_of ou size
	string s_temp; // string temporaire
	tableau t_temp("a",1); // tableau temporaire avec mot a et frequence 1
	//cout << "Les differents mots de votre phrase sont:" << endl;

	//prés traitement des caractère spéciaux
	size_t found = s.find_first_of("',?;.!§(*){[]}_");
	if (found > 0 && found <s.size()) {
		do {
			//string h(" ");
			s[found] = ' ';
			found = s.find_first_of("',?;.!§(*){[]}_");
		} while (found != string::npos);
	}
	//fin prés traitement


	while (n_fin != s.length() + 1) { // reduit la chaine a chaque fois et des qu'elle est = à 0 on arrete
		stop = 0;						// critere pour sortir de la boucle

		n_fin = s.find_first_of(' ', n_debut); // cherche le premier espace
		if (n_fin == string::npos) // si c'est la fin
		{
			n_fin = s.length() + 1; // alors on sort de la boucle principale
		}

		s_temp = s.substr(n_debut, n_fin - n_debut); // redéfinie la chaine en la coupant pour avoir que le premier mot
		transform(s_temp.begin(), s_temp.end(), s_temp.begin(), ::tolower);// MAJUSCULE !

		if (s_temp.size() == 1 || s_temp == "") {		//suppression des mots de longeur 1 et des espace!
			stop = 1;
		}

		do {
			for (size_t i = 0; i < tab_.size(); i++) { //	on parcours le tableau de mots afin de trouver un éventuel doublon
				if (s_temp == tab_[i].mots) {
					(tab_[i].freq)++;
					stop = 1;
				}
			}//	si pas de doublon, on ajout une case au deux tableau afin de crée un nouvel élément
			if (stop != 1)
			{
				t_temp.mots = s_temp;
				(tab_).push_back(t_temp);
				stop = 1;
			}

		} while (stop != 1);

		n_debut = n_fin + 1;
	}
	 // fonction qui trie la chaine de caractère en fonction des occurence
	sort(tab_.begin(), tab_.end());			// trie dans l'odre décroissant
}

void Texte::ajouter()
{
	tableau t_temp;
	do {
		cout << "Quelle mot voulez vous ajouter ? (-1 pour sortir): " << endl;
		cin >> t_temp.mots;
		cout << "Quelle fréquence voulez vous ajouter au mot " << t_temp.mots <<"?: " << endl;
		cin >> t_temp.freq;
		if (t_temp.mots!= "-1" && t_temp.freq > 0)
		{
			(tab_).push_back(t_temp);
		}
	} while (t_temp.mots != "-1");
}

void Texte::enlevermot(string mot)
{
	int i = 0;
	for (vector<tableau>::iterator it = tab_.begin(); it != tab_.end(); it++)
	{
		if ((*it).mots == mot)
		{
			tab_.erase(tab_.begin() + i);
			return;
		}
		i++;
	}
}

void Texte::enleverfreq(int f)
{
	int i = 0;
	for (size_t i = 0; i < tab_.size(); i++)
	{
		if (tab_[i].freq <= f)
		{
			tab_.resize(i);
			return;
		}
		i++;
	}
}

void Texte::enleverfreqmax(int max)
{
	for (size_t i = 0; i < tab_.size(); i++)
	{
		if (tab_[i].freq >= max)
		{
			tab_[i].freq = max;
		}
	}
}

void Texte::nombremot(int nb)
{
	if (nb < (int)tab_.size())
	{
		tab_.resize(nb);
	}
}

void Texte::afficher()
{
	int i = 0;
	for (vector<tableau>::iterator it = tab_.begin(); it != tab_.end(); it++)
	{
		cout << "mot n°" << i + 1 << " : " << (*it).mots <<setw(5)<< " | frequence = " << tab_[i].freq << endl;
		i++;
	}
}






Parametre::Parametre()
{
	freqMinEnlever_ = 0;
	spirale_ = 1;
	nbMots_ = 100;
	couleurs_ = 0;
}

void Parametre::enleverMots()
{
	int choix;
	string mot;

	cout << "Enlever les mots par: " << endl << "1 - occurence" << endl << "2 - mot" << endl << "3 - connecteurs" << endl << "4 - retour" << endl;
	cin >> choix;
	if (choix == 1)
	{
		cout << "Quel fréquence voulez-vous enlever ?" << endl;
		cin >> freqMinEnlever_;

	}
	if (choix == 2)
	{
		do {
			cout << "Quel mot voulez vous enlever ? (saisir  \"-1\" pour sortir)" << endl;
			cin >> mot;
			if (mot != "-1") {
				transform(mot.begin(), mot.end(), mot.begin(), ::tolower); // Majuscule !
				motsEnlever_.push_back(mot);
			}
		} while (mot != "-1");
	}
	if (choix == 3)
	{
		cout << "Voulez-vous enlever les pronoms/connecteur ? (o/n)" << endl;
		cin >> mot;
		if (mot == "o") {
			for (size_t i = 0; i < size(connecteur); i++) {
				motsEnlever_.push_back(connecteur[i]);
			}
		}
	}
	if (choix == 4)
	{
		return;
	}
}

void Parametre::afficherEnlever() {
	int i = 0;
	for (vector<string>::iterator it = motsEnlever_.begin(); it != motsEnlever_.end(); it++)
	{
		cout << "mot n°" << i + 1 << " : " << (*it) << endl;
		i++;
	}
	if (freqMinEnlever_ != 0) {
		cout << "Les mots de frequence inferieur ou egale a \'" << freqMinEnlever_ << "\' seront supprimes" << endl;
	}
}

void Parametre::setSpirale()
{
	do {
		cout << "Quelle forme de spirale voulez vous choisir ? " << endl << "1 - circulaire (par defaut)" << endl << "2 - carré" <<  endl;
		cin >> spirale_;
	} while (spirale_ < 0 || spirale_ > 3);
}

void Parametre::setNbMots()
{
	do {
	cout << "Combien de mots voulez vous conserver ? " << endl;
	cin >> nbMots_;
	} while (0 > nbMots_);
}

void Parametre::setCouleurs()
{
	do {
	cout << "Quelle pack de couleur voulez vous choisir ?: " << endl << "1 - Bleu " << endl << "2 - Rouge" << endl << "3 - Vert" << endl << "4 - Aleatoire" << endl;
	cin >> couleurs_;
	} while (couleurs_ < 0 || couleurs_ > 5);
}

void Parametre::setorientation()
{
	do {
	cout << "Quelle l'orientation maximum que vous voulez ? " << endl;
	cin >> orientation_.max;
	} while (orientation_.max < 90);
	do {
	cout << "Quelle l'orientation minimum que vous voulez ? " << endl;
	cin >> orientation_.min;
	} while (orientation_.min > -90);
}

void Parametre::sauvegarder(string cheminTexte)
{
	string cheminSortie =  getSaveFileName("Nom du fichier à sauvegarder :", "Fichiers textes (*.txt *.cpp)");

	ofstream sauv(cheminSortie);
	if (!sauv.is_open()) cout << "Erreur d'ouverture" << endl;
	else
	{
		sauv << cheminTexte << endl;
		sauv << freqMinEnlever_ << endl;
		sauv << spirale_ << endl;
		sauv << nbMots_ << endl;
		sauv << couleurs_ << endl;
		sauv << orientation_.min << endl << orientation_.max << endl;

		sauv << motsEnlever_.size() << endl;
		for (vector<string>::iterator it = motsEnlever_.begin(); it != motsEnlever_.end(); it++)
		{
			sauv << (*it)<< endl;
		}
		
		if (!sauv.good()) cout << "Erreur d'écriture" << endl;
		else cout << "Enregistrement terminé" << endl;
	}

}

string Parametre::charger()
{
	string cheminTexte;
	string str;
	int n;
	string cheminSauvegarde = getOpenFileName();
	ifstream charg (cheminSauvegarde);
	if (!charg.is_open()) cout << "Erreur d'ouverture" << endl;
	else
	{
		charg >> cheminTexte;
		charg >> freqMinEnlever_;
		charg >> spirale_;
		charg >> nbMots_;
		charg >> couleurs_;
		charg >> orientation_.min;
		charg >> orientation_.max;
		charg >> n ;

		for (int i = 0; i < n; i++) {
				getline(charg, str);
				motsEnlever_.push_back(str);
		}

		if (!charg.good()) cout << "Erreur de lecture" << endl;
		else cout << "Lecture terminée" << endl;
	}

	return cheminTexte;
}

Construction::Construction(Texte * txt, Parametre * param)
{
	txt_ = txt;
	param_ = param;
	texte_ = *txt_;
}

Construction::Construction()
{
}

void Construction::construiretexte()
{
	vector<string> motenlever(param_->getmotsEnlever());
	vector<tableau> tab = txt_->gettab();

	for (size_t i = 0; i < motenlever.size(); i++)
	{
		texte_.enlevermot(motenlever[i]);
	}

	texte_.enleverfreq(param_->getfreqMinEnlever());
	texte_.nombremot(param_->getnbMots());
	texte_.enleverfreqmax(15);
	

}


void Construction::construirespiralecercle(int taille_x, int taille_y, int pas)
{
	point pointtemp(taille_x / 2, taille_y / 2);
	int n = 100; // nb de points par tour

	for (int i = 0; pointtemp.x <  taille_x || pointtemp.y <  taille_y; i++)
	{
		pointtemp.x = taille_x / 2 + pas * 1.5 * (6.28*i / n)*cos(6.28*i / n); // elipse
		pointtemp.y = taille_y / 2 + pas * (6.28*i / n)*sin(6.28*i / n);

		spirale_.push_back(pointtemp);
	}
}


void Construction::construirespiralecarre(int taille_x,int taille_y,int pas)
{
	point pointtemp(taille_x / 2, taille_y / 2);
	int direction = 0; // 0=d ; 1=b ; 2=g ; 3=h
	int distance = 1; //nombre de fois le pas
	int tailleboucle;
	vector<point> listetoutpoint;

	spirale_.push_back(pointtemp);
	// ---------------- calcul des angles de la spirale  ----------------//
	while (pointtemp.x + pas <= taille_x && pointtemp.y + pas <= taille_y && pointtemp.x > 0 && pointtemp.y > 0)
	{
		if (direction == 0) // droite
		{
			pointtemp.x = pointtemp.x + (pas*distance);
			spirale_.push_back(pointtemp);
		}

		if (direction == 1) // haut
		{
			pointtemp.y = pointtemp.y + (pas*distance);
			spirale_.push_back(pointtemp);
			distance++;
		}

		if (direction == 2) // gauche
		{
			pointtemp.x = pointtemp.x - (pas*distance);
			spirale_.push_back(pointtemp);
		}

		if (direction == 3) // bas
		{
			pointtemp.y = pointtemp.y - (pas*distance);
			spirale_.push_back(pointtemp);
			distance++;
		}

		direction = (direction + 1) % 4;
	}

	// ---------------- calcul de tout les points  ----------------//
	for (size_t i = 0; i < spirale_.size() - 1; i++) {

		pointtemp = spirale_[i];

		if (spirale_[i].x == spirale_[i + 1].x && spirale_[i].y < spirale_[i + 1].y) // si les x ne bougent pas et y montent
		{
			tailleboucle = abs(spirale_[i].y - spirale_[i + 1].y); // important d'avoir la valeur absolue

			for (size_t j = 0; j != tailleboucle; j++) {
				pointtemp.y = pointtemp.y + 1;
				listetoutpoint.push_back(pointtemp);
			}
		}

		if (spirale_[i].x == spirale_[i + 1].x && spirale_[i].y > spirale_[i + 1].y) // si les x ne bougent pas et y descendent
		{
			tailleboucle = abs(spirale_[i].y - spirale_[i + 1].y); // important d'avoir la valeur absolue

			for (size_t j = 0; j != tailleboucle; j++) {
				pointtemp.y = pointtemp.y - 1;
				listetoutpoint.push_back(pointtemp);
			}
		}

		if (spirale_[i].y == spirale_[i + 1].y && spirale_[i].x < spirale_[i + 1].x) // si les y ne bougent pas et x montent
		{
			tailleboucle = abs(spirale_[i].x - spirale_[i + 1].x); // important d'avoir la valeur absolue

			for (size_t j = 0; j != tailleboucle; j++) {
				pointtemp.x = pointtemp.x + 1;
				listetoutpoint.push_back(pointtemp);
			}
		}

		if (spirale_[i].y == spirale_[i + 1].y && spirale_[i].x > spirale_[i + 1].x) // si les y ne bougent pas et x descendent
		{
			tailleboucle = abs(spirale_[i].x - spirale_[i + 1].x); // important d'avoir la valeur absolue

			for (size_t j = 0; j != tailleboucle; j++) {
				pointtemp.x = pointtemp.x - 1;
				listetoutpoint.push_back(pointtemp);
			}
		}
	}
	spirale_ = listetoutpoint;
}

void Construction::afficher(int taille_x, int taille_y)
{
	//varibales
	vector<tableau> tableau_ = texte_.gettab();
	long int vide = 0; // variable qui sert a voir si la zone est vide 1 pour quelle soit différente de 0 et rentre une fois dans le boucle
	int ok = 0;
	int taille_mot_x;
	int taille_mot_y;
	bool aleatoire_var = false;
	float freq_max = tableau_[0].freq; 
	int i;

	// Declare an image to draw the grid
	CImg<unsigned char> grid1(taille_x, taille_y, 1, 3, 255); // 720x480x1 avec 3 couleurs différente, prérempli avec 255 de partout
	 
	// Declare a display to draw the scene
	CImgDisplay disp1(grid1, "nuage de mot 1", 0, false, false);

	// declare les couleurs
	unsigned char couleur[3][3];
	unsigned char noir[3] = { 0,0,0 };
	unsigned char blanc[3] = { 255,255,255 };
	unsigned char bleu[3][3] = {{ 0,0,255 },{ 116, 208, 241 },{ 0, 51, 102 }};
	unsigned char rouge[3][3] = { { 255,0,0 }, { 187, 11, 11 }, { 107, 13, 13 }};
	unsigned char vert[3][3] = { { 0,255,0 },{ 159, 232, 85 },{ 0, 86, 27 } };

	//affecte la bonne couleur
	switch (param_->getcouleurs())
	{
	case 1:
		memcpy(couleur[0], bleu[0], 3 );
		memcpy(couleur[1], bleu[1], 3);
		memcpy(couleur[2], bleu[2], 3);
		aleatoire_var = false;
		break;
	case 2:
		memcpy(couleur[0], rouge[0], 3);
		memcpy(couleur[1], rouge[1], 3);
		memcpy(couleur[2], rouge[2], 3);
		aleatoire_var = false;
		break;
	case 3:
		memcpy(couleur[0], vert[0], 3);
		memcpy(couleur[1], vert[1], 3);
		memcpy(couleur[2], vert[2], 3);
		aleatoire_var = false;
		break;
	default:
		aleatoire_var = true;
	}


	// pour dessiner la spirale
	//for (size_t i = 0; i < spirale_.size() - 1; i++)
	//{
	//	grid1.draw_line(spirale_[i].x, spirale_[i].y, spirale_[i + 1].x, spirale_[i + 1].y, rouge);
	//}

	for (size_t t = 0; t < tableau_.size(); t++) { // parcour tous les mots du vecteur de mots
		
		CImg<unsigned char> temp; // pour le regenerer a chaque fois
		temp.draw_text(0, 0, (tableau_[t].mots).c_str(), blanc, blanc, 1, 12);
		taille_mot_x = (int)(((tableau_[t].mots).size())*log(((float)(tableau_[t].freq) / (freq_max*0.5) +1 ))* 60); // calcule la taille du mot en x
		taille_mot_y = (int)(log(((float)(tableau_[t].freq) / (freq_max*0.5) + 1) )* 100);							// calcule la taille du mot en y


		for (i = 0; ok != 1; i = i + rand()%15) {// parcour tous les pixel de la spirale 

			for (int j = spirale_[i].x; j < spirale_[i].x + taille_mot_x ||j > taille_x; j++) { // boucle qui regarde si l'emplacement est vide

				if ((int)grid1(j, spirale_[i].y, 0, 0) != 255 || (int)grid1(j, spirale_[i].y, 0, 1) != 255 || (int)grid1(j, spirale_[i].y, 0, 2) != 255)
				{
					vide++;
					break;
				}
				for (int k = spirale_[i].y; k < spirale_[i].y + taille_mot_y || k > taille_y; k++) {
					if ((int)grid1(j, k, 0, 0) != 255 || (int)grid1(j, k, 0, 1) != 255 || (int)grid1(j, k, 0, 2) != 255)
					{
						vide++;
						break;
					}
				}
			}// fin boucle detecter si vide

			if (vide == 0)
			{
				ok = 1;
				system("cls");
				cout << t +1 << "/" << tableau_.size() << "     freq:  " << (tableau_[t].freq) << endl; // / freq_max
				if (t + 1 == tableau_.size())
					cout << "affichage fini" << endl;
				break;
			}
			else
			{
				vide = 0;
			}
		}

		if (aleatoire_var) {
			unsigned char aleatoire[3] = { rand() % (256), rand() % (256), rand() % (256) }; // regénere une couleur aléatoire
			//
			CImg<unsigned char> temp; // pour le regenerer a chaque fois
			temp.draw_text(0, 0, (tableau_[t].mots).c_str(), aleatoire, blanc, 1, taille_mot_y);
			CImg<unsigned char> temp1(temp, "x,y,z,3", 0); // tout pareil mais avec 3 plans
			temp1.draw_text(0, 0, (tableau_[t].mots).c_str(), aleatoire, blanc, 1, taille_mot_y);
			grid1.draw_image(spirale_[i].x, spirale_[i].y, temp1); // avec image
			//temp1.display();
		}
		else {
			//	
			CImg<unsigned char> temp; // pour le regenerer a chaque fois
			temp.draw_text(0, 0, (tableau_[t].mots).c_str(), 1, blanc, 1, taille_mot_y);
			CImg<unsigned char> temp1(temp, "x,y,z,3", 0); // tout pareil mais avec 3 plans
			temp1.draw_text(0, 0, (tableau_[t].mots).c_str(), couleur[t % 3], blanc, 1, taille_mot_y);
			grid1.draw_image(spirale_[i].x, spirale_[i].y, temp1); // avec image
		}

		grid1.display(disp1);
		ok = 0;
	}

	Image_ = grid1;
	// Main loop, exit if the display window is closed or if ESC or Q key is hit
	while (!disp1.is_closed() && !disp1.is_keyESC() && !disp1.is_keyQ()) 
	{
		Image_.display(disp1);
	}
}

void Construction::visualiser()
{

	construiretexte();
	if (param_->getSpirale() != 1 )
		construirespiralecarre(1200, 600, 5); 
	else
		construirespiralecercle(1200, 600, 1);

	afficher(1200,600);
	system("pause");
}

void Construction::enregistrer()
{
	cout << "enregistrement" << endl;
	string cheminSortie = getSaveFileName("Nom du fichier à sauvegarder :", "Fichiers textes (*.txt *.cpp)");
	Image_.save(cheminSortie.c_str()); // char
	system("pause");
}
