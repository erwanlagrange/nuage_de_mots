#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "menu.h"

using namespace std;

// Definition des methodes de la classe OptionMenu

OptionMenu::OptionMenu(const string &nom,const string &description)  : nom_(nom), description_(description)
{
}


// Definition des methodes de la classe Menu

Menu::Menu(const string & titre) : titre_(titre)
{
}



void Menu::ajouterOption(const string &nom,const string &description)
{
  listeOptions_.push_back(OptionMenu(nom,description));
}


void Menu::afficherMenu()
{
	cout  << " ----------------------------------------------------" << endl;
	cout  << " -----------------------"<< titre_ <<"---------------" << endl;
	cout   << " ----------------------------------------------------" << endl << endl;
  for (int i=0;i<listeOptions_.size();i++) {
    cout<<"- "<<setw(2)<<i<<" : "<<listeOptions_[i].getDescription()<<endl;
  }
}

int Menu::demanderChoix()
{
  int choix;
  cout<<"Votre choix : ";
  cin>>choix;
  cout<<endl;
  return choix;
}

void Menu::executer()
{
  bool fin=false;
  while(!fin) {
    system("cls");
    afficherMenu();
    int choix=demanderChoix();
    if (choix>=0 && choix<listeOptions_.size())
      executerOption(listeOptions_[choix].getNom(),fin);
    else {
      cout<<"Choix incorrect"<<endl;
      system("pause");
    }
  }
}

void Menu::executerOption(const string &nom,bool &fin)
{
  fin=false;
  if (nom=="quitter") fin=quitter();
  else if (nom=="aide") aide();
  else {
    cout<<"Option inexistante"<<endl;
    system("pause");
    }
}

bool Menu::quitter()
{
  bool fin=false;
  char reponse;
  cout<<"Voulez-vous vraiment sortir de l'application (o/n) ?";
  cin>>reponse;
  if ((reponse=='o')||(reponse=='O')) fin=true;
  return fin;
}

void Menu::aide()
{
  cout<<"La liste ci-dessus vous propose les options disponibles pour ce menu."<<endl;
  cout<<"Vous devez entrer un numero qui correspond a votre choix et valider en"<<endl;
  cout<<"appuyant sur la touche <Entree>."<<endl;
  cout<<"Une fois l'option executee, vous aurez a nouveau acces au menu."<<endl<<endl;
  system("pause");
}



