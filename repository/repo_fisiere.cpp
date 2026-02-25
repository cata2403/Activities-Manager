#include "repo_fisiere.h"
#include <fstream>

void Repo_Fisiere::loadFromFile()
{
	std::ifstream fin(nume_fisier);
	if (!fin.is_open())
	{
		throw Repo_Exception("<Fisierul nu s-a putut deschide>");
	}
	string titlu, descriere, tip, durata_str;//fin >> titlu >> descriere >> tip >> durata_str
	while (getline(fin, titlu, ','))
	{
		getline(fin, descriere, ',');
		getline(fin, durata_str, ',');
		getline(fin, tip);
		int durata = stoi(durata_str);
		adaugareNoUnique(Activitate{titlu, descriere, tip, durata});
	}
	fin.close();
}

void Repo_Fisiere::saveToFile(const vector<Activitate>& data)
{
	std::ofstream fout(nume_fisier);
	/*if (!fout.is_open())
		throw Repo_Exception("<Fisierul nu s-a putut deschide>");*/
	int nr = 0;
	for (auto& act : data)
	{
		fout << act.get_titlu() << "," << act.get_descriere() << "," << act.get_durata() << "," << act.get_tip();
		if (nr < data.size() - 1)
		{
			fout << '\n';
			nr++;
		}
	}
	fout.close();
}

Repo_Fisiere::~Repo_Fisiere()
{
	saveToFile(get_all());
	golire();
}