#ifndef __MOT__
#define __MOT__
#include <iostream>
#include <string>

using namespace std;

// Realise par Romain JULIAN
class Mot {
	string text_;
	int occurence_;
	bool choisi_;
	
public:
	Mot(string text);
	void apparu() { occurence_ += 1;}  // incremente le nombre d'occurence
	bool getChoisi() { return choisi_; }
	string getText() { return text_; }
	int getOccurence() { return orccurence_; }
	void setChoisi(bool choix) { choisi_ = choix; }

}



#endif