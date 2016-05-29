#ifndef MOT_H
#define MOT_H
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
	bool getChoisi() const { return choisi_; }
	string getText() const { return text_; }
	int getOccurence() const { return occurence_; }
	void setChoisi(bool choix) { choisi_ = choix; }

};



#endif