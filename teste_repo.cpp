#include "teste_repo.h"
#include "repo_activitati.h"
#include "repo_fisiere.h"
#include "repo_map.h"
#include <qdebug.h>
#include <assert.h>
#include <stdexcept>

using std::exception;

void TestRepo::test_adaugare()
{

	const Activitate a1{ "1", "1", "1", 1 }, a2{ "2", "2", "2", 2 }, a3{ "3", "3", "3", 3 };
	try
	{
		repo.adaugare(a1); 
		repo.adaugare(a2);
		repo.adaugare(a3);
		assert(true);
	}
	catch (exception)
	{
		assert(false);
	}
	try
	{
		repo.adaugare(a1);
		assert(false);
	}
	catch (const exception& error)
	{
		assert(!strcmp(error.what(), "<Activitatea este deja adaugata>"));
		assert(true);
	}
}

void TestRepo::test_cautare()
{
	const Activitate a1{ "1", "1", "1", 1 }, a2{ "2", "2", "2", 2 }, a3{ "3", "3", "3", 3 };
	repo.adaugare(a1);
	repo.adaugare(a2);
	repo.adaugare(a3);
	const Activitate& a = repo.cautare("1"), & b = repo.cautare("2"), & c = repo.cautare("3");
	assert(a.get_descriere() == "1");
	assert(a.get_durata() == 1);
	assert(a.get_tip() == "1");
	assert(b.get_descriere() == "2");
	assert(b.get_durata() == 2);
	assert(b.get_tip() == "2");
	assert(c.get_descriere() == "3");
	assert(c.get_durata() == 3);
	assert(c.get_tip() == "3");
}

void TestRepo::test_stergere()
{

	Activitate a1{ "1", "1", "1", 1 }, a2{ "2", "2", "2", 2 }, a3{ "3", "3", "3", 3 };
	repo.adaugare(a1);
	repo.adaugare(a2);
	repo.adaugare(a3);
	try
	{
		repo.stergere("4");
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	repo.stergere("1");
	try
	{
		a1 = repo.cautare("1");
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	repo.stergere("2");
	try
	{
		a1 = repo.cautare("2");
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
	repo.stergere("3");
	try
	{
		a1 = repo.cautare("3");
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
}

void TestRepo::test_modificare()
{

	Activitate a{ "1", "1", "1", 1 };
	repo.adaugare(a);
	a = { "1", "2", "2", 2 };
	repo.modificare(a);
	a = repo.cautare("1");
	assert(a.get_durata() == 2);
	a = { "2", "2", "2", 2 };
	try
	{
		repo.modificare(a);
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
}

void TestRepo::test_get_all()
{
    const vector<Activitate>& v2 = repo.get_all();
	assert(size(v2) == 0);
	const Activitate a1 = Activitate("1", "1", "1", 1), a2 = Activitate("2", "2", "2", 2), a3 = Activitate("3", "3", "3", 3);
	repo.adaugare(a1);
	repo.adaugare(a2);
	repo.adaugare(a3);
	const vector<Activitate>& v = repo.get_all();
	assert(v.at(0).get_descriere() == "1");
	assert(v.at(1).get_tip() == "2");
	assert(v.at(2).get_durata() == 3);
	
}

void TestRepo::test_load_save_from_file()
{
	try
	{
		Repo_Fisiere repo{ "7e52tqg/`1`1/" };
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}

	try
	{
		Repo_Fisiere repo{ "test.csv" };
	}
	catch (exception)
	{
		assert(false);
	}

	try
	{
		Repo_Fisiere repo{ "test3.txt" };
		Activitate act = repo.cautare("a");
		assert(act.get_titlu() == "a");
		assert(repo.cautare("b").get_titlu() == "b");
	}
	catch (exception)
	{
		assert(false);
	}
}

void TestRepo::test_exception()
{
	Repo_Dictionar r{1};
	try
	{
		r.get_all();
		assert(false);
	}
	catch (exception)
	{
		assert(true);
	}
}

void TestRepo::test_adaugaRaw()
{
	Repo_Memorie r;
	r.adaugareNoUnique(Activitate{ "1","1","1",1 });
	r.adaugareNoUnique(Activitate{ "1","1","1",1 });
	r.adaugareNoUnique(Activitate{ "1","1","1",1 });
	r.adaugareNoUnique(Activitate{ "1","1","1",1 });
	r.adaugareNoUnique(Activitate{ "1","1","1",1 });
	assert(r.get_all().size() == 5);
	assert(r.get_all().at(0).get_durata() == 1);
	assert(r.get_all().at(2).get_durata() == 1);
	assert(r.get_all().at(4).get_durata() == 1);
}

void TestRepo::test_all_repo()
{
	repo.golire();
	test_adaugare();
	repo.golire();
	test_cautare();
	repo.golire();
	test_stergere();
	repo.golire();
	test_modificare();
	repo.golire();
	test_get_all();
	test_load_save_from_file();
	test_exception();
	repo.golire();
	test_adaugaRaw();
}