#include "service_activitati.h"
#include "utilitati.h"
#include <algorithm>
#include <fstream>
#include <map>
using std::copy_if;
using std::make_unique;

const char* Serv_Exception::what() const noexcept
{
	return msg.c_str();
}

ostream& operator<<(ostream& stream, const DTO_Stats& rap)
{
	stream << "[" << rap.key << "] --> " << rap.sum / rap.nr_obj;
	return stream;
}

void ServActivitati::do_undo()
{
	if (actiuni.empty())
		throw Serv_Exception("<Nu se mai poate face undo>");
	actiuni.back()->doUndo();
	actiuni.pop_back();
}

void ServActivitati::adaugare_activitate(const string& titlu, const string& descriere, const string& tip, const int durata)
{
	Activitate new_a{ titlu, descriere, tip, durata };
	val.validare_activitate(new_a);
	repo.adaugare(new_a);
	actiuni.push_back(make_unique<UndoAdaugare>(repo, titlu));
}

void ServActivitati::stergere_activitate(const string& titlu)
{
	Activitate temp{ titlu, "valid", "valid", 1 };
	val.validare_activitate(temp);
	const Activitate& ref = repo.cautare(titlu);
	actiuni.push_back(make_unique<UndoStergere>(repo, ref));
	repo.stergere(titlu);
}

void ServActivitati::modificare_activitate(const string& titlu, const string& descriereNoua, const string& tipNou, const int durataNoua)
{
	Activitate a{ titlu, descriereNoua, tipNou, durataNoua };
	val.validare_activitate(a);
	const Activitate& ref = repo.cautare(titlu);
	actiuni.push_back(make_unique<UndoModificare>(repo, ref));
	repo.modificare(a);
}

const Activitate& ServActivitati::obtine_activitate(const string& titlu)
{
	Activitate temp{ titlu, "valid", "valid", 1 };
	val.validare_activitate(temp);
	return repo.cautare(titlu);
}

const vector<Activitate> ServActivitati::filtreaza_dupa_tip(const string& tip) const
{
	const vector<Activitate> acts = repo.get_all();
	vector<Activitate> filtrat;
	copy_if(acts.begin(), acts.end(), back_inserter(filtrat), [&](const Activitate& act) noexcept {return act.get_tip() == tip; });
	return filtrat;
}

const vector<Activitate> ServActivitati::sorteaza_activitati() const
{
	vector<Activitate> acts = repo.get_all();
	sort(acts.begin(), acts.end(), [](const Activitate& a1, const Activitate& a2) noexcept {return (a2.get_titlu() > a1.get_titlu()) || (a2.get_titlu() == a1.get_titlu() && a2.get_durata() > a1.get_durata()); });
	return acts;
}

const vector<Activitate>& ServActivitati::obtine_toate_activitatile() const
{
	const vector<Activitate>& r = repo.get_all();
	return r;
}

int ServActivitati::adauga_curente(const string& titlu, const string& descriere, const string& tip, const int durata)
{
	Activitate act{ titlu, descriere, tip, durata };
	val.validare_activitate(act);
	repo_curente.adaugare(act);
	notify();
	return (int)repo_curente.get_all().size();
}

int ServActivitati::golire_curente()
{
	repo_curente.golire();
	notify(); 
	return (int)repo_curente.get_all().size();
}

const vector<Activitate>& ServActivitati::obtine_activitatile_curente() const noexcept
{
	return repo_curente.get_all();
}

int ServActivitati::adauga_curente_random(int nr_curente)
{
	int nr = 1;
	while (nr <= nr_curente)
	{
		Activitate a{ Utils::rand_cuvant(),Utils::rand_cuvant(),Utils::rand_cuvant(),Utils::rand_numar() };
		try
		{
			repo_curente.adaugare(a);
			nr++;
		}
		catch (exception) {};
	}
	notify(); 
	return (int)repo_curente.get_all().size();
}

void ServActivitati::export_activitati_curente(const string& file) const
{
	std::ofstream fout(file);
	if (!fout.is_open())
		throw Serv_Exception("<Erorare la deschidere fisier>");
	fout << "Titlu,Tip,Durata,Descriere\n";
	const vector<Activitate>& acts{ repo_curente.get_all() };
	for (auto& act : acts)
		fout << act.get_titlu() << ',' << act.get_tip() << ',' << act.get_durata() << ',' << act.get_descriere() << '\n';
	fout.close();
}

const vector<DTO_Stats> ServActivitati::raport() const
{
	map<char, pair<float, float>> date;
	const vector<Activitate>& activs = repo.get_all();
	for (auto& act : activs)
	{
		const char key = act.get_tip().at(0);
		date[key].first++;
		date[key].second += act.get_durata();
	}
	vector<DTO_Stats> raporturi;
	for (auto& rap : date)
		raporturi.push_back(DTO_Stats{ rap.first,rap.second.first,rap.second.second });
	return raporturi;
}