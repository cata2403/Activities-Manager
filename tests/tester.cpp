#include "tester.h"
#include "teste_service.h"
#include "repo_map.h"

void Tester::run_all_tests()
{
	TestDomain::test_all_domain();
	TestValidator::test_all_validator();
	TestService::test_all_service();
	Repo_Memorie r1;
	Repo_Dictionar r2{0};
	TestRepo t1{ r1 }, t2{ r2 };
	t1.test_all_repo();
	t2.test_all_repo();
}