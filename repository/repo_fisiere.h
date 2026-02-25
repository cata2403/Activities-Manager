#pragma once
#include "repo_activitati.h"
using std::vector;

class Repo_Fisiere : public Repo_Memorie
{
private:
	const string nume_fisier;
	void loadFromFile();
	void saveToFile(const vector<Activitate>& data);
public:
	Repo_Fisiere(const string& file) : nume_fisier{ file } {
		loadFromFile();
	};

	~Repo_Fisiere();
};
