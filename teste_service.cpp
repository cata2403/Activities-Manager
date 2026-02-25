#include "teste_service.h"
#include "service_activitati.h"
#include "undo.h"
#include <assert.h>
#include <stdexcept>

void TestService::test_adaugare_activitate()
{
	Repo_Memorie repo, rc;
	const Validator val;
	ServActivitati serv{ repo, rc, val };
	try
	{
		serv.adaugare_activitate("", "dawgd8hh.'/.;", "ewyu", -1);
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	serv.adaugare_activitate("aa", "aadhawuodh", "ewyu", 1);
	try
	{
		serv.adaugare_activitate("aa", "dawgd8hh.'/.;", "ewyu", 23);
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
}

void TestService::test_stergere_activitate()
{
	Repo_Memorie repo, rc;
	const Validator val;
	ServActivitati serv{ repo, rc, val };
	try
	{
		serv.stergere_activitate(" dvwayuv");
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	try
	{
		serv.stergere_activitate("dwaf");
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	serv.adaugare_activitate("aa", "aadhawuodh", "ewyu", 1);
	try
	{
		serv.stergere_activitate("aa");
		assert(true);
	}
	catch (exception)
	{
		assert(false);
	}
}

void TestService::test_modificare_activitate()
{
	Repo_Memorie repo, rc;
	const Validator val;
	ServActivitati serv{ repo, rc, val };
	try
	{
		serv.modificare_activitate("bd73", "", "b di ", -32);
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	serv.adaugare_activitate("aa", "aadhawuodh", "ewyu", 1);
	try
	{
		serv.modificare_activitate("bb", "aadhawuodh", "ewyu", 1);
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}

	try
	{
		serv.modificare_activitate("aa", "", "ewfawfayu", 213);
		assert(true);
	}
	catch (exception)
	{
		assert(false);
	}
}

void TestService::test_obtine_activitate()
{
	Repo_Memorie repo, rc;
	const Validator val;
	ServActivitati serv{ repo, rc, val };
	serv.adaugare_activitate("a", "a", "a", 1);
	serv.adaugare_activitate("b", "b", "b", 2);
	serv.adaugare_activitate("c", "c", "c", 3);
	Activitate a{ serv.obtine_activitate("a") };
	assert(a.get_descriere() == "a");
}

void TestService::test_filtrare()
{
	Repo_Memorie repo, rc;
	const Validator val;
	ServActivitati serv{ repo, rc, val };
	serv.adaugare_activitate("a", "a", "a", 1);
	serv.adaugare_activitate("b", "a", "b", 2);
	serv.adaugare_activitate("c", "c", "c", 3);
	const vector<Activitate>& acts = serv.filtreaza_dupa_tip("a");
	assert(acts.at(0).get_descriere() == "a");
}

void TestService::test_obtine_curente()
{
	Repo_Memorie repo, rc;
	const Validator val;
	ServActivitati serv{ repo, rc, val };
	serv.adauga_curente("a", "a", "a", 1);
	serv.adauga_curente("b", "b", "b", 2);
	serv.adauga_curente("c", "c", "c", 3);
	const vector<Activitate>& acts = serv.obtine_activitatile_curente();
	assert(acts.size() == 3);
}

void TestService::test_sortare()
{
	Repo_Memorie repo, rc;
	const Validator val;
	ServActivitati serv{ repo, rc, val };
	serv.adaugare_activitate("b", "a", "b", 2);
	serv.adaugare_activitate("c", "c", "c", 3);
	serv.adaugare_activitate("a", "a", "a", 1);
	const vector<Activitate>& acts = serv.sorteaza_activitati();
	assert(acts.at(0).get_titlu() == "a");
	assert(acts.at(1).get_titlu() == "b");
	assert(acts.at(2).get_titlu() == "c");
}

void TestService::test_obtine_toate_activitatile()
{
	Repo_Memorie repo, rc;
	const Validator val;
	ServActivitati serv{ repo, rc, val };
	serv.adaugare_activitate("a", "a", "a", 1);
	serv.adaugare_activitate("b", "b", "b", 2);
	serv.adaugare_activitate("c", "c", "c", 3);
	const vector<Activitate>& v = serv.obtine_toate_activitatile();
	assert(v.at(0).get_titlu() == "a");
	assert(v.at(1).get_titlu() == "b");
	assert(v.at(2).get_titlu() == "c");
	assert(v.at(0).get_durata() == 1);
	assert(v.at(1).get_durata() == 2);
	assert(v.at(2).get_durata() == 3);
}

void TestService::test_adauga_curent()
{
	Repo_Memorie repo, rc;
	const Validator val;
	ServActivitati serv{ repo, rc, val };
	try
	{
		serv.adauga_curente("", "dawgd8hh.'/.;", "ewyu", -1);
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	serv.adauga_curente("aa", "aadhawuodh", "ewyu", 1);
	try
	{
		serv.adauga_curente("aa", "dawgd8hh.'/.;", "ewyu", 23);
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
}

void TestService::test_golire_curente()
{
	Repo_Memorie repo, rc;
	const Validator val;
	ServActivitati serv{ repo, rc, val };
	serv.adauga_curente("a", "a", "a", 1);
	serv.adauga_curente("b", "b", "b", 2);
	serv.adauga_curente("c", "c", "c", 3);
	serv.golire_curente();
	const vector<Activitate>& acts = serv.obtine_activitatile_curente();
	assert(acts.size() == 0);
}

void TestService::test_adauga_random()
{
	Repo_Memorie repo, rc;
	const Validator val;
	ServActivitati serv{ repo, rc, val };
	serv.adauga_curente_random(3);
	const vector<Activitate>& v{ serv.obtine_activitatile_curente() };
	assert(v.at(0).get_titlu() != v.at(1).get_titlu());
	assert(v.at(1).get_titlu() != v.at(2).get_titlu());
}

void TestService::test_raport()
{
	Repo_Memorie repo, rc;
	const Validator val;
	ServActivitati serv{ repo, rc, val };
	serv.adaugare_activitate("a", "a", "a", 1);
	serv.adaugare_activitate("b", "b", "b", 2);
	serv.adaugare_activitate("c", "c", "c", 3);
	serv.adaugare_activitate("d", "a", "a", 1);
	serv.adaugare_activitate("f", "b", "b", 2);
	serv.adaugare_activitate("g", "c", "c", 3);
	const vector<DTO_Stats>& rap{ serv.raport() };
	assert(rap.size() == 3);
}

void TestService::test_export_serv()
{
	Repo_Memorie repo, rc;
	const Validator val;
	ServActivitati serv{ repo, rc, val };
	serv.adauga_curente("a", "a", "a", 1);
	serv.adauga_curente("b", "b", "b", 2);
	serv.adauga_curente("c", "c", "c", 3);
	try
	{
		serv.export_activitati_curente("test2.csv");
		assert(true);
	}
	catch (exception)
	{
		assert(false);
	}
	try
	{
		serv.export_activitati_curente("W//:'~ \\|%^");
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
}

void TestService::test_undo()
{
	Repo_Memorie repo, rc;
	const Validator val;
	ServActivitati serv{ repo, rc, val };
	try
	{
		serv.do_undo();
		assert(false);
	}
	catch (const exception& error)
	{
		assert(strcmp(error.what(), "<Nu se mai poate face undo>") == 0);
	}

	serv.adaugare_activitate("a", "a", "a", 1);
	serv.do_undo();
	assert(serv.obtine_toate_activitatile().size() == 0);
	serv.adaugare_activitate("b", "b", "b", 1);
	serv.stergere_activitate("b");
	serv.do_undo();
	assert(serv.obtine_toate_activitatile().size() == 1);
	try
	{
		assert(serv.obtine_activitate("b").get_titlu() == "b");
	}
	catch (exception)
	{
		assert(false);
	}
	serv.modificare_activitate("b", "a", "c", 3);
	serv.do_undo();
	try
	{
		assert(serv.obtine_activitate("b").get_durata() == 1);
	}
	catch (exception)
	{
		assert(false);
	}
}

void TestService::test_all_service()
{
	test_adaugare_activitate();
	test_stergere_activitate();
	test_modificare_activitate();
	test_obtine_toate_activitatile();
	test_obtine_curente();
	test_obtine_activitate();
	test_filtrare();
	test_sortare();
	test_adauga_curent();
	test_golire_curente();
	test_raport();
	test_adauga_random();
	test_export_serv();
	test_undo();
}