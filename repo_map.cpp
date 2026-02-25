#include "repo_map.h"
#include "utilitati.h"

void Repo_Dictionar::AruncaExceptie() const
{
	int verif = (int)(chance * 1000);
	if (verif >= Utils::rand_numar())
		throw Repo_Exception("<Hopa, operatia a aruncat exceptie>");
}

void Repo_Dictionar::adaugare(const Activitate& act)
{
	AruncaExceptie();
	if (elems.count(act.get_titlu()))
		throw Repo_Exception("<Activitatea este deja adaugata>");
	elems.emplace(act.get_titlu(), act);
}

void Repo_Dictionar::stergere(const string& titlu)
{
	AruncaExceptie();
	auto it = elems.find(titlu);
	if (it == elems.end())
		throw Repo_Exception("<Activitatea nu exista>");
	elems.erase(it);
}

void Repo_Dictionar::modificare(const Activitate& act)
{
	AruncaExceptie();
	if (!elems.count(act.get_titlu()))
		throw Repo_Exception("<Activitatea nu exista>");
	elems[act.get_titlu()] = act;
}

const Activitate& Repo_Dictionar::cautare(const string& titlu) const
{
	AruncaExceptie();
	if (!elems.count(titlu))
		throw Repo_Exception("<Activitatea nu exista>");
	return elems.at(titlu);
}

void Repo_Dictionar::golire()
{
	AruncaExceptie();
	elems.clear();
}

const vector<Activitate>& Repo_Dictionar::get_all() const
{
	AruncaExceptie();
	vect_transfer.clear();
	for (auto& elem : elems)
		vect_transfer.push_back(elem.second);
	return vect_transfer;
}