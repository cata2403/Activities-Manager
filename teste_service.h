#pragma once

class TestService
{
private:
	static void test_adaugare_activitate();
	static void test_stergere_activitate();
	static void test_modificare_activitate();
	static void test_obtine_toate_activitatile();
	static void test_obtine_curente();
	static void test_obtine_activitate();
	static void test_filtrare();
	static void test_sortare();
	static void test_adauga_curent();
	static void test_golire_curente();
	static void test_raport();
	static void test_adauga_random();
	static void test_export_serv();
	static void test_undo();
public:
	static void test_all_service();
};