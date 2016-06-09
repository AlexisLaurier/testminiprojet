#include <time.h>
#include <iostream>

#include "Menu.h"
#include "CImg.h"

using namespace std;
using namespace cimg_library;


int main() {
	srand(time(NULL));
	MenuPrincipal menu;
	menu.executer();
	return 0;
}


/*
int main()
{
	Diagramme diag;
	diag.afficher();
	return 0;
} 
*/

