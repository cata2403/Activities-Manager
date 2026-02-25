#pragma once
#include "repository.h"
#include "repo_activitati.h"

class TestRepo
{
public:
	TestRepo(RepoActivitati& r) : repo{r} {};
private:
	RepoActivitati& repo;
	void test_adaugare();
	void test_cautare();
	void test_stergere();
	void test_modificare();
	void test_get_all();
	void test_load_save_from_file();
	void test_exception();
	void test_adaugaRaw();
public:
	void test_all_repo();
};
