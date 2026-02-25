#pragma once
#include "repository.h"
#include "validator.h"
#include "Activitate.h"
#include "observer.h" 
#include "undo.h"

using std::unique_ptr;

class Serv_Exception : public exception
{
private:
	const string msg;
public:
	Serv_Exception(const string& str) : msg(str) {};
	const char* what() const noexcept override;
};

class DTO_Stats
{
public:
	char key;
	float nr_obj, sum;

	friend ostream& operator<< (ostream& stream, const DTO_Stats& rap);
	DTO_Stats(char key, float nr, float sum) noexcept : key{ key }, nr_obj{ nr }, sum{ sum } {};
};

class ServActivitati: public Observable
{
private:
	RepoActivitati& repo, & repo_curente;
	const Validator& val;
	vector<unique_ptr<ActiuneUndo>> actiuni;
public:

	ServActivitati(RepoActivitati& repo, RepoActivitati& rc, const Validator& val) noexcept : repo{ repo }, repo_curente{ rc }, val{ val } {};

	void do_undo();

	void adaugare_activitate(const string& titlu, const string& descriere, const string& tip, const int durata);

	void stergere_activitate(const string& titlu);

	void modificare_activitate(const string& titlu, const string& descriereNoua, const string& tipNou, const int durataNoua);

	const Activitate& obtine_activitate(const string& titlu);

	const vector<Activitate>& obtine_toate_activitatile() const;

	const vector<Activitate> filtreaza_dupa_tip(const string& tip) const;

	const vector<Activitate> sorteaza_activitati() const;

	int adauga_curente(const string& titlu, const string& descriere, const string& tip, const int durata);

	int golire_curente();

	int adauga_curente_random(int nr_curente);

	const vector<Activitate>& obtine_activitatile_curente() const noexcept;

	void export_activitati_curente(const string& file_name) const;

	const vector<DTO_Stats> raport() const;
};