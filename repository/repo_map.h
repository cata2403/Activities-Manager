#pragma once
#include "repository.h"
#include <map>

using std::map;

class Repo_Dictionar : public RepoActivitati
{
private:
	map<string, Activitate> elems;
	mutable vector<Activitate> vect_transfer;
	double chance;
	void AruncaExceptie() const;
public:
	Repo_Dictionar(double ch) : chance{ ch } {};
	void adaugare(const Activitate& act);
	void stergere(const string& titlu);
	void modificare(const Activitate& act);
	const Activitate& cautare(const string& titlu) const;
	void golire();
	const vector<Activitate>& get_all() const;
};