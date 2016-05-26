#include <iostream>
#include <string>
#include "Mot.h"

using namespace std;

Mot::Mot(string text) :text_(text) {
	occurence_ = 1;
	choisi_ = true;
}

