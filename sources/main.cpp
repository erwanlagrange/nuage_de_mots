#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "fonctions.h"
#include "menu.h"
#include "menu_NuageMots.h"
using namespace std;

int main()
{
	srand(time(NULL)); // pour avoir un temp aleatoire
	MenuNuageMots m;
	m.executer();
	system("pause");
	return 0;
}


